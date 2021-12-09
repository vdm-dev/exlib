/*
 * Copyright (c) Gregory Pakosz
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


#if defined(__linux__) || defined(__CYGWIN__) || defined(__sun)


#include <stdlib.h>
#include <limits.h>

#include "exlib/ex_strings.h"
#include "exlib/ex_safestr.h"


#if defined(__sun)
#define EX_PROC_SELF_EXE "/proc/self/path/a.out"
#else
#define EX_PROC_SELF_EXE "/proc/self/exe"
#endif


size_t ex_application_path(char* path, size_t size)
{
    char  buffer[PATH_MAX];
    char* resolved = NULL;

    resolved = realpath(EX_PROC_SELF_EXE, buffer);
    exs_strcpy(path, size, resolved);
    return ex_strlen(resolved);
}


#endif /* defined(__linux__) || defined(__CYGWIN__) || defined(__sun) */
