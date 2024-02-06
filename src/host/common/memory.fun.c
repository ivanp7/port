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
 * @brief Functions for memory operations.
 */

#include <port/host/common/memory.fun.h>

#ifdef PORT_FEATURE_SUPPORT_BFD
#  define PACKAGE
#  define PACKAGE_VERSION
#  include <bfd.h>
#  undef PACKAGE_VERSION
#  undef PACKAGE
#endif

void
port_memory_storage_destroy_section_list(
        port_memory_storage_section_t *section_list_head)
{
    for (port_memory_storage_section_t *section = section_list_head, *next_section;
            section != NULL; section = next_section)
    {
        next_section = section->next;

        free((char*)section->name);
        free(section);
    }
}

void
port_memory_storage_destroy_symbol_list(
        port_memory_storage_symbol_t *symbol_list_head)
{
    for (port_memory_storage_symbol_t *symbol = symbol_list_head, *next_symbol;
            symbol != NULL; symbol = next_symbol)
    {
        next_symbol = symbol->next;

        free((char*)symbol->name);
        free(symbol);
    }
}

///////////////////////////////////////////////////////////////////////////////
// BFD
///////////////////////////////////////////////////////////////////////////////

void
port_memory_storage_init_bfd(
        void)
{
#ifdef PORT_FEATURE_SUPPORT_BFD
    bfd_init();
#endif
}

port_void_ptr_t
port_memory_storage_open_bfd(
        port_bool_t for_writing,
        port_void_ptr_t stream,
        const char *filename,
        const char *target)
{
#ifndef PORT_FEATURE_SUPPORT_BFD
    (void) for_writing;
    (void) stream;
    (void) filename;
    (void) target;

    return NULL;
#else
    if (filename == NULL)
        return NULL;

    port_void_ptr_t bfd_storage;

    if (!for_writing)
    {
        if (stream != NULL)
            bfd_storage = bfd_openstreamr(filename, target, stream);
        else
            bfd_storage = bfd_openr(filename, target);

        if (bfd_storage == NULL)
            return NULL;

        if (!bfd_check_format(bfd_storage, bfd_object))
        {
            bfd_close_all_done(bfd_storage);
            return NULL;
        }
    }
    else // for writing
    {
        if (stream != NULL)
            return NULL; // there is no bfd_openstreamw()

        bfd_storage = bfd_openw(filename, target);
        if (bfd_storage == NULL)
            return NULL;

        if (!bfd_set_format(bfd_storage, bfd_object))
        {
            bfd_close_all_done(bfd_storage);
            return NULL;
        }

        if (!bfd_set_file_flags(bfd_storage, HAS_SYMS))
        {
            bfd_close_all_done(bfd_storage);
            return NULL;
        }
    }

    return bfd_storage;
#endif
}

port_bool_t
port_memory_storage_close_bfd(
        port_void_ptr_t bfd_storage,
        port_bool_t complete_operations)
{
#ifndef PORT_FEATURE_SUPPORT_BFD
    (void) bfd_storage;

    return false;
#else
    if (bfd_storage == NULL)
        return false;

    bfd *abfd = bfd_storage;

    asymbol **symbol_table = abfd->outsymbols;

    port_bool_t result;

    if (complete_operations)
        result = bfd_close(abfd);
    else
        result = bfd_close_all_done(abfd);

    if (result)
        free(symbol_table);

    return result;
#endif
}

port_bool_t
port_memory_storage_read_bfd(
        port_void_ptr_t bfd_storage,

        port_memory_storage_section_filter_func_t section_filter,
        port_memory_storage_symbol_filter_func_t symbol_filter,

        port_memory_storage_section_t **section_list_head,
        port_memory_storage_section_t **section_list_tail,
        port_size_t *num_sections,

        port_memory_storage_symbol_t **symbol_list_head,
        port_memory_storage_symbol_t **symbol_list_tail,
        port_size_t *num_symbols)
{
#ifndef PORT_FEATURE_SUPPORT_BFD
    (void) bfd_storage;
    (void) section_filter;
    (void) symbol_filter;
    (void) section_list_head;
    (void) num_sections;
    (void) symbol_list_head;
    (void) num_symbols;

    return false;
#else
    if (bfd_storage == NULL)
        return false;
    else if ((section_list_head == NULL) || (symbol_list_head == NULL))
        return false;

    bfd *abfd = bfd_storage;

    port_bool_t result = false;

    asymbol **symbol_table = NULL;
    long number_of_symbols = 0;

    port_memory_storage_section_t *section_first = NULL, *section_last = NULL;
    port_size_t section_list_size = 0;
    port_memory_storage_symbol_t *symbol_first = NULL, *symbol_last = NULL;
    port_size_t symbol_list_size = 0;

    // Read symbol table
    {
        long storage_needed = bfd_get_symtab_upper_bound(abfd);
        if (storage_needed < 0)
            goto cleanup;

        if (storage_needed > 0)
        {
            symbol_table = malloc(storage_needed);
            if (symbol_table == NULL)
                goto cleanup;

            number_of_symbols = bfd_canonicalize_symtab(abfd, symbol_table);
            if (number_of_symbols < 0)
                goto cleanup;
        }
    }

    // Read sections
    for (asection *sec = abfd->sections; sec != NULL; sec = sec->next)
    {
        if ((sec->flags & SEC_HAS_CONTENTS) == 0)
            continue; // section has no contents

        size_t size = bfd_get_section_limit_octets(abfd, sec);
        if ((size % sizeof(port_memory_unit_t) != 0) || (size == 0))
            continue; // section size is incorrect

        // Filter sections
        if ((section_filter != NULL) && !section_filter(sec->name))
            continue; // section is filtered out

        // Allocate
        port_memory_storage_section_t *section = malloc(sizeof(*section));
        if (section == NULL)
            goto cleanup;

        // Initialize fields
        section->name = malloc(strlen(sec->name) + 1);
        if (section->name == NULL)
        {
            free(section);
            goto cleanup;
        }
        strcpy((char*)section->name, sec->name);

        section->storage = sec;
        section->contents = NULL;
        section->size = size / sizeof(port_memory_unit_t);
        section->data = NULL;
        section->next = NULL;

        // Append to the list
        if (section_last != NULL)
        {
            section_last->next = section;
            section_last = section;
        }
        else if (section_first != NULL)
        {
            section_first->next = section;
            section_last = section;
        }
        else
            section_first = section;

        section_list_size++;
    }

    // Read symbols
    for (long i = 0; i < number_of_symbols; i++)
    {
        asymbol *sym = symbol_table[i];

        if ((sym->flags & BSF_GLOBAL) == 0)
            continue; // not exported data
        else if ((sym->value % sizeof(port_memory_unit_t) != 0) ||
                (sym->value >= bfd_get_section_limit_octets(abfd, sym->section)))
            continue; // symbol value is incorrect

        // Filter
        if ((symbol_filter != NULL) && !symbol_filter(sym->name, sym->section->name))
            continue; // symbol is filtered out

        // Find owner section
        port_memory_storage_section_t *section;
        for (section = section_first; section != NULL; section = section->next)
            if (section->storage == sym->section)
                break;

        if (section == NULL)
            continue; // section is filtered out

        // Allocate
        port_memory_storage_symbol_t *symbol = malloc(sizeof(*symbol));
        if (symbol == NULL)
            goto cleanup;

        // Initialize fields
        symbol->name = malloc(strlen(sym->name) + 1);
        if (symbol->name == NULL)
        {
            free(symbol);
            goto cleanup;
        }
        strcpy((char*)symbol->name, sym->name);

        symbol->section = section;
        symbol->offset = sym->value / sizeof(port_memory_unit_t);
        symbol->data = NULL;
        symbol->next = NULL;

        // Append to the list
        if (symbol_last != NULL)
        {
            symbol_last->next = symbol;
            symbol_last = symbol;
        }
        else if (symbol_first != NULL)
        {
            symbol_first->next = symbol;
            symbol_last = symbol;
        }
        else
            symbol_first = symbol;

        symbol_list_size++;
    }

    // Set output parameters
    *section_list_head = section_first;

    if (section_list_tail != NULL)
        *section_list_tail = (section_last != NULL) ? section_last : section_first;

    if (num_sections != NULL)
        *num_sections = section_list_size;

    *symbol_list_head = symbol_first;

    if (symbol_list_tail != NULL)
        *symbol_list_tail = (symbol_last != NULL) ? symbol_last : symbol_first;

    if (num_symbols != NULL)
        *num_symbols = symbol_list_size;

    result = true;

cleanup:
    free(symbol_table);

    if (!result)
    {
        port_memory_storage_destroy_section_list(section_first);
        port_memory_storage_destroy_symbol_list(symbol_first);
    }

    return result;
#endif
}

port_bool_t
port_memory_storage_write_bfd(
        port_void_ptr_t bfd_storage,

        port_memory_storage_section_t *section_list_head,
        port_memory_storage_symbol_t *symbol_list_head)
{
#ifndef PORT_FEATURE_SUPPORT_BFD
    (void) bfd_storage;
    (void) section_list_head;
    (void) symbol_list_head;

    return false;
#else
    if (bfd_storage == NULL)
        return false;

    bfd *abfd = bfd_storage;

    // Write sections
    for (port_memory_storage_section_t *section = section_list_head;
            section != NULL; section = section->next)
    {
        asection *bfd_section = bfd_make_section_anyway_with_flags(
                abfd, section->name, SEC_HAS_CONTENTS | SEC_DATA);
        if (bfd_section == NULL)
            return false;

        if (!bfd_set_section_size(bfd_section,
                    section->size * sizeof(port_memory_unit_t)))
            return false;

        section->storage = bfd_section;
    }

    for (port_memory_storage_section_t *section = section_list_head;
            section != NULL; section = section->next)
    {
        asection *bfd_section = section->storage;

        if (!bfd_set_section_contents(abfd, bfd_section, section->contents,
                    0, section->size * sizeof(port_memory_unit_t)))
            return false;
    }

    // Count symbols in the list
    unsigned int num_symbols = 0;

    for (port_memory_storage_symbol_t *symbol = symbol_list_head;
            symbol != NULL; symbol = symbol->next)
        num_symbols++;

    // Write symbol table
    if (num_symbols > 0)
    {
        asymbol **symbol_table = malloc(sizeof(*symbol_table) * (num_symbols + 1));
        if (symbol_table == NULL)
            return false;

        symbol_table[num_symbols] = NULL;

        unsigned int i = 0;
        for (port_memory_storage_symbol_t *symbol = symbol_list_head;
                symbol != NULL; symbol = symbol->next)
        {
            asymbol *sym = bfd_make_empty_symbol(abfd);
            if (sym == NULL)
            {
                free(symbol_table);
                return false;
            }

            sym->name = symbol->name;
            sym->section = symbol->section->storage;
            sym->flags = BSF_GLOBAL;
            sym->value = symbol->offset * sizeof(port_memory_unit_t);

            symbol_table[i++] = sym;
        }

        if (!bfd_set_symtab(abfd, symbol_table, num_symbols))
        {
            free(symbol_table);
            return false;
        }
    }

    return true;
#endif
}

port_bool_t
port_memory_storage_section_contents_bfd(
        port_memory_storage_section_t *section,
        port_size_t offset,
        port_size_t size,

        port_memory_ptr_t memory)
{
#ifndef PORT_FEATURE_SUPPORT_BFD
    (void) section;
    (void) offset;
    (void) size;
    (void) memory;

    return false;
#else
    if ((section == NULL) || (offset + size > section->size) || (memory == NULL))
        return false;
    else if (section->storage == NULL)
        return false;

    asection *bfd_section = section->storage;

    return bfd_get_section_contents(bfd_section->owner, bfd_section, memory,
            offset * sizeof(port_memory_unit_t), size * sizeof(port_memory_unit_t));
#endif
}

