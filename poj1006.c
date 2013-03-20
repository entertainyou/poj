#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int p, e, i, d, number = 0;
    while (scanf("%d %d %d %d", &p, &e, &i, &d) == 4)
    {
        int iter;
        if (p == -1 && e == -1 && i == -1 && d == -1)
            break;
        number ++;
        for (iter = d + 1; iter <= 21252 + d + 1; ++iter)
        {
            if ((iter - p) % 23 == 0 && (iter - e) % 28 == 0 && (iter - i) % 33 == 0)
                break;
        }
        printf("Case %d: the next triple peak occurs in %d days.\n", number, iter - d);
    }
    return 0;
}
