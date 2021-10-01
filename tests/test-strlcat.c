/*
 * Copyright (c) 2014 Todd C. Miller <millert@openbsd.org>
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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>

#include <exlib/ex_strings.h>


static volatile int got_signal;
static jmp_buf jump_buffer;


void signal_handler (int signo)
{
    got_signal = signo;
    longjmp(jump_buffer, 1);
}


int main(void)
{
    char* buffer = NULL;
    char* position = NULL;
    char* buffer_end = NULL;
    size_t length = 0;
    size_t buffer_size = 4096;
    volatile int failures = 0;

    buffer = malloc(buffer_size);

    if (buffer == NULL)
    {
        fprintf(stderr, "unable to allocate memory\n");
        return 1;
    }

    memset(buffer, 'z', buffer_size);
    buffer_end = buffer + buffer_size;

    /* Test appending to an unterminated string. */
    length = ex_strlcat(buffer, "abcd", buffer_size);
    if (length != 4 + buffer_size)
    {
        fprintf(stderr,
                "ex_strlcat: failed unterminated buffer test (1a)\n");
        failures++;
    }
    /* Make sure we only wrote where expected. */
    for (position = buffer; position < buffer_end; position++)
    {
        if (*position != 'z')
        {
            fprintf(stderr,
                    "ex_strlcat: failed unterminated buffer test (1b)\n");
            failures++;
            break;
        }
    }

    /* Test appending to a full string. */
    buffer_end[-1] = '\0';
    length = ex_strlcat(buffer, "abcd", buffer_size);
    if (length != 4 + buffer_size - 1)
    {
        fprintf(stderr, "ex_strlcat: failed full buffer test (2a)\n");
        failures++;
    }
    /* Make sure we only wrote where expected. */
    for (position = buffer; position < buffer_end - 1; position++)
    {
        if (*position != 'z')
        {
            fprintf(stderr,
                    "ex_strlcat: failed full buffer test (2b)\n");
            failures++;
            break;
        }
    }

    /* Test appending to an empty string. */
    buffer_end[-1] = 'z';
    buffer[0] = '\0';
    length = ex_strlcat(buffer, "abcd", buffer_size);
    if (length != 4)
    {
        fprintf(stderr, "ex_strlcat: failed empty buffer test (3a)\n");
        failures++;
    }
    /* Make sure we only wrote where expected. */
    if (memcmp(buffer, "abcd", sizeof("abcd")) != 0)
    {
        fprintf(stderr, "ex_strlcat: failed empty buffer test (3b)\n");
        failures++;
    }
    for (position = buffer + length + 1; position < buffer_end; position++)
    {
        if (*position != 'z')
        {
            fprintf(stderr,
                    "ex_strlcat: failed empty buffer test (3c)\n");
            failures++;
            break;
        }
    }

    /* Test appending to a NUL-terminated string. */
    memcpy(buffer, "abcd", sizeof("abcd"));
    length = ex_strlcat(buffer, "efgh", buffer_size);
    if (length != 8)
    {
        fprintf(stderr, "ex_strlcat: failed empty buffer test (4a)\n");
        failures++;
    }
    /* Make sure we only wrote where expected. */
    if (memcmp(buffer, "abcdefgh", sizeof("abcdefgh")) != 0)
    {
        fprintf(stderr, "ex_strlcat: failed empty buffer test (4b)\n");
        failures++;
    }
    for (position = buffer + length + 1; position < buffer_end; position++)
    {
        if (*position != 'z') {
            fprintf(stderr,
                    "ex_strlcat: failed empty buffer test (4c)\n");
            failures++;
            break;
        }
    }

    /*
     * The following tests should result in SIGSEGV, however some
     * systems may erroneously report SIGBUS.
     * These tests assume that ex_strlcat() is signal-safe.
     */

    /* Test copying to a NULL buffer with non-zero size. */
    got_signal = 0;
    signal(SIGSEGV, &signal_handler);
    if (setjmp(jump_buffer) == 0)
    {
        length = ex_strlcat(NULL, "abcd", sizeof(buffer));
        fprintf(stderr, "ex_strlcat: failed NULL dst test (5a), "
                        "expected signal %d, got len %zu\n", SIGSEGV, length);
        failures++;
    }
    else if (got_signal != SIGSEGV)
    {
        fprintf(stderr, "ex_strlcat: failed NULL dst test (5b), "
                        "expected signal %d, got %d\n", SIGSEGV, got_signal);
        failures++;
    }

    /* Test copying from a NULL src. */
    memcpy(buffer, "abcd", sizeof("abcd"));
    got_signal = 0;
    signal(SIGSEGV, &signal_handler);
    if (setjmp(jump_buffer) == 0)
    {
        length = ex_strlcat(buffer, NULL, sizeof(buffer));
        fprintf(stderr, "ex_strlcat: failed NULL src test (6a), "
                        "expected signal %d, got len %zu\n", SIGSEGV, length);
        failures++;
    }
    else if (got_signal != SIGSEGV)
    {
        fprintf(stderr, "ex_strlcat: failed NULL src test (6b), "
                        "expected signal %d, got %d\n", SIGSEGV, got_signal);
        failures++;
    }

    return failures;
}
