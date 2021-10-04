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


#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif /* _MSC_VER */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
#include <setjmp.h>

#include <exlib/ex_strings.h>


#define TEST_STR(string) #string
#define TEST_XSTR(string) TEST_STR(string)


#define TEST_SIGNED(__stage, __func, __var, __value)                 \
    memset(buffer, 'z', buffer_size);                                \
    sprintf(buffer, "%d", __value);                                  \
    __var = __func(buffer, &ok);                                     \
    if (__var != __value || ok == false)                             \
    {                                                                \
        fprintf(stderr,                                              \
            "%s: failed conversion (%s), expected %d, got %d\n",     \
            TEST_STR(__func), __stage, __value, __var);              \
        failures++;                                                  \
    }                                                                \

#define TEST_SIGNED64(__stage, __func, __var, __value)               \
    memset(buffer, 'z', buffer_size);                                \
    sprintf(buffer, "%lld", __value);                                \
    __var = __func(buffer, &ok);                                     \
    if (__var != __value || ok == false)                             \
    {                                                                \
        fprintf(stderr,                                              \
            "%s: failed conversion (%s), expected %lld, got %lld\n", \
            TEST_STR(__func), __stage, __value, __var);              \
        failures++;                                                  \
    }                                                                \

#define TEST_SIGNED_LNG(__stage, __func, __var, __value)             \
    memset(buffer, 'z', buffer_size);                                \
    sprintf(buffer, "%ld", __value);                                 \
    __var = __func(buffer, &ok);                                     \
    if (__var != __value || ok == false)                             \
    {                                                                \
        fprintf(stderr,                                              \
            "%s: failed conversion (%s), expected %ld, got %ld\n",   \
            TEST_STR(__func), __stage, __value, __var);              \
        failures++;                                                  \
    }                                                                \


#define TEST_UNSIGNED(__stage, __func, __var, __value)               \
    memset(buffer, 'z', buffer_size);                                \
    sprintf(buffer, "%u", __value);                                  \
    __var = __func(buffer, &ok);                                     \
    if (__var != __value || ok == false)                             \
    {                                                                \
        fprintf(stderr,                                              \
            "%s: failed conversion (%s), expected %u, got %u\n",     \
            TEST_STR(__func), __stage, __value, __var);              \
        failures++;                                                  \
    }                                                                \

#define TEST_UNSIGNED64(__stage, __func, __var, __value)             \
    memset(buffer, 'z', buffer_size);                                \
    sprintf(buffer, "%llu", __value);                                \
    __var = __func(buffer, &ok);                                     \
    if (__var != __value || ok == false)                             \
    {                                                                \
        fprintf(stderr,                                              \
            "%s: failed conversion (%s), expected %llu, got %llu\n", \
            TEST_STR(__func), __stage, __value, __var);              \
        failures++;                                                  \
    }                                                                \

#define TEST_UNSIGNED_LNG(__stage, __func, __var, __value)           \
    memset(buffer, 'z', buffer_size);                                \
    sprintf(buffer, "%lu", __value);                                 \
    __var = __func(buffer, &ok);                                     \
    if (__var != __value || ok == false)                             \
    {                                                                \
        fprintf(stderr,                                              \
            "%s: failed conversion (%s), expected %lu, got %lu\n",   \
            TEST_STR(__func), __stage, __value, __var);              \
        failures++;                                                  \
    }                                                                \


int main(void)
{
    char*          buffer = NULL;
    size_t         buffer_size = 4096;
    volatile int   failures = 0;

    int8_t         ivalue8 = 0;
    int16_t        ivalue16 = 0;
    int32_t        ivalue32 = 0;
    int64_t        ivalue64 = 0;
    short          s_short = 0;
    int            s_int   = 0;
    long           s_long  = 0;
    uint8_t        uvalue8 = 0;
    uint16_t       uvalue16 = 0;
    uint32_t       uvalue32 = 0;
    uint64_t       uvalue64 = 0;
    unsigned short u_short = 0;
    unsigned int   u_int   = 0;
    unsigned long  u_long  = 0;

    bool           ok = false;

    buffer = malloc(buffer_size);

    if (buffer == NULL)
    {
        fprintf(stderr, "unable to allocate memory\n");
        return 1;
    }

    /* Test: ex_decstr_to_i8 */
    TEST_SIGNED("1a", ex_decstr_to_i8, ivalue8, INT8_MIN);
    TEST_SIGNED("2a", ex_decstr_to_i8, ivalue8, INT8_MIN / 2);
    TEST_SIGNED("3a", ex_decstr_to_i8, ivalue8, 0);
    TEST_SIGNED("4a", ex_decstr_to_i8, ivalue8, INT8_MAX / 2);
    TEST_SIGNED("5a", ex_decstr_to_i8, ivalue8, INT8_MAX);

    /* Test: ex_decstr_to_i16 */
    TEST_SIGNED("6a", ex_decstr_to_i16, ivalue16, INT16_MIN);
    TEST_SIGNED("7a", ex_decstr_to_i16, ivalue16, INT16_MIN / 2);
    TEST_SIGNED("8a", ex_decstr_to_i16, ivalue16, 0);
    TEST_SIGNED("9a", ex_decstr_to_i16, ivalue16, INT16_MAX / 2);
    TEST_SIGNED("10a", ex_decstr_to_i16, ivalue16, INT16_MAX);

    /* Test: ex_decstr_to_i32 */
    TEST_SIGNED("11a", ex_decstr_to_i32, ivalue32, INT32_MIN);
    TEST_SIGNED("12a", ex_decstr_to_i32, ivalue32, INT32_MIN / 2);
    TEST_SIGNED("13a", ex_decstr_to_i32, ivalue32, 0);
    TEST_SIGNED("14a", ex_decstr_to_i32, ivalue32, INT32_MAX / 2);
    TEST_SIGNED("15a", ex_decstr_to_i32, ivalue32, INT32_MAX);

    /* Test: ex_decstr_to_i64 */
    TEST_SIGNED64("16a", ex_decstr_to_i64, ivalue64, INT64_MIN);
    TEST_SIGNED64("17a", ex_decstr_to_i64, ivalue64, INT64_MIN / 2);
    TEST_SIGNED64("18a", ex_decstr_to_i64, ivalue64, ((int64_t) 0));
    TEST_SIGNED64("19a", ex_decstr_to_i64, ivalue64, INT64_MAX / 2);
    TEST_SIGNED64("20a", ex_decstr_to_i64, ivalue64, INT64_MAX);

    /* Test: ex_decstr_to_short */
    TEST_SIGNED("21a", ex_decstr_to_short, s_short, SHRT_MIN);
    TEST_SIGNED("22a", ex_decstr_to_short, s_short, SHRT_MIN / 2);
    TEST_SIGNED("23a", ex_decstr_to_short, s_short, 0);
    TEST_SIGNED("24a", ex_decstr_to_short, s_short, SHRT_MAX / 2);
    TEST_SIGNED("25a", ex_decstr_to_short, s_short, SHRT_MAX);

    /* Test: ex_decstr_to_int */
    TEST_SIGNED("26a", ex_decstr_to_int, s_int, INT_MIN);
    TEST_SIGNED("27a", ex_decstr_to_int, s_int, INT_MIN / 2);
    TEST_SIGNED("28a", ex_decstr_to_int, s_int, 0);
    TEST_SIGNED("29a", ex_decstr_to_int, s_int, INT_MAX / 2);
    TEST_SIGNED("30a", ex_decstr_to_int, s_int, INT_MAX);

    /* Test: ex_decstr_to_long */
    TEST_SIGNED_LNG("31a", ex_decstr_to_long, s_long, LONG_MIN);
    TEST_SIGNED_LNG("32a", ex_decstr_to_long, s_long, LONG_MIN / 2);
    TEST_SIGNED_LNG("33a", ex_decstr_to_long, s_long, ((long) 0));
    TEST_SIGNED_LNG("34a", ex_decstr_to_long, s_long, LONG_MAX / 2);
    TEST_SIGNED_LNG("35a", ex_decstr_to_long, s_long, LONG_MAX);


    /* Test: ex_decstr_to_u8 */
    TEST_UNSIGNED("36a", ex_decstr_to_u8, uvalue8, 0);
    TEST_UNSIGNED("37a", ex_decstr_to_u8, uvalue8, UINT8_MAX / 2);
    TEST_UNSIGNED("38a", ex_decstr_to_u8, uvalue8, UINT8_MAX);

    /* Test: ex_decstr_to_u16 */
    TEST_UNSIGNED("39a", ex_decstr_to_u16, uvalue16, 0);
    TEST_UNSIGNED("40a", ex_decstr_to_u16, uvalue16, UINT16_MAX / 2);
    TEST_UNSIGNED("41a", ex_decstr_to_u16, uvalue16, UINT16_MAX);

    /* Test: ex_decstr_to_u32 */
    TEST_UNSIGNED("42a", ex_decstr_to_u32, uvalue32, 0);
    TEST_UNSIGNED("43a", ex_decstr_to_u32, uvalue32, UINT32_MAX / 2);
    TEST_UNSIGNED("44a", ex_decstr_to_u32, uvalue32, UINT32_MAX);

    /* Test: ex_decstr_to_u64 */
    TEST_UNSIGNED64("45a", ex_decstr_to_u64, uvalue64, ((uint64_t) 0));
    TEST_UNSIGNED64("46a", ex_decstr_to_u64, uvalue64, UINT64_MAX / 2);
    TEST_UNSIGNED64("47a", ex_decstr_to_u64, uvalue64, UINT64_MAX);

    /* Test: ex_decstr_to_short */
    TEST_UNSIGNED("48a", ex_decstr_to_ushort, u_short, 0);
    TEST_UNSIGNED("49a", ex_decstr_to_ushort, u_short, USHRT_MAX / 2);
    TEST_UNSIGNED("50a", ex_decstr_to_ushort, u_short, USHRT_MAX);

    /* Test: ex_decstr_to_uint */
    TEST_UNSIGNED("51a", ex_decstr_to_uint, u_int, 0);
    TEST_UNSIGNED("52a", ex_decstr_to_uint, u_int, UINT_MAX / 2);
    TEST_UNSIGNED("53a", ex_decstr_to_uint, u_int, UINT_MAX);

    /* Test: ex_decstr_to_ulong */
    TEST_UNSIGNED_LNG("54a", ex_decstr_to_ulong, u_long, ((unsigned long) 0));
    TEST_UNSIGNED_LNG("55a", ex_decstr_to_ulong, u_long, ULONG_MAX / 2);
    TEST_UNSIGNED_LNG("56a", ex_decstr_to_ulong, u_long, ULONG_MAX);

    return failures;
}
