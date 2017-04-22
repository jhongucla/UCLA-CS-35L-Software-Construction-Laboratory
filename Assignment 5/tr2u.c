#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Wrong number of arguments.");
        exit(1);
    }
    char* from = argv[1];
    char* to = argv[2];
    if (strlen(from) != strlen(to))
    {
        fprintf(stderr, "Arguments are not the same length.");
        exit(1);
    }
    size_t i, j;
    for (i = 0; i < strlen(from); i++)
    {
        for (j = i+1; j < strlen(from); j++)
        {
            if (from[i] == from[j])
            {
                fprintf(stderr, "The first argument may not contain duplicates.");
                exit(1);
            }
        }
    }
    char currChar[1];
    while (read(0, currChar, 1) > 0)
    {
        for (i = 0; i < strlen(from); i++)
        {
            if (currChar[0] == from[i])
            {
                currChar[0] = to[i];
                break;
            }
        }
        write(1, currChar, 1);
    }
    return 0;
}
