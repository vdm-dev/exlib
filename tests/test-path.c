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


#include <stdio.h>

#include <exlib/ex_path.h>
#include <exlib/ex_safestr.h>


int main(void)
{
    const char* source = "/sample/path/to/fileName.ext.tar.gz";
    char output[4096];

    printf("Source Path: %s\n", source);

    ex_get_path(output, sizeof(output), source);
    printf("Path: %s\n", output);

    ex_get_filename(output, sizeof(output), source);
    printf("FileName: %s\n", output);

    ex_get_basename(output, sizeof(output), source);
    printf("BaseName: %s\n", output);

    ex_get_suffix(output, sizeof(output), source);
    printf("Suffix: %s\n", output);

    ex_get_complete_suffix(output, sizeof(output), source);
    printf("Complete Suffix: %s\n", output);

    exs_strcpy(output, sizeof(output), source);
    ex_keep_path(output);
    printf("Path (keep): %s\n", output);

    exs_strcpy(output, sizeof(output), source);
    ex_keep_filename(output);
    printf("FileName (keep): %s\n", output);

    exs_strcpy(output, sizeof(output), source);
    ex_keep_basename(output);
    printf("BaseName (keep): %s\n", output);

    exs_strcpy(output, sizeof(output), source);
    ex_keep_suffix(output);
    printf("Suffix (keep): %s\n", output);

    exs_strcpy(output, sizeof(output), source);
    ex_keep_complete_suffix(output);
    printf("Complete Suffix (keep): %s\n", output);

    return 0;
}
