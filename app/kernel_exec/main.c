/****************************************************************************
 * Copyright (C) 2020-2024 by Ivan Podmazov                                 *
 *                                                                          *
 * This file is part of Port.                                               *
 *                                                                          *
 *   Port is free software: you can redistribute it and/or modify it        *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   Port is distributed in the hope that it will be useful,                *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Port. If not, see <http://www.gnu.org/licenses/>.   *
 ****************************************************************************/

/**
 * @file
 * @brief Kernel execution application.
 */

#include <station/plugin.def.h>
#include <station/plugin.typ.h>
#include <station/application.def.h>
#include <station/application.fun.h>
#include <station/shared_memory.fun.h>
#include <station/fsm.typ.h>
#include <station/fsm.def.h>
#include <station/concurrent.typ.h>
#include <station/concurrent.fun.h>
#include <station/opencl.typ.h>

#include <port/host/opencl/memory.fun.h>
#include <port/host/opencl/memory.typ.h>
#include <port/host/opencl/kargs_setter.typ.h>
#include <port/host/opencl/program.fun.h>
#include <port/host/opencl/program.typ.h>
#include <port/host/cpu/memory.fun.h>
#include <port/host/cpu/pfunc.typ.h>
#include <port/host/memory.typ.h>
#include <port/host/vtable.typ.h>
#include <port/host/vtable.def.h>

#include <argp.h>
#include <CL/cl.h>
#include <dlfcn.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/time.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define _STR(x) #x
#define STR(x) _STR(x)

///////////////////////////////////////////////////////////////////////////////

enum plugin_args_keys {
    ARGKEY_VERSION = 'V',

    ARGKEY_BUILD_LOG = 'j',

    ARGKEY_VTABLE_SYMBOL = 'v',

    ARGKEY_WORK_SIZE = 'w',

    ARGKEY_OUT_SHM = 'o',

    ARGKEY_CPU_BATCH_SIZE = 'b',
    ARGKEY_CPU_BUSY_WAIT = 'B',

    ARGKEY_CL_DEVICE_IDX = 'd',
    ARGKEY_CL_LOCAL_WORK_SIZE = 'l',

    ARGKEY_PROFILE = 'p',
};

static struct argp_option plugin_args_options[] = {
    {.name = "version", .key = ARGKEY_VERSION, .doc = "Display expected library vtable version", .group = -1},

    {.name = "build-log", .key = ARGKEY_BUILD_LOG, .doc = "Display OpenCL program build log"},

    {.doc = "Input options:"},
    {.name = "vtable", .key = ARGKEY_VTABLE_SYMBOL, .arg = "NAME", .doc = "Name of vtable symbol in the shared library"},

    {.doc = "Output options:"},
    {.name = "out-shm", .key = ARGKEY_OUT_SHM, .arg = "IDHEX@PATH", .doc = "Shared memory with pointer support for writing output data"},
    {.name = "work-size", .key = ARGKEY_WORK_SIZE, .arg = "SIZE", .doc = "Work size"},

    {.doc = "Execution options (CPU):"},
    {.name = "batch-size", .key = ARGKEY_CPU_BATCH_SIZE, .arg = "SIZE", .doc = "Thread work item batch size"},
    {.name = "busy-wait", .key = ARGKEY_CPU_BUSY_WAIT, .doc = "Enable busy-waiting"},

    {.doc = "Execution options (OpenCL):"},
    {.name = "device-idx", .key = ARGKEY_CL_DEVICE_IDX, .arg = "IDX", .doc = "Use OpenCL device specified by index"},
    {.name = "local-work-size", .key = ARGKEY_CL_LOCAL_WORK_SIZE, .arg = "SIZE", .doc = "Local work size for execution on OpenCL"},

    {.doc = "Profiling options:"},
    {.name = "profile", .key = ARGKEY_PROFILE, .arg = "NUM", .doc = "Profile kernel using additional number of runs"},

    {0}
};

static error_t plugin_args_parse(int key, char *arg, struct argp_state *state);

static struct argp plugin_args_parser = {
    .options = plugin_args_options,
    .parser = plugin_args_parse,
    .args_doc = "[KERNEL_NAME]",
};

struct plugin_args {
    struct {
        const char *vtable_symbol_name;
    } in;

    struct {
        const char *shm_path;
        int shm_proj_id;

        unsigned work_size;
    } out;

    struct {
        unsigned batch_size;
        bool busy_wait;
    } cpu;

    struct {
        bool build_log;
        unsigned device_idx;
        unsigned local_work_size;
    } opencl;

    struct {
        unsigned runs;
    } profile;

    const char *kernel_name;
};

///////////////////////////////////////////////////////////////////////////////

struct plugin_resources {
    struct plugin_args *args;

    struct {
        port_const_void_ptr_t shm_in;
        port_const_void_ptr_t shm_in_metadata;

        void *shm_out_addr;
        port_void_ptr_t shm_out;
        port_void_ptr_t shm_out_metadata;

        port_void_ptr_t private;
        port_void_ptr_t private_metadata;
    } kargs;

    struct {
        const port_vtable_t *vtable;

        struct {
            port_memory_operations_t op;
            port_memory_operation_properties_t op_prop_ro;
            port_memory_operation_properties_t op_prop_rw;
            port_memory_operation_properties_t op_prop_wo;
        } memory;

        port_size_t work_type;

        station_sfunc_t sfunc;
        unsigned runs_done;

        float total_milliseconds;
        float min_milliseconds;
        float max_milliseconds;
    } exec;

    struct {
        bool used;
        station_concurrent_processing_contexts_array_t *contexts;

        port_pfunc_t pfunc; // equivalent to station_pfunc_t

        struct {
            port_memory_operations_t op;
            port_memory_operation_properties_t op_prop;
        } memory;
    } cpu;

    struct {
        bool used;
        station_opencl_contexts_array_t *contexts;

        cl_command_queue command_queue;

        cl_program program;
        cl_kernel kernel;

        port_kargs_setter_t kargs_setter;

        port_memory_opencl_alloc_properties_t alloc_properties[3]; // read-only, read+write, write-only
        port_memory_opencl_map_properties_t map_properties[3]; // read-only, read+write, write-only
    } opencl;
};

///////////////////////////////////////////////////////////////////////////////

static error_t plugin_args_parse(int key, char *arg, struct argp_state *state)
{
    struct plugin_args *args = state->input;

    switch (key)
    {
        case ARGKEY_VERSION:
            {
                uint32_t version_year = PORT_VTABLE_VERSION / 10000;
                uint32_t version_month = (PORT_VTABLE_VERSION / 100) % 100;
                uint32_t version_day = PORT_VTABLE_VERSION % 100;
                printf("%u.%.2u.%.2u\n", version_year, version_month, version_day);
                exit(EXIT_SUCCESS);
            }
            break;

        case ARGKEY_BUILD_LOG:
            args->opencl.build_log = true;
            break;

        case ARGKEY_VTABLE_SYMBOL:
            args->in.vtable_symbol_name = arg;
            break;

        case ARGKEY_OUT_SHM:
            {
                if (strlen(arg) < 4)
                {
                    printf("[Error] Output shared memory specifier is too short\n");
                    return EINVAL;
                }
                else if ((arg[2] != '@') || (strspn(arg, "0123456789ABCDEFabcdef") != 2))
                {
                    printf("[Error] Output shared memory specifier has incorrect format\n");
                    return EINVAL;
                }

                int proj_id = 0;
                {
                    if ((arg[0] >= '0') && (arg[0] <= '9'))
                        proj_id += arg[0] - '0';
                    else if ((arg[0] >= 'A') && (arg[0] <= 'F'))
                        proj_id += arg[0] - 'A' + 10;
                    else if ((arg[0] >= 'a') && (arg[0] <= 'f'))
                        proj_id += arg[0] - 'a' + 10;

                    proj_id <<= 4;

                    if ((arg[1] >= '0') && (arg[1] <= '9'))
                        proj_id += arg[1] - '0';
                    else if ((arg[1] >= 'A') && (arg[1] <= 'F'))
                        proj_id += arg[1] - 'A' + 10;
                    else if ((arg[1] >= 'a') && (arg[1] <= 'f'))
                        proj_id += arg[1] - 'a' + 10;
                }

                args->out.shm_proj_id = proj_id;
                args->out.shm_path = arg + 3;
            }
            break;

        case ARGKEY_WORK_SIZE:
            {
                int num = atoi(arg);
                if (num < 0)
                {
                    printf("[Error] work size cannot be a negative number\n");
                    return EINVAL;
                }

                args->out.work_size = num;
            }
            break;

        case ARGKEY_CPU_BATCH_SIZE:
            {
                int num = atoi(arg);
                if (num < 0)
                {
                    printf("[Error] work item batch size cannot be a negative number\n");
                    return EINVAL;
                }

                args->cpu.batch_size = num;
            }
            break;

        case ARGKEY_CPU_BUSY_WAIT:
            args->cpu.busy_wait = true;
            break;

        case ARGKEY_CL_DEVICE_IDX:
            {
                int num = atoi(arg);
                if (num < 0)
                {
                    printf("[Error] OpenCL device index cannot be negative\n");
                    return EINVAL;
                }

                args->opencl.device_idx = num;
            }
            break;

        case ARGKEY_CL_LOCAL_WORK_SIZE:
            {
                int num = atoi(arg);
                if (num < 0)
                {
                    printf("[Error] local work size cannot be a negative number\n");
                    return EINVAL;
                }

                args->opencl.local_work_size = num;
            }
            break;

        case ARGKEY_PROFILE:
            {
                int num = atoi(arg);
                if (num < 0)
                {
                    printf("[Error] number of profiling runs cannot be negative\n");
                    return EINVAL;
                }

                args->profile.runs = num;
            }
            break;

        case ARGP_KEY_ARG:
            if (args->kernel_name != NULL)
            {
                printf("[Error] cannot execute more than one kernel\n");
                return EINVAL;
            }

            args->kernel_name = arg;
            break;

        case ARGP_KEY_ARGS:
        case ARGP_KEY_NO_ARGS:
        case ARGP_KEY_END:
        case ARGP_KEY_INIT:
        case ARGP_KEY_SUCCESS:
        case ARGP_KEY_ERROR:
        case ARGP_KEY_FINI:
            break;

        default:
            return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

///////////////////////////////////////////////////////////////////////////////

static STATION_SFUNC(exec_loop);

static STATION_SFUNC(exec_kernel_cpu)
{
    struct plugin_resources *resources = fsm_data;

    // Record start time
    struct timeval tval_start;
    gettimeofday(&tval_start, NULL);

    // Execute the kernel
    do // threads may be busy for a short amount of time, try until success
    {
    }
    while (!station_concurrent_processing_execute(&resources->cpu.contexts->contexts[0],
                resources->args->out.work_size, resources->args->cpu.batch_size,
                resources->cpu.pfunc, resources->kargs.private,
                NULL, NULL, resources->args->cpu.busy_wait));

    // Record end time
    struct timeval tval_end;
    gettimeofday(&tval_end, NULL);

    // Update time records when profiling
    if (resources->exec.runs_done > 0)
    {
        float milliseconds = (tval_end.tv_sec - tval_start.tv_sec) * 1000.0f +
            (tval_end.tv_usec - tval_start.tv_usec) / 1000.0f;

        resources->exec.total_milliseconds += milliseconds;

        if (milliseconds < resources->exec.min_milliseconds)
            resources->exec.min_milliseconds = milliseconds;

        if (milliseconds > resources->exec.max_milliseconds)
            resources->exec.max_milliseconds = milliseconds;
    }

    // Proceed to the next loop iteration
    resources->exec.runs_done++;
    state->sfunc = exec_loop;
}

static STATION_SFUNC(exec_kernel_opencl)
{
    struct plugin_resources *resources = fsm_data;

    // Set kernel arguments
    if (resources->exec.runs_done == 0)
        resources->opencl.kargs_setter(resources->opencl.kernel,
                (cl_ulong)-1, resources->kargs.private);

    // Enqueue the kernel
    size_t global_work_size = resources->args->out.work_size;
    size_t local_work_size = resources->args->opencl.local_work_size;

    cl_event prof_event;

    cl_int err = clEnqueueNDRangeKernel(resources->opencl.command_queue,
            resources->opencl.kernel, 1, NULL, &global_work_size,
            local_work_size > 0 ? &local_work_size : NULL,
            0, NULL, &prof_event);
    if (err != CL_SUCCESS)
    {
        printf("[Error] couldn't enqueue kernel for execution (error code %i)\n", err);
        exit(EXIT_FAILURE);
    }

    // Wait until finished
    err = clWaitForEvents(1, &prof_event);
    if (err != CL_SUCCESS)
    {
        printf("[Error] couldn't wait for kernel event (error code %i)\n", err);
        exit(EXIT_FAILURE);
    }

    // Update time records when profiling
    if (resources->exec.runs_done > 0)
    {
        cl_ulong start_time, end_time; // nanoseconds

        err = clGetEventProfilingInfo(prof_event, CL_PROFILING_COMMAND_START,
                    sizeof(start_time), &start_time, NULL);
        if (err != CL_SUCCESS)
        {
            printf("[Error] couldn't get kernel start time (error code %i)\n", err);
            exit(EXIT_FAILURE);
        }

        err = clGetEventProfilingInfo(prof_event, CL_PROFILING_COMMAND_END,
                    sizeof(end_time), &end_time, NULL);
        if (err != CL_SUCCESS)
        {
            printf("[Error] couldn't get kernel start time (error code %i)\n", err);
            exit(EXIT_FAILURE);
        }

        float milliseconds = (end_time - start_time) / 1e6f;

        resources->exec.total_milliseconds += milliseconds;

        if (milliseconds < resources->exec.min_milliseconds)
            resources->exec.min_milliseconds = milliseconds;

        if (milliseconds > resources->exec.max_milliseconds)
            resources->exec.max_milliseconds = milliseconds;
    }

    // Proceed to the next loop iteration
    resources->exec.runs_done++;
    state->sfunc = exec_loop;
}

static STATION_SFUNC(exec_loop)
{
    struct plugin_resources *resources = fsm_data;

    // Set next sfunc
    state->sfunc = resources->exec.sfunc;

    if (resources->exec.runs_done == 0)
    {
        printf("Executing kernel '%s' (work size %llu)...\n",
                resources->args->kernel_name, (unsigned long long)resources->args->out.work_size);
        return;
    }
    else if (resources->exec.runs_done == 1)
    {
        printf("Done.\n");

        // Write output data if needed
        if (resources->kargs.shm_out != NULL)
        {
            if (!resources->exec.vtable->kargs_operations.copy_fn(
                        resources->kargs.shm_out, resources->kargs.private, resources->kargs.private_metadata,
                        true,
                        &resources->cpu.memory.op, &resources->cpu.memory.op_prop,
                        &resources->cpu.memory.op, &resources->cpu.memory.op_prop,
                        &resources->exec.memory.op, &resources->exec.memory.op_prop_rw))
            {
                printf("[Error] couldn't write output kernel arguments data\n");
                exit(EXIT_FAILURE);
            }
        }

        if (resources->args->profile.runs > 0)
            printf("\nExecuting kernel %u more times to profile...\n",
                    resources->args->profile.runs);
    }

    // If done, print statistics and exit
    if (resources->exec.runs_done == 1 + resources->args->profile.runs)
    {
        if (resources->args->profile.runs > 0)
        {
            printf("Minimum time = %.2g ms\n", resources->exec.min_milliseconds);
            printf("Average time = %.2g ms\n",
                    resources->exec.total_milliseconds / resources->args->profile.runs);
            printf("Maximum time = %.2g ms\n", resources->exec.max_milliseconds);
        }

        state->sfunc = NULL;
        return;
    }

    // Restore kernel arguments
    if (!resources->exec.vtable->kargs_operations.copy_fn(
                resources->kargs.private, resources->kargs.shm_in, resources->kargs.private_metadata,
                true,
                &resources->cpu.memory.op, &resources->cpu.memory.op_prop,
                &resources->exec.memory.op, &resources->exec.memory.op_prop_rw,
                &resources->cpu.memory.op, &resources->cpu.memory.op_prop))
    {
        printf("[Error] couldn't restore private kernel arguments data\n");
        exit(EXIT_FAILURE);
    }
}

///////////////////////////////////////////////////////////////////////////////

// Plugin help function
static STATION_PLUGIN_HELP_FUNC(plugin_help)
{
    (void) argc;
    (void) argv;

    argp_help(&plugin_args_parser, stdout, ARGP_HELP_STD_HELP, APP_NAME);
}

// Plugin configuration function
static STATION_PLUGIN_CONF_FUNC(plugin_conf)
{
    {
        struct plugin_args *pargs = malloc(sizeof(*pargs));

        if (pargs == NULL)
        {
            printf("[Error] couldn't allocate memory for command line arguments parser\n");
            exit(EXIT_FAILURE);
        }

        *pargs = (struct plugin_args){0};
        args->cmdline = pargs;
    }

    error_t err = argp_parse(&plugin_args_parser, argc, argv,
            ARGP_NO_EXIT | ARGP_NO_HELP, NULL, args->cmdline);
    if (err != 0)
    {
        printf("[Error] couldn't parse command line arguments\n");
        exit(EXIT_FAILURE);
    }

    args->num_sharedmem_ptrs_used = 1;
    args->num_libraries_used = 1;
    args->num_concurrent_processing_contexts_used = 1;
    args->num_opencl_contexts_used = 1;
}

// Plugin initialization function
static STATION_PLUGIN_INIT_FUNC(plugin_init)
{
    int step = 0;

    // Allocate structure for resources
    struct plugin_resources *resources;
    outputs->plugin_resources = resources = malloc(sizeof(*resources));

    if (resources == NULL)
    {
        printf("[Error] couldn't allocate structure of resources\n");
        goto failure;
    }
    step = 1;

    *resources = (struct plugin_resources){.args = inputs->cmdline};

    // Get library vtable
    if (inputs->num_libraries == 0)
    {
        printf("[Error] no library has been specified\n");
        goto failure;
    }

    resources->exec.vtable = dlsym(inputs->libraries[0], resources->args->in.vtable_symbol_name);
    if (resources->exec.vtable == NULL)
    {
        printf("[Error] couldn't get library vtable address\n");
        goto failure;
    }
    else if (resources->exec.vtable->magic != PORT_VTABLE_MAGIC)
    {
        printf("[Error] library vtable magic value (%u) does not match %u\n",
                resources->exec.vtable->magic, PORT_VTABLE_MAGIC);
        goto failure;
    }
    else if (resources->exec.vtable->version != PORT_VTABLE_VERSION)
    {
        printf("[Error] library vtable version (%u) does not match %u\n",
                resources->exec.vtable->version, PORT_VTABLE_VERSION);
        goto failure;
    }

    // Initialize contexts
    if (inputs->concurrent_processing_contexts->num_contexts +
            inputs->opencl_contexts->num_contexts != 1)
    {
        if (inputs->concurrent_processing_contexts->num_contexts +
                inputs->opencl_contexts->num_contexts == 0)
            printf("[Error] no computational context (CPU threads/OpenCL) has been specified\n");
        else
            printf("[Error] too many computational contexts has been specified\n");

        goto failure;
    }

    resources->cpu.used = inputs->concurrent_processing_contexts->num_contexts != 0;
    resources->opencl.used = inputs->opencl_contexts->num_contexts != 0;

    if (resources->cpu.used)
        resources->cpu.contexts = inputs->concurrent_processing_contexts;
    else if (resources->opencl.used)
        resources->opencl.contexts = inputs->opencl_contexts;

    // Build OpenCL program
    if (resources->opencl.used)
    {
        if (resources->exec.vtable->opencl.program_sources == NULL)
        {
            printf("[Error] OpenCL program sources are not available\n");
            goto failure;
        }

        size_t num_program_sources = 0;
        while (resources->exec.vtable->opencl.program_sources[num_program_sources] != NULL)
            num_program_sources++;

        cl_int err;
        resources->opencl.program = port_opencl_build_program(
                resources->opencl.contexts->contexts[0],
                resources->opencl.contexts->context_info[0].num_devices,
                resources->opencl.contexts->context_info[0].device_ids,
                num_program_sources,
                (const struct port_opencl_program_source**)resources->exec.vtable->opencl.program_sources,
                0, NULL,
                "", "",
                resources->args->opencl.build_log ? stdout : NULL, &err);

        if (resources->opencl.program == NULL)
        {
            printf("[Error] couldn't build OpenCL program (error code %i)\n", err);
            goto failure;
        }
        step = 2;
    }

    // Get OpenCL kernel
    if (resources->args->kernel_name == NULL)
        return; // engine building process is tested, nothing more to do

    if (resources->opencl.used)
    {
        cl_int err;
        resources->opencl.kernel = clCreateKernel(resources->opencl.program,
                resources->args->kernel_name, &err);
        if (resources->opencl.kernel == NULL)
        {
            printf("[Error] couldn't create OpenCL kernel (error code %i)\n", err);
            goto failure;
        }
        step = 3;
    }

    // Extract kernel wrapper
    if (resources->exec.vtable->kernel_descriptions == NULL)
    {
        printf("[Error] kernel descriptions list is not available\n");
        goto failure;
    }

    {
        port_bool_t kernel_found = false;

        for (const port_vtable_kernel_description_t *descr = resources->exec.vtable->kernel_descriptions;
                descr->kernel_name != NULL; descr++)
        {
            if (strcmp(descr->kernel_name, resources->args->kernel_name) == 0)
            {
                kernel_found = true;

                resources->exec.work_type = descr->work_type;

                if (resources->cpu.used)
                    resources->cpu.pfunc = descr->cpu.pfunc;
                else if (resources->opencl.used)
                    resources->opencl.kargs_setter = descr->opencl.kargs_setter_fn;

                break;
            }
        }

        if (!kernel_found)
        {
            printf("[Error] kernel '%s' is not provided by the library\n", resources->args->kernel_name);
            goto failure;
        }
    }

    // Create OpenCL command queue
    if (resources->opencl.used)
    {
        if (resources->args->opencl.device_idx >= resources->opencl.contexts->context_info[0].num_devices)
        {
            printf("[Error] OpenCL device index is invalid\n");
            goto failure;
        }

        cl_queue_properties queue_properties[] = {CL_QUEUE_PROPERTIES,
            (resources->args->profile.runs > 0) ? CL_QUEUE_PROFILING_ENABLE : 0, 0};
        cl_int err;
        resources->opencl.command_queue = clCreateCommandQueueWithProperties(
                resources->opencl.contexts->contexts[0],
                resources->opencl.contexts->context_info[0].device_ids[resources->args->opencl.device_idx],
                queue_properties, &err);
        if (err != CL_SUCCESS)
        {
            printf("[Error] couldn't create OpenCL command queue\n");
            goto failure;
        }
        step = 4;

        for (int i = 0; i < 3; i++)
            resources->opencl.alloc_properties[i].context = resources->opencl.contexts->contexts[0];

        resources->opencl.alloc_properties[0].svm_mem_flags = CL_MEM_READ_ONLY;
        resources->opencl.alloc_properties[1].svm_mem_flags = CL_MEM_READ_WRITE;
        resources->opencl.alloc_properties[2].svm_mem_flags = CL_MEM_WRITE_ONLY;

        for (int i = 0; i < 3; i++)
            resources->opencl.map_properties[i].command_queue = resources->opencl.command_queue;

        resources->opencl.map_properties[0].map_flags = CL_MAP_READ;
        resources->opencl.map_properties[1].map_flags = CL_MAP_WRITE;
        resources->opencl.map_properties[2].map_flags = CL_MAP_WRITE_INVALIDATE_REGION;
    }

    // Initialize profiling information
    resources->exec.min_milliseconds = INFINITY;

    // Initialize memory operations & operation properties
    if (resources->cpu.used)
    {
        resources->exec.memory.op.alloc_fn = port_memory_cpu_alloc;
        resources->exec.memory.op.free_fn = port_memory_cpu_free;
        resources->exec.memory.op.map_fn = port_memory_cpu_map;
        resources->exec.memory.op.unmap_fn = port_memory_cpu_unmap;
    }
    else if (resources->opencl.used)
    {
        resources->exec.memory.op.alloc_fn = port_memory_opencl_alloc;
        resources->exec.memory.op.free_fn = port_memory_opencl_free;
        resources->exec.memory.op.map_fn = port_memory_opencl_map;
        resources->exec.memory.op.unmap_fn = port_memory_opencl_unmap;

        resources->exec.memory.op_prop_ro.alloc_properties = &resources->opencl.alloc_properties[0];
        resources->exec.memory.op_prop_ro.map_properties = &resources->opencl.map_properties[0];

        resources->exec.memory.op_prop_rw.alloc_properties = &resources->opencl.alloc_properties[1];
        resources->exec.memory.op_prop_rw.map_properties = &resources->opencl.map_properties[1];

        resources->exec.memory.op_prop_wo.alloc_properties = &resources->opencl.alloc_properties[2];
        resources->exec.memory.op_prop_wo.map_properties = &resources->opencl.map_properties[2];
    }

    resources->cpu.memory.op.alloc_fn = port_memory_cpu_alloc;
    resources->cpu.memory.op.free_fn = port_memory_cpu_free;
    resources->cpu.memory.op.map_fn = port_memory_cpu_map;
    resources->cpu.memory.op.unmap_fn = port_memory_cpu_unmap;

    // Initialize input kernel arguments
    if (inputs->num_sharedmem_ptrs == 0)
    {
        printf("[Error] no kernel arguments data has been specified\n");
        goto failure;
    }
    else if (resources->exec.vtable->kargs_operations.metainfo_getter_fn == NULL)
    {
        printf("[Error] metainfo getter function for kernel arguments is not available\n");
        goto failure;
    }

    resources->kargs.shm_in = *(void**)inputs->sharedmem_ptrs[0];
    resources->kargs.shm_in_metadata = resources->exec.vtable->kargs_operations.metainfo_getter_fn(resources->kargs.shm_in);

    // Initialize work size
    if (resources->exec.vtable->kargs_operations.metainfo.work_size_getter_fn == NULL)
    {
        printf("[Error] work size getter function for kernel arguments metainfo is not available\n");
        goto failure;
    }

    {
        port_work_size_t work_size = resources->exec.vtable->kargs_operations.metainfo.work_size_getter_fn(
                resources->kargs.shm_in_metadata, resources->exec.work_type);

        if ((resources->args->out.work_size == 0) || (work_size < resources->args->out.work_size))
            resources->args->out.work_size = work_size;
    }

    // Initialize output kernel arguments
    if (resources->args->out.shm_path != NULL)
    {
        key_t key = ftok(resources->args->out.shm_path, resources->args->out.shm_proj_id);
        if (key == -1)
        {
            printf("[Error] couldn't create an IPC key for file '%s', project id %i\n",
                    resources->args->out.shm_path, resources->args->out.shm_proj_id);
            goto failure;
        }

        int shmid = shmget(key, 0, 0);
        if (shmid == -1)
        {
            printf("[Error] couldn't get output shared memory segment\n");
            goto failure;
        }

        void *shmaddr = station_shared_memory_with_ptr_support_attach(shmid, 0);
        if (shmaddr == NULL)
        {
            printf("[Error] couldn't attach output shared memory segment\n");
            goto failure;
        }
        step = 5;

        resources->kargs.shm_out_addr = shmaddr;

        shmaddr = station_shared_memory_with_ptr_support_get_data(shmaddr);

        resources->kargs.shm_out = *(void**)shmaddr;
        resources->kargs.shm_out_metadata = *((void**)shmaddr + 1);
    }

    // Initialize private kernel arguments
    if (resources->exec.vtable->kargs_operations.metainfo.alloc_copy_fn == NULL)
    {
        printf("[Error] function for kernel arguments metainfo copy allocation is not available\n");
        goto failure;
    }
    else if (resources->exec.vtable->kargs_operations.metainfo.free_fn == NULL)
    {
        printf("[Error] function for kernel arguments metainfo deallocation is not available\n");
        goto failure;
    }
    else if (resources->exec.vtable->kargs_operations.alloc_fn == NULL)
    {
        printf("[Error] function for kernel arguments allocation is not available\n");
        goto failure;
    }
    else if (resources->exec.vtable->kargs_operations.copy_fn == NULL)
    {
        printf("[Error] function for kernel arguments copying is not available\n");
        goto failure;
    }
    else if (resources->exec.vtable->kargs_operations.free_fn == NULL)
    {
        printf("[Error] function for kernel arguments deallocation is not available\n");
        goto failure;
    }

    resources->kargs.private_metadata = resources->exec.vtable->kargs_operations.metainfo.alloc_copy_fn(
            resources->kargs.shm_in_metadata, &resources->cpu.memory.op, &resources->cpu.memory.op_prop);
    if (resources->kargs.private_metadata == NULL)
    {
        printf("[Error] couldn't copy input kernel arguments metadata\n");
        goto failure;
    }
    step = 6;

    resources->kargs.private = resources->exec.vtable->kargs_operations.alloc_fn(
            resources->kargs.private_metadata, false,
            &resources->cpu.memory.op, &resources->cpu.memory.op_prop,
            &resources->exec.memory.op,
            &resources->exec.memory.op_prop_ro, &resources->exec.memory.op_prop_rw);
    if (resources->kargs.private == NULL)
    {
        printf("[Error] couldn't allocate private kernel arguments data\n");
        goto failure;
    }
    step = 7;

    if (!resources->exec.vtable->kargs_operations.copy_fn(
                resources->kargs.private, resources->kargs.shm_in, resources->kargs.private_metadata,
                false,
                &resources->cpu.memory.op, &resources->cpu.memory.op_prop,
                &resources->exec.memory.op, &resources->exec.memory.op_prop_rw,
                &resources->cpu.memory.op, &resources->cpu.memory.op_prop))
    {
        printf("[Error] couldn't copy private kernel arguments data\n");
        goto failure;
    }

    // Set initial finite state machine function
    if (resources->cpu.used)
        resources->exec.sfunc = exec_kernel_cpu;
    else if (resources->opencl.used)
        resources->exec.sfunc = exec_kernel_opencl;

    // Proceed to kernel execution
    outputs->fsm_initial_state.sfunc = exec_loop;
    outputs->fsm_data = resources;

    return;

failure:
    if (step >= 7)
        if (resources->kargs.private != NULL)
            resources->exec.vtable->kargs_operations.free_fn(resources->kargs.private,
                    resources->kargs.private_metadata,
                    &resources->cpu.memory.op, &resources->cpu.memory.op_prop,
                    &resources->exec.memory.op, &resources->exec.memory.op_prop_rw);

    if (step >= 6)
        if (resources->kargs.private_metadata != NULL)
            resources->exec.vtable->kargs_operations.metainfo.free_fn(resources->kargs.private_metadata,
                    &resources->cpu.memory.op, &resources->cpu.memory.op_prop);

    if (step >= 5)
        if (resources->kargs.shm_out_addr != NULL)
            shmdt(resources->kargs.shm_out_addr);

    if (step >= 4)
        if (resources->opencl.command_queue != NULL)
            clReleaseCommandQueue(resources->opencl.command_queue);

    if (step >= 3)
        if (resources->opencl.kernel != NULL)
            clReleaseKernel(resources->opencl.kernel);

    if (step >= 2)
        if (resources->opencl.program != NULL)
            clReleaseProgram(resources->opencl.program);

    if (step >= 1)
        free(resources);

    if (step >= 0)
        free(inputs->cmdline);

    exit(EXIT_FAILURE);
}

// Plugin finalization function
static STATION_PLUGIN_FINAL_FUNC(plugin_final)
{
    (void) quick;

    if (plugin_resources == NULL)
        return 0;

    struct plugin_resources *resources = plugin_resources;

    if (resources->kargs.private != NULL)
        resources->exec.vtable->kargs_operations.free_fn(resources->kargs.private,
                resources->kargs.private_metadata,
                &resources->cpu.memory.op, &resources->cpu.memory.op_prop,
                &resources->exec.memory.op, &resources->exec.memory.op_prop_rw);

    if (resources->kargs.private_metadata != NULL)
        resources->exec.vtable->kargs_operations.metainfo.free_fn(resources->kargs.private_metadata,
                &resources->cpu.memory.op, &resources->cpu.memory.op_prop);

    if (resources->kargs.shm_out_addr != NULL)
        shmdt(resources->kargs.shm_out_addr);

    if (resources->opencl.command_queue != NULL)
        clReleaseCommandQueue(resources->opencl.command_queue);

    if (resources->opencl.kernel != NULL)
        clReleaseKernel(resources->opencl.kernel);

    if (resources->opencl.program != NULL)
        clReleaseProgram(resources->opencl.program);

    free(resources->args);
    free(resources);

    return 0;
}

///////////////////////////////////////////////////////////////////////////////

// Define the plugin
STATION_PLUGIN(APP_NAME, "Kernel execution",
        plugin_help, plugin_conf, plugin_init, plugin_final);
STATION_APP_PLUGIN_MAIN()

