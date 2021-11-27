/*
 * Copyright (c) 2021 Dmitry Lavygin <vdm.inbox@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     1. Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *
 *     2. Redistributions in binary form must reproduce the above copyright
 *        notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 *
 *     3. Neither the name of the copyright holder nor the names of its
 *        contributors may be used to endorse or promote products derived from
 *        this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */


#include <string.h>

#include "exlib/ex_strings.h"
#include "exlib/ex_safestr.h"


size_t ex_get_path(char* output, size_t osize, const char* spath)
{
    size_t size = ex_strlen(spath);
    while (size > 0)
    {
        size--;
        if (spath[size] == '\\' || spath[size] == '/')
        {
            size++;
            break;
        }
    }
    exs_strncpy(output, osize, spath, size);
    return ex_strlen(output);
}

size_t ex_get_filename(char* output, size_t osize, const char* spath)
{
    size_t size = ex_strlen(spath);
    while (size > 0)
    {
        size--;
        if (spath[size] == '\\' || spath[size] == '/')
        {
            size++;
            break;
        }
    }
    exs_strcpy(output, osize, &spath[size]);
    return ex_strlen(output);
}

size_t ex_get_basename(char* output, size_t osize, const char* spath)
{
    size_t dot  = 0;
    size_t size = ex_strlen(spath);
    while (size > 0)
    {
        size--;
        if (spath[size] == '\\' || spath[size] == '/')
        {
            size++;
            break;
        }
        else if (spath[size] == '.')
        {
            dot = size;
        }
    }

    if (dot >= size)
    {
        exs_strncpy(output, osize, &spath[size], dot - size);
    }
    else
    {
        exs_strcpy(output, osize, &spath[size]);
    }

    return ex_strlen(output);
}

size_t ex_get_suffix(char* output, size_t osize, const char* spath)
{
    size_t size = ex_strlen(spath);
    while (size > 0)
    {
        size--;
        if (spath[size] == '.')
        {
            exs_strcpy(output, osize, &spath[size]);
            return ex_strlen(output);
        }
        else if (spath[size] == '\\' || spath[size] == '/')
        {
            break;
        }
    }
    if (output != NULL && osize > 0)
        output[0] = '\0';

    return 0;
}

size_t ex_get_complete_suffix(char* output, size_t osize, const char* spath)
{
    size_t dot  = 0;
    size_t size = ex_strlen(spath);
    while (size > 0)
    {
        size--;
        if (spath[size] == '.')
        {
            dot = size;
        }
        else if (spath[size] == '\\' || spath[size] == '/')
        {
            size++;
            break;
        }
    }

    if (dot >= size)
    {
        exs_strcpy(output, osize, &spath[dot]);
        return ex_strlen(output);
    }

    if (output != NULL && osize > 0)
        output[0] = '\0';

    return 0;
}

size_t ex_keep_path(char* path)
{
    size_t size = ex_strlen(path);
    while (size > 0)
    {
        size--;
        if (path[size] == '\\' || path[size] == '/')
        {
            size++;
            break;
        }
    }
    if (path)
      path[size] = '\0';

    return size;
}

size_t ex_keep_filename(char* path)
{
    size_t size   = ex_strlen(path);
    size_t offset = size;
    while (offset > 0)
    {
        offset--;
        if (path[offset] == '\\' || path[offset] == '/')
        {
            offset++;
            break;
        }
    }
    if (path && offset > 0)
    {
        memmove(path, &path[offset], size - offset);
        path[size - offset] = '\0';
    }

    return (size - offset);
}

size_t ex_keep_basename(char* path)
{
    size_t index = 0;
    size_t size = ex_keep_filename(path);
    for (index = 0; index < size; ++index)
    {
        if (path[index] == '.')
            break;
    }
    if (path)
      path[index] = '\0';

    return index;
}

size_t ex_keep_suffix(char* path)
{
    size_t size   = ex_strlen(path);
    size_t offset = size;
    while (offset > 0)
    {
        offset--;
        if (path[offset] == '.')
        {
            memmove(path, &path[offset], size - offset);
            path[size - offset] = '\0';
            return (size - offset);
        }
        else if (path[offset] == '\\' || path[offset] == '/')
        {
            break;
        }
    }
    if (path && size > 0)
        path[0] = '\0';

    return 0;
}

size_t ex_keep_complete_suffix(char* path)
{
    size_t dot    = 0;
    size_t size   = ex_strlen(path);
    size_t offset = size;
    while (offset > 0)
    {
        offset--;
        if (path[offset] == '.')
        {
            dot = offset;
        }
        else if (path[offset] == '\\' || path[offset] == '/')
        {
            offset++;
            break;
        }
    }
    if (path)
    {
        if (dot >= offset)
        {
            memmove(path, &path[dot], size - dot);
            path[size - dot] = '\0';
            return (size - dot);
        }
        path[0] = '\0';
    }

    return 0;
}
