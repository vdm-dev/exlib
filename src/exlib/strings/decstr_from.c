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


#define EX_DECSTR_FROM_SIGNED()       \
    int8_t digit = 0;                 \
    size_t size = 0;                  \
    bool   negative = (value < 0);    \
    do                                \
    {                                 \
        digit = (value % 10);         \
        if (digit < 0)                \
        {                             \
            digit = -digit;           \
        }                             \
        result[size++] = digit + '0'; \
        value /= 10;                  \
    } while (value != 0);             \
    if (negative)                     \
    {                                 \
        result[size++] = '-';         \
    }                                 \
    result[size] = '\0';              \
    ex_memrev(result, size);          \

#define EX_DECSTR_FROM_UNSIGNED()     \
    int8_t digit = 0;                 \
    size_t size = 0;                  \
    do                                \
    {                                 \
        digit = (value % 10);         \
        result[size++] = digit + '0'; \
        value /= 10;                  \
    } while (value != 0);             \
    result[size] = '\0';              \
    ex_memrev(result, size);          \


/* Signed Fixed Size */
void ex_decstr_from_i8(char* result, int8_t value)
{
    EX_DECSTR_FROM_SIGNED()
}

void ex_decstr_from_i16(char* result, int16_t value)
{
    EX_DECSTR_FROM_SIGNED()
}

void ex_decstr_from_i32(char* result, int32_t value)
{
    EX_DECSTR_FROM_SIGNED()
}

void ex_decstr_from_i64(char* result, int64_t value)
{
    EX_DECSTR_FROM_SIGNED()
}


/* Signed Platform Dependent Size */
void ex_decstr_from_short(char* result, short value)
{
    EX_DECSTR_FROM_SIGNED()
}

void ex_decstr_from_int(char* result, int value)
{
    EX_DECSTR_FROM_SIGNED()
}

void ex_decstr_from_long(char* result, long value)
{
    EX_DECSTR_FROM_SIGNED()
}


/* Unsigned Fixed Size */
void ex_decstr_from_u8(char* result, uint8_t value)
{
    EX_DECSTR_FROM_UNSIGNED()
}

void ex_decstr_from_u16(char* result, uint16_t value)
{
    EX_DECSTR_FROM_UNSIGNED()
}

void ex_decstr_from_u32(char* result, uint32_t value)
{
    EX_DECSTR_FROM_UNSIGNED()
}

void ex_decstr_from_u64(char* result, uint64_t value)
{
    EX_DECSTR_FROM_UNSIGNED()
}


/* Unsigned Platform Dependent Size */
void ex_decstr_from_ushort(char* result, unsigned short value)
{
    EX_DECSTR_FROM_UNSIGNED()
}

void ex_decstr_from_uint(char* result, unsigned int value)
{
    EX_DECSTR_FROM_UNSIGNED()
}

void ex_decstr_from_ulong(char* result, unsigned long value)
{
    EX_DECSTR_FROM_UNSIGNED()
}
