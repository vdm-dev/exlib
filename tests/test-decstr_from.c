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
#include <setjmp.h>

#include <exlib/ex_strings.h>


#define TEST_STR(string) #string
#define TEST_XSTR(string) TEST_STR(string)


#define TEST_SIGNED(__stage, __func, __var, __value)             \
    memset(buffer, 'z', buffer_size);                            \
    memset(buffer2, 'z', buffer_size);                           \
    __var = __value;                                             \
    __func(buffer, __var);                                       \
    sprintf(buffer2, "%d", __var);                               \
    if (strcmp(buffer, buffer2) != 0)                            \
    {                                                            \
        fprintf(stderr,                                          \
            "%s: failed conversion (%s), expected %s, got %s\n", \
            TEST_STR(__func), __stage, buffer2, buffer);         \
        failures++;                                              \
    }                                                            \

#define TEST_SIGNED64(__stage, __func, __var, __value)           \
    memset(buffer, 'z', buffer_size);                            \
    memset(buffer2, 'z', buffer_size);                           \
    __var = __value;                                             \
    __func(buffer, __var);                                       \
    sprintf(buffer2, "%lld", __var);                             \
    if (strcmp(buffer, buffer2) != 0)                            \
    {                                                            \
        fprintf(stderr,                                          \
            "%s: failed conversion (%s), expected %s, got %s\n", \
            TEST_STR(__func), __stage, buffer2, buffer);         \
        failures++;                                              \
    }                                                            \


int main(void)
{
    char* buffer = NULL;
    char* buffer2 = NULL;
    size_t buffer_size = 4096;
    volatile int failures = 0;

    int8_t  ivalue8 = 0;
    int16_t ivalue16 = 0;
    int32_t ivalue32 = 0;
    int64_t ivalue64 = 0;
    uint8_t  uvalue8 = 0;
    uint16_t uvalue16 = 0;
    uint32_t uvalue32 = 0;
    uint64_t uvalue64 = 0;

    buffer = malloc(buffer_size);
    buffer2 = malloc(buffer_size);

    if (buffer == NULL || buffer2 == NULL)
    {
        fprintf(stderr, "unable to allocate memory\n");
        return 1;
    }

    /* Test: ex_decstr_from_i8 */
    TEST_SIGNED("1a", ex_decstr_from_i8, ivalue8, INT8_MIN);
    TEST_SIGNED("2a", ex_decstr_from_i8, ivalue8, INT8_MIN / 2);
    TEST_SIGNED("3a", ex_decstr_from_i8, ivalue8, 0);
    TEST_SIGNED("4a", ex_decstr_from_i8, ivalue8, INT8_MAX / 2);
    TEST_SIGNED("5a", ex_decstr_from_i8, ivalue8, INT8_MAX);

    /* Test: ex_decstr_from_i16 */
    TEST_SIGNED("6a", ex_decstr_from_i16, ivalue16, INT16_MIN);
    TEST_SIGNED("7a", ex_decstr_from_i16, ivalue16, INT16_MIN / 2);
    TEST_SIGNED("8a", ex_decstr_from_i16, ivalue16, 0);
    TEST_SIGNED("9a", ex_decstr_from_i16, ivalue16, INT16_MAX / 2);
    TEST_SIGNED("10a", ex_decstr_from_i16, ivalue16, INT16_MAX);

    /* Test: ex_decstr_from_i32 */
    TEST_SIGNED("11a", ex_decstr_from_i32, ivalue32, INT32_MIN);
    TEST_SIGNED("12a", ex_decstr_from_i32, ivalue32, INT32_MIN / 2);
    TEST_SIGNED("13a", ex_decstr_from_i32, ivalue32, 0);
    TEST_SIGNED("14a", ex_decstr_from_i32, ivalue32, INT32_MAX / 2);
    TEST_SIGNED("15a", ex_decstr_from_i32, ivalue32, INT32_MAX);

    /* Test: ex_decstr_from_i64 */
    TEST_SIGNED64("16a", ex_decstr_from_i64, ivalue64, INT64_MIN);
    TEST_SIGNED64("17a", ex_decstr_from_i64, ivalue64, INT64_MIN / 2);
    TEST_SIGNED64("18a", ex_decstr_from_i64, ivalue64, 0);
    TEST_SIGNED64("19a", ex_decstr_from_i64, ivalue64, INT64_MAX / 2);
    TEST_SIGNED64("20a", ex_decstr_from_i64, ivalue64, INT64_MAX);

    return failures;
}