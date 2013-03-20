#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

/* struct number */
/* { */
/*     int count[10]; */
/* }; */

void iter(const char *str, char *buffer)
{
    const char *p;
    int count[10], index, i;

    memset(count, 0, 10 * sizeof(int));
    for (p = str; isdigit(*p); ++p)
    {
        /* assert(*p >= '0' && *p <= '9'); */
        count[*p - '0'] ++;
    }

    /* for (i = 0; i < 10; ++i) */
    /* { */
    /*     printf("count[%d] = %d\n", i, count[i]); */
    /* } */
    index = 0;
    for (i = 0; i < 10; ++i)
    {
        if (count[i] != 0)
        {
            index = index + sprintf(buffer + index, "%d%d", count[i], i);
        }
    }
}

int main(int argc, char *argv[])
{
    char buffer[256];
    while (fgets(buffer, 256, stdin) != NULL && strncmp(buffer, "-1", 2) != 0)
    {
        char data[16][256], *p;
        int i, j, found;
        strcpy(data[0], buffer);

        for (p = data[0]; *p; ++p)
        {
            if (!isdigit(*p))
                *p = '\0';
        }

        for (i = 0; i < 16 - 1; ++i)
        {
            iter(data[i], data[i + 1]);
        }

        /* for (i = 0; i < 16; ++i) */
        /* { */
        /*     printf("%d %s\n", i, data[i]); */
        /* } */
        found = 0;
        for (i = 0; i < 16; ++i)
        {
            /* printf("%d %s\n", i, data[i]); */
            for (j = i + 1; j < 16; ++j)
            {
                if (strcmp(data[i], data[j]) == 0)
                {
                    found = 1;
                    break;
                }
            }
            if (found)
                break;
        }

        if (found)
        {
            if (j - i == 1)
            {
                if (i == 0 && j == 1)
                {
                    printf("%s is self-inventorying\n", data[0]);
                }
                else
                {
                    printf("%s is self-inventorying after %d steps\n", data[0], i);
                }
            }
            else
            {
                printf("%s enters an inventory loop of length %d\n", data[0], j - i);
            }
        }
        else
        {
            printf("%s can not be classified after 15 iterations\n", data[0]);
        }
    }
    return 0;
}
