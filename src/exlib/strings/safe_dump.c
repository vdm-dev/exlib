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
#include "exlib/ex_safestr.h"


bool exs_hexstr_from_buffer(const void* data, size_t dsize, char* output,
    size_t osize, uint32_t options)
{
    size_t i = 0;
    size_t asize = 0;
    size_t opos = 0;
    bool   result = true;
    char   hex[2];

    if (data == NULL || output == NULL || osize == 0)
        return false;

    asize = (options & EX_STR_NOZERO) ? osize : (osize - 1);

    for (i = 0; i < dsize; ++i)
    {
        if (i > 0 && (options & EX_STR_NOSPACES) == 0)
        {
            if (opos < asize)
            {
                output[opos++] = ' ';
            }
            else
            {
                /* Cannot insert new character into output string */
                result = false;
                break;
            }
        }

        hex[1] = ((const char*) data)[i];
        hex[0] = (hex[1] >> 4) & 0x0F;
        hex[1] = hex[1] & 0x0F;

        if (options & EX_STR_LOWERCASE)
        {
            hex[0] = (hex[0] < 10) ? (hex[0] + '0') : (hex[0] + 'a' - 10);
            hex[1] = (hex[1] < 10) ? (hex[1] + '0') : (hex[1] + 'a' - 10);
        }
        else
        {
            hex[0] = (hex[0] < 10) ? (hex[0] + '0') : (hex[0] + 'A' - 10);
            hex[1] = (hex[1] < 10) ? (hex[1] + '0') : (hex[1] + 'A' - 10);
        }

        if (opos + 2 <= asize)
        {
            output[opos++] = hex[0];
            output[opos++] = hex[1];
        }
        else
        {
            /* Cannot insert two characters into output string */
            result = false;
            break;
        }
    }

    if ((options & EX_STR_NOZERO) == 0)
    {
        output[opos] = '\0';
    }

    return result;
}
