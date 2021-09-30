/*
 * Copyright (c) 1998, 2015 Todd C. Miller <millert@openbsd.org>
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

#include "exlib/ex_types.h"


size_t ex_strlcpy(char* destination, const char* source, size_t dsize)
{
    size_t result = 0;

    while (source[result] != '\0')
    {
        if (result < dsize)
            destination[result] = source[result];

        result++;
    }

    if (result < dsize)
    {
        destination[result] = '\0';
    }
    else if (dsize > 0)
    {
        destination[dsize - 1] = '\0';
    }

    return result;
}

size_t ex_strlcat(char* destination, const char* source, size_t dsize)
{
    const char* odst = destination;
    const char* osrc = source;
    size_t n = dsize;
    size_t dlen;

    /* Find the end of dst and adjust bytes left but don't go past end. */
    while (n-- != 0 && *destination != '\0')
        destination++;
    dlen = (size_t)(destination - odst);
    n = dsize - dlen;

    if (n-- == 0)
        return(dlen + strlen(source));
    while (*source != '\0') {
        if (n != 0) {
            *destination++ = *source;
            n--;
        }
        source++;
    }
    *destination = '\0';

    return (dlen + (size_t)(source - osrc)); /* count does not include NUL */
}
