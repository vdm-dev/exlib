/*
 * Copyright (c) 1998, 2015 Todd C. Miller <millert@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
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
