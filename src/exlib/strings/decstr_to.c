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

#include "exlib/ex_strings.h"


#define EX_DECSTR_TO_SIGNED(__type, __min, __max)              \
    __type result = 0;                                         \
    int8_t check = 0;                                          \
    size_t index = 0;                                          \
    size_t size = 0;                                           \
    bool negative = false;                                     \
    if (ok)                                                    \
    {                                                          \
        *ok = false;                                           \
    }                                                          \
    size = ex_strlen(string);                                  \
    if (size == 0)                                             \
    {                                                          \
        return 0;                                              \
    }                                                          \
    for (index = 0; index < size; ++index)                     \
    {                                                          \
        if (string[index] == '-')                              \
        {                                                      \
            if (index > 0 || negative)                         \
            {                                                  \
                return 0;                                      \
            }                                                  \
            else                                               \
            {                                                  \
                negative = true;                               \
            }                                                  \
        }                                                      \
        else if (string[index] >= '0' && string[index] <= '9') \
        {                                                      \
            result *= 10;                                      \
            check = string[index] - '0';                       \
            if (negative)                                      \
            {                                                  \
                check = -check;                                \
                if ((__min - result) > check)                  \
                {                                              \
                    return 0;                                  \
                }                                              \
            }                                                  \
            else                                               \
            {                                                  \
                if ((__max - result) < check)                  \
                {                                              \
                    return 0;                                  \
                }                                              \
            }                                                  \
            result += check;                                   \
        }                                                      \
        else                                                   \
        {                                                      \
            return 0;                                          \
        }                                                      \
    }                                                          \
    if (ok)                                                    \
    {                                                          \
        *ok = true;                                            \
    }                                                          \
    return result;                                             \


#define EX_DECSTR_TO_UNSIGNED(__type, __max)                   \
    __type  result = 0;                                        \
    uint8_t check = 0;                                         \
    size_t  index = 0;                                         \
    size_t  size = 0;                                          \
    if (ok)                                                    \
    {                                                          \
        *ok = false;                                           \
    }                                                          \
    size = ex_strlen(string);                                  \
    if (size == 0)                                             \
    {                                                          \
        return 0;                                              \
    }                                                          \
    for (index = 0; index < size; ++index)                     \
    {                                                          \
        if (string[index] >= '0' && string[index] <= '9')      \
        {                                                      \
            result *= 10;                                      \
            check = (uint8_t) (string[index] - '0');           \
            if ((__max - result) < check)                      \
            {                                                  \
                return 0;                                      \
            }                                                  \
            result += check;                                   \
        }                                                      \
        else                                                   \
        {                                                      \
            return 0;                                          \
        }                                                      \
    }                                                          \
    if (ok)                                                    \
    {                                                          \
        *ok = true;                                            \
    }                                                          \
    return result;                                             \


/* Signed Fixed Size */
int8_t ex_decstr_to_i8(char* string, bool* ok)
{
    EX_DECSTR_TO_SIGNED(int8_t, INT8_MIN, INT8_MAX)
}

int16_t ex_decstr_to_i16(char* string, bool* ok)
{
    EX_DECSTR_TO_SIGNED(int16_t, INT16_MIN, INT16_MAX)
}

int32_t ex_decstr_to_i32(char* string, bool* ok)
{
    EX_DECSTR_TO_SIGNED(int32_t, INT32_MIN, INT32_MAX)
}

int64_t ex_decstr_to_i64(char* string, bool* ok)
{
    EX_DECSTR_TO_SIGNED(int64_t, INT64_MIN, INT64_MAX)
}


/* Signed Platform Dependent Size */
short ex_decstr_to_short(char* string, bool* ok)
{
    EX_DECSTR_TO_SIGNED(short, SHRT_MIN, SHRT_MAX)
}

int ex_decstr_to_int(char* string, bool* ok)
{
    EX_DECSTR_TO_SIGNED(int, INT_MIN, INT_MAX)
}

long ex_decstr_to_long(char* string, bool* ok)
{
    EX_DECSTR_TO_SIGNED(long, LONG_MIN, LONG_MAX)
}


/* Unsigned Fixed Size */
uint8_t ex_decstr_to_u8(char* string, bool* ok)
{
    EX_DECSTR_TO_UNSIGNED(uint8_t, UINT8_MAX)
}

uint16_t ex_decstr_to_u16(char* string, bool* ok)
{
    EX_DECSTR_TO_UNSIGNED(uint16_t, UINT16_MAX)
}

uint32_t ex_decstr_to_u32(char* string, bool* ok)
{
    EX_DECSTR_TO_UNSIGNED(uint32_t, UINT32_MAX)
}

uint64_t ex_decstr_to_u64(char* string, bool* ok)
{
    EX_DECSTR_TO_UNSIGNED(uint64_t, UINT64_MAX)
}


/* Unsigned Platform Dependent Size */
unsigned short ex_decstr_to_ushort(char* string, bool* ok)
{
    EX_DECSTR_TO_UNSIGNED(unsigned short, USHRT_MAX)
}

unsigned int ex_decstr_to_uint(char* string, bool* ok)
{
    EX_DECSTR_TO_UNSIGNED(unsigned int, UINT_MAX)
}

unsigned long ex_decstr_to_ulong(char* string, bool* ok)
{
    EX_DECSTR_TO_UNSIGNED(unsigned long, ULONG_MAX)
}
