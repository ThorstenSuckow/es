#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


/**
 * ES5, 3.2
 *
 * compile w/ linking to math libs, e.g.
 * $  gcc RandomNoise.c -o RandomNoise -lm
 */
int main(int argc, char *argv[]) {

    time_t t = time(NULL);
    srand(t);

    double r = rand();

    int N = 15;

    double n[N];
    double min_v = 1;
    double max_v = -1;

    for (int k = 0; k < N; k++) {
        n[k] = ((((double)rand()) / RAND_MAX) * 2.) - 1.;

        min_v = min_v < n[k] ? min_v : n[k];
        max_v = max_v > n[k] ? max_v : n[k];
    }

    for (int i = 0; i < N; i++) {
        printf("n[%d]: %f\n", i, n[i]);
    }

    printf("min: %f\n", min_v);
    printf("max: %f\n", max_v);

    return EXIT_SUCCESS;
}