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
 * @brief OpenCL program builder.
 */

#include <port/host/opencl/program.fun.h>
#include <port/host/opencl/program.typ.h>

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const char*
port_opencl_concat_flags(
        const char *flags[])
{
    if (flags == NULL)
        return NULL;

    size_t total_length = 0;
    for (size_t i = 0; flags[i] != NULL; i++)
        total_length += strlen(flags[i]) + 1; // count separating space

    char *result = malloc(total_length);
    if (result == NULL)
        return NULL;

    size_t processed_length = 0;
    for (size_t i = 0; flags[i] != NULL; i++)
    {
        size_t length = strlen(flags[i]);
        memcpy(result + processed_length, flags[i], length);
        processed_length += length + 1;
        result[processed_length - 1] = ' ';
    }

    result[total_length - 1] = '\0';
    return result;
}

///////////////////////////////////////////////////////////////////////////////

#define CASE_RETURN_STRING(x) case x: return #x;

static
const char*
opencl_error_string(
        cl_int err)
{
    switch (err)
    {
        // run-time and JIT compiler errors
        CASE_RETURN_STRING(CL_SUCCESS)
        CASE_RETURN_STRING(CL_DEVICE_NOT_FOUND)
        CASE_RETURN_STRING(CL_DEVICE_NOT_AVAILABLE)
        CASE_RETURN_STRING(CL_COMPILER_NOT_AVAILABLE)
        CASE_RETURN_STRING(CL_MEM_OBJECT_ALLOCATION_FAILURE)
        CASE_RETURN_STRING(CL_OUT_OF_RESOURCES)
        CASE_RETURN_STRING(CL_OUT_OF_HOST_MEMORY)
        CASE_RETURN_STRING(CL_PROFILING_INFO_NOT_AVAILABLE)
        CASE_RETURN_STRING(CL_MEM_COPY_OVERLAP)
        CASE_RETURN_STRING(CL_IMAGE_FORMAT_MISMATCH)
        CASE_RETURN_STRING(CL_IMAGE_FORMAT_NOT_SUPPORTED)
        CASE_RETURN_STRING(CL_BUILD_PROGRAM_FAILURE)
        CASE_RETURN_STRING(CL_MAP_FAILURE)
        CASE_RETURN_STRING(CL_MISALIGNED_SUB_BUFFER_OFFSET)
        CASE_RETURN_STRING(CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST)
        CASE_RETURN_STRING(CL_COMPILE_PROGRAM_FAILURE)
        CASE_RETURN_STRING(CL_LINKER_NOT_AVAILABLE)
        CASE_RETURN_STRING(CL_LINK_PROGRAM_FAILURE)
        CASE_RETURN_STRING(CL_DEVICE_PARTITION_FAILED)
        CASE_RETURN_STRING(CL_KERNEL_ARG_INFO_NOT_AVAILABLE)

        // compile-time errors
        CASE_RETURN_STRING(CL_INVALID_VALUE)
        CASE_RETURN_STRING(CL_INVALID_DEVICE_TYPE)
        CASE_RETURN_STRING(CL_INVALID_PLATFORM)
        CASE_RETURN_STRING(CL_INVALID_DEVICE)
        CASE_RETURN_STRING(CL_INVALID_CONTEXT)
        CASE_RETURN_STRING(CL_INVALID_QUEUE_PROPERTIES)
        CASE_RETURN_STRING(CL_INVALID_COMMAND_QUEUE)
        CASE_RETURN_STRING(CL_INVALID_HOST_PTR)
        CASE_RETURN_STRING(CL_INVALID_MEM_OBJECT)
        CASE_RETURN_STRING(CL_INVALID_IMAGE_FORMAT_DESCRIPTOR)
        CASE_RETURN_STRING(CL_INVALID_IMAGE_SIZE)
        CASE_RETURN_STRING(CL_INVALID_SAMPLER)
        CASE_RETURN_STRING(CL_INVALID_BINARY)
        CASE_RETURN_STRING(CL_INVALID_BUILD_OPTIONS)
        CASE_RETURN_STRING(CL_INVALID_PROGRAM)
        CASE_RETURN_STRING(CL_INVALID_PROGRAM_EXECUTABLE)
        CASE_RETURN_STRING(CL_INVALID_KERNEL_NAME)
        CASE_RETURN_STRING(CL_INVALID_KERNEL_DEFINITION)
        CASE_RETURN_STRING(CL_INVALID_KERNEL)
        CASE_RETURN_STRING(CL_INVALID_ARG_INDEX)
        CASE_RETURN_STRING(CL_INVALID_ARG_VALUE)
        CASE_RETURN_STRING(CL_INVALID_ARG_SIZE)
        CASE_RETURN_STRING(CL_INVALID_KERNEL_ARGS)
        CASE_RETURN_STRING(CL_INVALID_WORK_DIMENSION)
        CASE_RETURN_STRING(CL_INVALID_WORK_GROUP_SIZE)
        CASE_RETURN_STRING(CL_INVALID_WORK_ITEM_SIZE)
        CASE_RETURN_STRING(CL_INVALID_GLOBAL_OFFSET)
        CASE_RETURN_STRING(CL_INVALID_EVENT_WAIT_LIST)
        CASE_RETURN_STRING(CL_INVALID_EVENT)
        CASE_RETURN_STRING(CL_INVALID_OPERATION)
        CASE_RETURN_STRING(CL_INVALID_GL_OBJECT)
        CASE_RETURN_STRING(CL_INVALID_BUFFER_SIZE)
        CASE_RETURN_STRING(CL_INVALID_MIP_LEVEL)
        CASE_RETURN_STRING(CL_INVALID_GLOBAL_WORK_SIZE)
        CASE_RETURN_STRING(CL_INVALID_PROPERTY)
        CASE_RETURN_STRING(CL_INVALID_IMAGE_DESCRIPTOR)
        CASE_RETURN_STRING(CL_INVALID_COMPILER_OPTIONS)
        CASE_RETURN_STRING(CL_INVALID_LINKER_OPTIONS)
        CASE_RETURN_STRING(CL_INVALID_DEVICE_PARTITION_COUNT)

        default: return NULL;
    }
}

static
const char*
opencl_build_status_string(
        cl_build_status err)
{
    switch (err)
    {
        CASE_RETURN_STRING(CL_BUILD_NONE)
        CASE_RETURN_STRING(CL_BUILD_ERROR)
        CASE_RETURN_STRING(CL_BUILD_SUCCESS)
        CASE_RETURN_STRING(CL_BUILD_IN_PROGRESS)

        default: return NULL;
    }
}

#undef CASE_RETURN_STRING

#define SEPARATOR "···············································································"

static
void
log_operation(
        const char *op,
        const char *file,

        cl_int error,
        bool add_build_log,
        FILE *stream,

        cl_program program,
        cl_uint num_devices,
        const cl_device_id *device_list)
{
    const char *code_str;

    if (add_build_log)
        fprintf(stream, SEPARATOR "\n");

    if (file != NULL)
        fprintf(stream, "%s(\"%s\"): ", op, file);
    else
        fprintf(stream, "%s(): ", op);

    code_str = opencl_error_string(error);
    if (code_str != NULL)
        fprintf(stream, "%s", code_str);
    else
        fprintf(stream, "code %i", error);

    if (!add_build_log)
    {
        fprintf(stream, "\n");
        return;
    }

    char *build_log = NULL;
    size_t build_log_length = 0;

    for (cl_uint i = 0; i < num_devices; i++)
    {
        cl_build_status status;
        size_t length;

        error = clGetProgramBuildInfo(program, device_list[i],
                CL_PROGRAM_BUILD_STATUS, sizeof(status), &status, NULL);
        if (error != CL_SUCCESS)
        {
            fprintf(stream, "\n[device #%u] couldn't obtain build status\n", i);
            continue;
        }

        fprintf(stream, "\n[device #%u] build status: ", i);
        code_str = opencl_build_status_string(status);
        if (code_str != NULL)
            fprintf(stream, "%s\n", code_str);
        else
            fprintf(stream, "code %i\n", status);

        error = clGetProgramBuildInfo(program, device_list[i],
                CL_PROGRAM_BUILD_LOG, 0, NULL, &length);
        if (error != CL_SUCCESS)
        {
            fprintf(stream, "Error: couldn't obtain build log length.");
            continue;
        }

        if (length > build_log_length)
        {
            char *new_build_log = realloc(build_log, length);
            if (!new_build_log)
            {
                fprintf(stream, "Error: realloc(build_log, %zu) returned NULL.", length);
                continue;
            }
            build_log = new_build_log;
            build_log_length = length;
        }

        if (length == 0)
            continue;

        error = clGetProgramBuildInfo(program, device_list[i],
                CL_PROGRAM_BUILD_LOG, length, build_log, NULL);
        if (error == CL_SUCCESS)
            fprintf(stream, "%s", build_log);
        else
            fprintf(stream, "Error: couldn't obtain build log.");
    }

    free(build_log);
}

cl_program
port_opencl_build_program(
        cl_context context,
        cl_uint num_devices,
        const cl_device_id *device_list,

        cl_uint num_inputs,
        const port_opencl_program_source_t *inputs[],

        cl_uint num_libraries,
        const cl_program libraries[],

        const char *cflags,
        const char *lflags,

        FILE *stream,
        cl_int *error)
{
    if (context == NULL)
    {
        if (stream != NULL)
            fprintf(stream, "Error: context is NULL.\n");
        if (error != NULL)
            *error = CL_INVALID_CONTEXT;
        return NULL;
    }
    else if ((num_devices == 0) || (device_list == NULL))
    {
        if (stream != NULL)
            fprintf(stream, "Error: device list is zero length or NULL.\n");
        if (error != NULL)
            *error = CL_INVALID_DEVICE;
        return NULL;
    }

    if (num_inputs == 0)
    {
        if (stream != NULL)
            fprintf(stream, "Error: number of input sets of sources is zero.\n");
        if (error != NULL)
            *error = CL_INVALID_VALUE;
        return NULL;
    }
    else if (inputs == NULL)
    {
        if (stream != NULL)
            fprintf(stream, "Error: array of pointers to input sets of sources is NULL.\n");
        if (error != NULL)
            *error = CL_INVALID_VALUE;
        return NULL;
    }

    if ((num_libraries > 0) && (libraries == NULL))
    {
        if (stream != NULL)
            fprintf(stream, "Error: array of libraries is NULL.\n");
        if (error != NULL)
            *error = CL_INVALID_VALUE;
        return NULL;
    }

    cl_uint num_headers = 0, num_sources = 0;

    for (cl_uint i = 0; i < num_inputs; i++)
    {
        if (inputs[i] == NULL)
        {
            if (stream != NULL)
                fprintf(stream, "Error: pointer to input sets of sources is NULL (set #%u).\n", i);
            if (error != NULL)
                *error = CL_INVALID_VALUE;
            return NULL;
        }

        num_headers += inputs[i]->header.num_files;
        num_sources += inputs[i]->source.num_files;

        if (inputs[i]->header.num_files > 0)
        {
            if (inputs[i]->header.file_paths == NULL)
            {
                if (stream != NULL)
                    fprintf(stream, "Error: array of header include names is NULL (set #%u).\n", i);
                if (error != NULL)
                    *error = CL_INVALID_VALUE;
                return NULL;
            }
            else if (inputs[i]->header.file_contents == NULL)
            {
                if (stream != NULL)
                    fprintf(stream, "Error: array of headers is NULL (set #%u).\n", i);
                if (error != NULL)
                    *error = CL_INVALID_VALUE;
                return NULL;
            }
            else if (inputs[i]->header.file_sizes == NULL)
            {
                if (stream != NULL)
                    fprintf(stream, "Error: array of header sizes is NULL (set #%u).\n", i);
                if (error != NULL)
                    *error = CL_INVALID_VALUE;
                return NULL;
            }
        }

        if (inputs[i]->source.num_files == 0)
        {
            if (stream != NULL)
                fprintf(stream, "Error: number of sources is zero (set #%u).\n", i);
            if (error != NULL)
                *error = CL_INVALID_VALUE;
            return NULL;
        }
        else if (inputs[i]->source.file_paths == NULL)
        {
            if (stream != NULL)
                fprintf(stream, "Error: array of source names is NULL (set #%u).\n", i);
            if (error != NULL)
                *error = CL_INVALID_VALUE;
            return NULL;
        }
        else if (inputs[i]->source.file_contents == NULL)
        {
            if (stream != NULL)
                fprintf(stream, "Error: array of sources is NULL (set #%u).\n", i);
            if (error != NULL)
                *error = CL_INVALID_VALUE;
            return NULL;
        }
        else if (inputs[i]->source.file_sizes == NULL)
        {
            if (stream != NULL)
                fprintf(stream, "Error: array of source sizes is NULL (set #%u).\n", i);
            if (error != NULL)
                *error = CL_INVALID_VALUE;
            return NULL;
        }
    }

    cl_int err;

    const char **header_include_names = NULL;
    cl_program *program_headers = NULL;
    cl_program *program_sources = NULL;
    cl_program program = NULL;

    // Create header programs
    if (num_headers > 0)
    {
        header_include_names = malloc(sizeof(*header_include_names) * num_headers);
        if (header_include_names == NULL)
        {
            if (stream != NULL)
                fprintf(stream, "Error: malloc() returned NULL\n");
            err = CL_OUT_OF_HOST_MEMORY;
            goto finish;
        }

        program_headers = malloc(sizeof(*program_headers) * num_headers);
        if (program_headers == NULL)
        {
            if (stream != NULL)
                fprintf(stream, "Error: malloc() returned NULL\n");
            err = CL_OUT_OF_HOST_MEMORY;
            goto finish;
        }

        for (cl_uint idx = 0; idx < num_headers; idx++)
            program_headers[idx] = NULL;

        cl_uint idx = 0;
        for (cl_uint i = 0; i < num_inputs; i++)
        {
            for (cl_uint j = 0; j < inputs[i]->header.num_files; j++)
            {
                header_include_names[idx] = inputs[i]->header.file_paths[j];
                program_headers[idx++] = clCreateProgramWithSource(context,
                        1, (const char**)&inputs[i]->header.file_contents[j], &inputs[i]->header.file_sizes[j], &err);

                if (stream != NULL)
                    log_operation("clCreateProgramWithSource", inputs[i]->header.file_paths[j],
                            err, false, stream, NULL, 0, NULL);

                if (err != CL_SUCCESS)
                    goto finish;
            }
        }
    }

    // Create source programs
    {
        program_sources = malloc(sizeof(*program_sources) * (num_sources + num_libraries));
        if (program_sources == NULL)
        {
            if (stream != NULL)
                fprintf(stream, "Error: malloc() returned NULL\n");
            err = CL_OUT_OF_HOST_MEMORY;
            goto finish;
        }

        for (cl_uint idx = 0; idx < num_sources; idx++)
            program_sources[idx] = NULL;

        for (cl_uint idx = 0; idx < num_libraries; idx++)
            program_sources[num_sources + idx] = libraries[idx];

        cl_uint idx = 0;
        for (cl_uint i = 0; i < num_inputs; i++)
        {
            for (cl_uint j = 0; j < inputs[i]->source.num_files; j++)
            {
                program_sources[idx++] = clCreateProgramWithSource(context,
                        1, (const char**)&inputs[i]->source.file_contents[j], &inputs[i]->source.file_sizes[j], &err);

                if (stream != NULL)
                    log_operation("clCreateProgramWithSource", inputs[i]->source.file_paths[j],
                            err, false, stream, NULL, 0, NULL);

                if (err != CL_SUCCESS)
                    goto finish;
            }
        }
    }

    // Compile programs
    {
        cl_uint idx = 0;
        for (cl_uint i = 0; i < num_inputs; i++)
        {
            for (cl_uint j = 0; j < inputs[i]->source.num_files; j++)
            {
                err = clCompileProgram(program_sources[idx], num_devices, device_list, cflags,
                        num_headers, program_headers, header_include_names, NULL, NULL);

                if (stream != NULL)
                    log_operation("clCompileProgram", inputs[i]->source.file_paths[j],
                            err, true, stream, program_sources[idx], num_devices, device_list);

                if (err != CL_SUCCESS)
                    goto finish;

                idx++;
            }
        }
    }

    // Link program
    program = clLinkProgram(context, num_devices, device_list, lflags,
            num_sources + num_libraries, program_sources, NULL, NULL, &err);

    if (stream != NULL)
        log_operation("clLinkProgram", NULL, err, true, stream, program, num_devices, device_list);

finish:
    if (header_include_names != NULL)
        free(header_include_names);

    if (program_headers != NULL)
    {
        for (cl_uint i = 0; i < num_headers; i++)
            if (program_headers[i] != NULL)
                clReleaseProgram(program_headers[i]);

        free(program_headers);
    }

    if (program_sources != NULL)
    {
        for (cl_uint i = 0; i < num_sources; i++)
            if (program_sources[i] != NULL)
                clReleaseProgram(program_sources[i]);

        free(program_sources);
    }

    if (error != NULL)
        *error = err;

    return program;
}

