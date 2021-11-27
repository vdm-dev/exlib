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


#ifndef EX_PATH_H_INCLUDED
#define EX_PATH_H_INCLUDED


#include <exlib/ex_types.h>


/* path/linux.c */
size_t ex_application_path(char* path, size_t size);

/* path/base.c */
size_t ex_get_path(char* output, size_t osize, const char* spath);
size_t ex_get_filename(char* output, size_t osize, const char* spath);
size_t ex_get_basename(char* output, size_t osize, const char* spath);
size_t ex_get_suffix(char* output, size_t osize, const char* spath);
size_t ex_get_complete_suffix(char* output, size_t osize, const char* spath);
size_t ex_keep_path(char* path);
size_t ex_keep_filename(char* path);
size_t ex_keep_basename(char* path);
size_t ex_keep_suffix(char* path);
size_t ex_keep_complete_suffix(char* path);


#endif /* EX_PATH_H_INCLUDED */
