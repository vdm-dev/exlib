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


#ifndef EX_STRINGS_H_INCLUDED
#define EX_STRINGS_H_INCLUDED


#include <exlib/ex_types.h>


/* base.c */
size_t ex_strlcpy(char* destination, const char* source, size_t dsize);
size_t ex_strlcat(char* destination, const char* source, size_t dsize);
void* ex_memrev(void* pointer, size_t size);

/* substrings.c */
const char* ex_str_skip(const char* string, char character);

/* decstr_from.c */
void ex_decstr_from_i8(char* result, int8_t value);
void ex_decstr_from_i16(char* result, int16_t value);
void ex_decstr_from_i32(char* result, int32_t value);
void ex_decstr_from_i64(char* result, int64_t value);

void ex_decstr_from_short(char* result, short value);
void ex_decstr_from_int(char* result, int value);
void ex_decstr_from_long(char* result, long value);

void ex_decstr_from_u8(char* result, uint8_t value);
void ex_decstr_from_u16(char* result, uint16_t value);
void ex_decstr_from_u32(char* result, uint32_t value);
void ex_decstr_from_u64(char* result, uint64_t value);

void ex_decstr_from_ushort(char* result, unsigned short value);
void ex_decstr_from_uint(char* result, unsigned int value);
void ex_decstr_from_ulong(char* result, unsigned long value);


#endif /* EX_STRINGS_H_INCLUDED */
