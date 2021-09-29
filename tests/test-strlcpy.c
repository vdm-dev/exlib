#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <exlib/ex_strings.h>


int main(void)
{
    char* buffer = NULL;
    char* buffer2 = NULL;
    char* position = NULL;
    char* buffer_end = NULL;
    size_t length = 0;
    size_t buffer_size = 4096;
    volatile int failures = 0;

    buffer = malloc(buffer_size);
    buffer2 = malloc(buffer_size);

    if (buffer == NULL || buffer2 == NULL)
    {
        fprintf(stderr, "unable to allocate memory\n");
        return 1;
    }

    memset(buffer, 'z', buffer_size);
    buffer_end = buffer + buffer_size;

    /* Test copying to a zero-length NULL buffer. */
    length = ex_strlcpy(NULL, "abcd", 0);
    if (length != 4)
    {
        fprintf(stderr, "ex_strlcpy: failed zero-length buffer test (1a)\n");
        failures++;
    }

    /* Test copying small string to a large buffer. */
    length = ex_strlcpy(buffer, "abcd", buffer_size);
    if (length != 4)
    {
        fprintf(stderr, "ex_strlcpy: failed large buffer test (2a)\n");
        failures++;
    }

    /* Make sure we only wrote where expected. */
    if (memcmp(buffer, "abcd", sizeof("abcd")) != 0)
    {
        fprintf(stderr, "ex_strlcpy: failed large buffer test (2b)\n");
        failures++;
    }
    for (position = buffer + length + 1; position < buffer_end; position++)
    {
        if (*position != 'z')
        {
            fprintf(stderr, "ex_strlcpy: failed large buffer test (2c)\n");
            failures++;
            break;
        }
    }

    /* Test copying large string to a small buffer. */
    memset(buffer, 'z', buffer_size);
    memset(buffer2, 'x', buffer_size - 1);
    buffer2[buffer_size - 1] = '\0';
    length = ex_strlcpy(buffer, buffer2, buffer_size / 2);
    if (length != buffer_size - 1)
    {
        fprintf(stderr, "ex_strlcpy: failed small buffer test (3a)\n");
        failures++;
    }

    /* Make sure we only wrote where expected. */
    length = (buffer_size / 2) - 1;
    if (memcmp(buffer, buffer2, length) != 0 || buffer[length] != '\0')
    {
        fprintf(stderr, "ex_strlcpy: failed small buffer test (3b)\n");
        failures++;
    }
    for (position = buffer + length + 1; position < buffer_end; position++)
    {
        if (*position != 'z')
        {
            fprintf(stderr, "ex_strlcpy: failed small buffer test (3c)\n");
            failures++;
            break;
        }
    }

    /* Test copying to a 1-byte buffer. */
    memset(buffer, 'z', buffer_size);
    length = ex_strlcpy(buffer, "abcd", 1);
    if (length != 4)
    {
        fprintf(stderr, "ex_strlcpy: failed 1-byte buffer test (4a)\n");
        failures++;
    }

    /* Make sure we only wrote where expected. */
    if (buffer[0] != '\0')
    {
        fprintf(stderr, "ex_strlcpy: failed 1-byte buffer test (4b)\n");
        failures++;
    }
    for (position = buffer + 1; position < buffer_end; position++)
    {
        if (*position != 'z')
        {
            fprintf(stderr, "ex_strlcpy: failed 1-byte buffer test (4c)\n");
            failures++;
            break;
        }
    }

    return failures;
}
