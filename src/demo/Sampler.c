#include <stdio.h>
#include <math.h>


/**
 * ES5, 3.1
 */
int main() {


    int N = 15;

    double x[N];

    // Sampling interval
    double T_a = 1.;

    // period duration
    int T_0 = 12;

    // frequency
    double f_0 = 1.0/T_0;


    for (int t = 0; t < N; t++) {
        x[t] = 1.0 * sin(2.0 * M_PI * f_0 * t * T_a);
    }

    for (int i = 0; i < N; i++) {
        printf("x[%d] = %f\n", i, x[i]);
    }

}