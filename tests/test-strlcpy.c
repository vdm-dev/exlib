#include <stdio.h>

#include <exlib/ex_strings.h>


int main(int argc, char* argv[])
{
    char string[100];

    ex_strlcpy(string, "Added", sizeof(string));

    printf("Test %s\n", string);
    return 0;
}
