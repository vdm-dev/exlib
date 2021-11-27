/*
 * Copyright (c) 1998, 2015 Todd C. Miller <millert@openbsd.org>
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


size_t ex_strlcpy(char* destination, const char* source, size_t dsize)
{
    size_t result = 0;

    while (source[result] != '\0')
    {
        if (result < dsize)
            destination[result] = source[result];

        result++;
    }

    if (result < dsize)
    {
        destination[result] = '\0';
    }
    else if (dsize > 0)
    {
        destination[dsize - 1] = '\0';
    }

    return result;
}

size_t ex_strlcat(char* destination, const char* source, size_t dsize)
{
    size_t result = 0;
    size_t offset = 0;

    while (result < dsize && destination[result] != '\0')
        result++;

    if (result >= dsize)
        return result + strlen(source);

    while (source[offset] != '\0')
    {
        if (result < dsize)
            destination[result] = source[offset];

        result++;
        offset++;
    }

    if (result < dsize)
    {
        destination[result] = '\0';
    }
    else if (dsize > 0)
    {
        destination[dsize - 1] = '\0';
    }

    return result;
}

size_t ex_strlen(const char* str)
{
    return str ? strlen(str) : 0;
}

size_t ex_strnlen(const char* string, size_t limit)
{
    size_t result = 0;
    while (string != NULL && string[result] != '\0' && result < limit)
    {
        result++;
    }
    return result;
}

void* ex_memrev(void* pointer, size_t size)
{
    size_t   index = 0;
    uint8_t  data = 0;
    uint8_t* result = (uint8_t*) pointer;

    for (index = 0; index < (size / 2); ++index)
    {
        data = result[index];
        result[index] = result[size - index - 1];
        result[size - index - 1] = data;
    }

    return result;
}
