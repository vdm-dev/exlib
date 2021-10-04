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
#include <limits.h>

#include "exlib/ex_safestr.h"


#define EXS_HEXSTR_TO_ANY(__type)                                \
    __type  result = 0;                                          \
    size_t  index = 0;                                           \
    if (ok)                                                      \
    {                                                            \
        *ok = false;                                             \
    }                                                            \
    if (string == NULL || size < 1 || size > sizeof(result) * 2) \
    {                                                            \
        return 0;                                                \
    }                                                            \
    for (index = 0; index < size; ++index)                       \
    {                                                            \
        result <<= 4;                                            \
        if (string[index] >= '0' && string[index] <= '9')        \
        {                                                        \
            result |= (__type) (string[index] - '0');            \
        }                                                        \
        else if (string[index] >= 'a' && string[index] <= 'f')   \
        {                                                        \
            result |= (__type) (string[index] - 'a' + 10);       \
        }                                                        \
        else if (string[index] >= 'A' && string[index] <= 'F')   \
        {                                                        \
            result |= (__type) (string[index] - 'A' + 10);       \
        }                                                        \
        else                                                     \
        {                                                        \
            return 0;                                            \
        }                                                        \
    }                                                            \
    if (ok)                                                      \
    {                                                            \
        *ok = true;                                              \
    }                                                            \
    return result;                                               \


/* Signed Fixed Size */
int8_t exs_hexstr_to_i8(char* string, size_t size, bool* ok)
{
    return (int8_t) exs_hexstr_to_u8(string, size, ok);
}

int16_t exs_hexstr_to_i16(char* string, size_t size, bool* ok)
{
    return (int16_t) exs_hexstr_to_u16(string, size, ok);
}

int32_t exs_hexstr_to_i32(char* string, size_t size, bool* ok)
{
    return (int32_t) exs_hexstr_to_u32(string, size, ok);
}

int64_t exs_hexstr_to_i64(char* string, size_t size, bool* ok)
{
    return (int64_t) exs_hexstr_to_u64(string, size, ok);
}


/* Signed Platform Dependent Size */
short exs_hexstr_to_short(char* string, size_t size, bool* ok)
{
    return (short) exs_hexstr_to_ushort(string, size, ok);
}

int exs_hexstr_to_int(char* string, size_t size, bool* ok)
{
    return (int) exs_hexstr_to_uint(string, size, ok);
}

long exs_hexstr_to_long(char* string, size_t size, bool* ok)
{
    return (long) exs_hexstr_to_ulong(string, size, ok);
}


/* Unsigned Fixed Size */
uint8_t exs_hexstr_to_u8(char* string, size_t size, bool* ok)
{
    EXS_HEXSTR_TO_ANY(uint8_t)
}

uint16_t exs_hexstr_to_u16(char* string, size_t size, bool* ok)
{
    EXS_HEXSTR_TO_ANY(uint16_t)
}

uint32_t exs_hexstr_to_u32(char* string, size_t size, bool* ok)
{
    EXS_HEXSTR_TO_ANY(uint32_t)
}

uint64_t exs_hexstr_to_u64(char* string, size_t size, bool* ok)
{
    EXS_HEXSTR_TO_ANY(uint64_t)
}


/* Unsigned Platform Dependent Size */
unsigned short exs_hexstr_to_ushort(char* string, size_t size, bool* ok)
{
    EXS_HEXSTR_TO_ANY(unsigned short)
}

unsigned int exs_hexstr_to_uint(char* string, size_t size, bool* ok)
{
    EXS_HEXSTR_TO_ANY(unsigned int)
}

unsigned long exs_hexstr_to_ulong(char* string, size_t size, bool* ok)
{
    EXS_HEXSTR_TO_ANY(unsigned long)
}
