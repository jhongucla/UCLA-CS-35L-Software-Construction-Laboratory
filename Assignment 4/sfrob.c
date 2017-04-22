#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int frobcmp(char const *a, char const *b){
    for (;; a++, b++){
        if (*a == ' ' && *b == ' ')
            return 0;
        else if (*a == ' ' || ((*a^42) < (*b^42)))
            return -1;
        else if (*b == ' ' || ((*a^42) > (*b^42)))
            return 1;
    }
}

int cmp(const void *cmp1, const void *cmp2)
{
    const char *a = *(const char**)cmp1;
    const char *b = *(const char**)cmp2;
    return frobcmp(a, b);
}

int main(){
    int ncols = 400;
    char *cols;
    cols = (char*)malloc(sizeof(char) * ncols);
    if (cols == NULL){
        fprintf(stderr, "Could not allocate memory.");
        exit(1);
    }
    char ch = '#';
    int i = 0;
    int words = 0;
    while (ch != EOF){
        if (i >= ncols){
            cols = (char*)realloc(cols, sizeof(char)*ncols*2);
            ncols *= 2;
            if (cols == NULL){
                fprintf(stderr, "Could not re-allocate memory");
                exit(1);
            }
        }
        ch = getchar();
        if (ch != EOF){
            cols[i] = ch;
            i++;
        }
        if (ch == ' ')
            words++;
    }
    if (cols[i-1] != ' '){
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
    for(int j=0; j<k; ++j){
        for(int d=0; p[j][d]!=' '; d++){
            putchar(p[j][d]);
        }
        putchar(' ');
    }
    free(p);
    free(cols);
}
