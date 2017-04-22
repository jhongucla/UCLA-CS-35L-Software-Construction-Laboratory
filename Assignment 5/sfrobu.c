#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>

int toUpper;

int frobcmp(char const *a, char const *b)
{
    for (;; a++, b++){
        if (*a == ' ' && *b == ' ')
            return 0;
        if (toUpper == 1)
        {
            if (*a == ' ' || (toupper((*(unsigned char*)a)^42)) < toupper((*(unsigned char*)b)^42))
                return -1;
            else if (*b == ' ' || (toupper((*(unsigned char*)a)^42)) > toupper((*(unsigned char*)b)^42))
                return 1;
        }
        else
        {
            if (*a == ' ' || ((*a^42) < (*b^42)))
                return -1;
            else if (*b == ' ' || ((*a^42) > (*b^42)))
                return 1;
        }
    }
}

int cmp(const void *cmp1, const void *cmp2)
{
    const char *a = *(const char**)cmp1;
    const char *b = *(const char**)cmp2;
    return frobcmp(a, b);
}

int main(int argc, char* argv[])
{
    if (argc > 2)
    {
        fprintf(stderr, "Wrong number of arguments.");
        exit(1);
    }
    if (argc == 2 && strcmp(argv[1], "-f") == 0)
        toUpper = 1;
    else
        toUpper = 0;
    struct stat fileStats;
    fstat(0, &fileStats);
    int ncols = 1000;
    char *cols;
    char buf[5];
    int i = 0;
    int words = 0;
    if (S_ISREG(fileStats.st_mode))
    {
        if (read(0, &buf, 1) == 0)
            exit(0);
        cols = (char*)malloc(sizeof(char) * fileStats.st_size);
        if (cols == NULL)
        {
            fprintf(stderr, "Could not allocate memory.");
            exit(1);
        }
        int totalSize = fileStats.st_size;
        int size = totalSize;
        for (; i < size; i++)
        {
            read(0, &buf, 1);
            cols[i] = *buf;
            if (*buf == ' ')
                words++;
            if (i == totalSize)
            {
                cols = realloc(cols, totalSize + ncols);
                if (cols == NULL)
                {
                    fprintf(stderr, "Could not reallocate memory.");
                    exit(1);
                }
            }
            totalSize = totalSize + ncols;
            fstat(0, &fileStats);
            size = fileStats.st_size;
        }
    }
    else
    {
        cols = (char*)malloc(sizeof(char) * ncols);
        if (cols == NULL)
        {
            fprintf(stderr, "Could not allocate memory.");
            exit(1);
        }
        while (read(0, &buf, 1))
        {
            cols[i] = *buf;
            i++;
            if (*buf == ' ')
                words++;
            if (i == ncols)
            {
                cols = realloc(cols, sizeof(char) * ncols * 2);
                ncols *= 2;
                if (cols == NULL)
                {
                    fprintf(stderr, "Could not reallocate memory.");
                    exit(1);
                }
            }
        }
    }
    if (cols[i-1] != ' ')
    {
        cols[i++] = ' ';
        words++;
    }
    char **p;
    p = (char**)malloc(sizeof(char*) * words);
    if (p == NULL){
        fprintf(stderr, "Could not allocate memory");
        exit(1);
    }
    char *ptr = cols;
    int k = 0;
    p[0] = cols;
    for (int j = 0; j<i; ++j){
        if (cols[j] == ' ')
            p[++k] = &cols[j+1];
    }
    qsort(p, k, sizeof(char*), cmp);
    for(size_t i = 0; i < words; i++)
    {
        long wordSize = 0;
        for(size_t j = 0;;j++)
        {
            wordSize++;
            if(p[i][j] == ' ')
                break;
        }
        if(write(1,p[i], wordSize) == 0)
        {
            fprintf(stderr, "Could not write.");
            exit(1);
        }
    }
    free(p);
    free(cols);
}
