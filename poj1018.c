#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

struct device
{
    struct manufacturer *manus;
    int manus_size;
};

struct manufacturer
{
    int bandwidth;
    int price;
};

double get_b_device_p(struct device *devices, int number, int *trial)
{
    int b, p, i, temp;

    b = INT_MAX;
    p = 0;
    for (i = 0; i < number; ++i)
    {
        temp = devices[i].manus[trial[i]].bandwidth;
        b = temp < b ? temp : b;
        p += devices[i].manus[trial[i]].price;
    }
    /* printf("b = %d p = %d\n", b, p); */
    return b * 1.0 / p;
}

void array_assign(int *dest, const int *src, int number)
{
    memcpy(dest, src, number * sizeof(int));
}

double solve(struct device *devices, int number)
{
    int *trial, *new_trial;
    double old, iter;
    trial = malloc(number * sizeof(int));
    new_trial = malloc(number * sizeof(int));
    memset(trial, 0, number * sizeof(int));

    while (1)
    {
        int i, changed;

        old = get_b_device_p(devices, number, trial);
        printf("OLD = %lf\n", old);
        iter = old;
        changed = 0;

        array_assign(new_trial, trial, number);
        for (i = 0; i < number; ++i)
        {
            int j;
            double trial_iter;
            for (j = 0; j < devices[i].manus_size; ++j)
            {
                new_trial[i] = j;
                if ((trial_iter = get_b_device_p(devices, number, new_trial)) > iter)
                {
                    int k;
                    for (k = 0; k < number; ++k)
                    {
                        printf(" %d ", new_trial[k]);
                    }
                    printf("\n--------------------------------------------------\n");
                    printf("TRIAL_ITER: %lf\n", trial_iter);
                    iter = trial_iter;
                    trial[i] = j;
                    changed = 1;
                }
                printf("J: %d ITER %lf TRIAL_ITER %lf\n", j, iter, trial_iter);
            }
            new_trial[i] = trial[i];
        }

        if (changed == 0)
        {
            break;
        }
    }

    return iter;
}

double solve2(struct device *devices, int number)
{
    int i, j, *trial;

    double val = 0;
    trial = malloc(number * sizeof(int));

    for (i = 0; i < number; ++i)
    {
        for (j = 0; j < devices[i].manus_size; ++j)
        {
            int band, foo, bar, found, x, y, min_price = INT_MAX;
            double iter;
            band = devices[i].manus[j].bandwidth;

            memset(trial, 0, number * sizeof(int));
            /* for (foo = 0; foo < number; ++foo) */
            /* { */
            /*     for (bar = 0; bar < devices[foo].manus_size; ++bar) */
            /*     { */
            /*         if (devices[foo].manus[bar].bandwidth == band) */
            /*         { */
            /*             int price = devices[foo].manus[bar].price; */
            /*             if (price < min_price) */
            /*             { */
            /*                 x = foo; */
            /*                 y = bar; */
            /*                 min_price = price; */
            /*             } */
            /*         } */
            /*     } */
            /* } */

            /* trial[x] = y; */
            for (foo = 0; foo < number; ++foo)
            {
                /* if (foo == x) */
                /*     continue; */
                found = 0;
                min_price = INT_MAX;
                for (bar = 0; bar < devices[foo].manus_size; ++bar)
                {
                    if (devices[foo].manus[bar].bandwidth >= band)
                    {
                        int price = devices[foo].manus[bar].price;
                        if (price < min_price)
                        {
                            x = foo;
                            y = bar;
                            min_price = price;
                            found = 1;
                        }
                    }
                }
                if (!found)
                {
                    break;
                }

                trial[foo] = y;
            }

            if (!found)
                continue;

            for (foo = 0; foo < number; ++foo)
            {
                for (bar = 0; bar < devices[foo].manus_size; ++bar)
                {
                    if (devices[foo].manus[bar].bandwidth == band)
                    {
                        int oldval = trial[foo];
                        trial[foo] = bar;
                        if ((iter = get_b_device_p(devices, number, trial)) > val)
                        {
                            val = iter;
                        }
                        trial[foo] = oldval;
                    }
                }
            }
        }
    }

    free(trial);
    return val;
}

int main(int argc, char *argv[])
{
    int i, n;
    scanf("%d", &n);

    for (i = 0; i < n; ++i)
    {
        int number, j;
        struct device *devices;

        scanf("%d", &number);
        devices = malloc(number * sizeof(struct device));
        for (j = 0; j < number; ++j)
        {
            int manu_number, k;
            scanf("%d", &manu_number);
            devices[j].manus_size = manu_number;
            devices[j].manus = malloc(manu_number * sizeof(struct manufacturer));
            for (k = 0; k < manu_number; ++k)
            {
                int band, price;
                scanf("%d %d", &band, &price);
                devices[j].manus[k].bandwidth = band;
                devices[j].manus[k].price = price;
            }
        }

        printf("%.3lf\n", solve2(devices, number));
        for (j = 0; j < number; ++j)
        {
            free(devices[j].manus);
        }
        free(devices);
    }
    return 0;
}
