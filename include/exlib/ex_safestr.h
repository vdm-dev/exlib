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


#ifndef EX_SAFESTR_H_INCLUDED
#define EX_SAFESTR_H_INCLUDED


#include <exlib/ex_types.h>


#define EX_STR_NULL      0
#define EX_STR_NOSPACES  1
#define EX_STR_LOWERCASE 2
#define EX_STR_NOZERO    4


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* safe_base.c */
int exs_strcpy(char* destination, size_t dmax, const char* source);
int exs_strcat(char* destination, size_t dmax, const char* source);

/* safe_dump.c */
bool exs_hexstr_from_buffer(const void* data, size_t dsize, char* output,
    size_t osize, uint32_t options);

/* safe_decstr_to.c */
int8_t exs_decstr_to_i8(char* string, size_t size, bool* ok);
int16_t exs_decstr_to_i16(char* string, size_t size, bool* ok);
int32_t exs_decstr_to_i32(char* string, size_t size, bool* ok);
int64_t exs_decstr_to_i64(char* string, size_t size, bool* ok);

short exs_decstr_to_short(char* string, size_t size, bool* ok);
int exs_decstr_to_int(char* string, size_t size, bool* ok);
long exs_decstr_to_long(char* string, size_t size, bool* ok);

uint8_t exs_decstr_to_u8(char* string, size_t size, bool* ok);
uint16_t exs_decstr_to_u16(char* string, size_t size, bool* ok);
uint32_t exs_decstr_to_u32(char* string, size_t size, bool* ok);
uint64_t exs_decstr_to_u64(char* string, size_t size, bool* ok);

unsigned short exs_decstr_to_ushort(char* string, size_t size, bool* ok);
unsigned int exs_decstr_to_uint(char* string, size_t size, bool* ok);
unsigned long exs_decstr_to_ulong(char* string, size_t size, bool* ok);


/* safe_hexstr_to.c */
int8_t exs_hexstr_to_i8(char* string, size_t size, bool* ok);
int16_t exs_hexstr_to_i16(char* string, size_t size, bool* ok);
int32_t exs_hexstr_to_i32(char* string, size_t size, bool* ok);
int64_t exs_hexstr_to_i64(char* string, size_t size, bool* ok);

short exs_hexstr_to_short(char* string, size_t size, bool* ok);
int exs_hexstr_to_int(char* string, size_t size, bool* ok);
long exs_hexstr_to_long(char* string, size_t size, bool* ok);

uint8_t exs_hexstr_to_u8(char* string, size_t size, bool* ok);
uint16_t exs_hexstr_to_u16(char* string, size_t size, bool* ok);
uint32_t exs_hexstr_to_u32(char* string, size_t size, bool* ok);
uint64_t exs_hexstr_to_u64(char* string, size_t size, bool* ok);

unsigned short exs_hexstr_to_ushort(char* string, size_t size, bool* ok);
unsigned int exs_hexstr_to_uint(char* string, size_t size, bool* ok);
unsigned long exs_hexstr_to_ulong(char* string, size_t size, bool* ok);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* EX_SAFESTR_H_INCLUDED */
