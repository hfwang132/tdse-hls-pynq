#include <math.h>
#include "dft.h"
#include "coefficients1024.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/time.h>

// #define _LEGACY_
#define _WITH_TB_

void dft(DTYPE real_sample[SIZE], DTYPE imag_sample[SIZE], DTYPE real_op[SIZE], DTYPE imag_op[SIZE])
{
    int i, j;
    int index;
    DTYPE c, s;

    // Temporary arrays to hold the intermediate frequency domain results
    DTYPE temp_real[SIZE];
    DTYPE temp_imag[SIZE];

    // Calculate each frequency domain sample iteratively
    for (i = 0; i < SIZE; i += 1)
    {
        temp_real[i] = 0;
        temp_imag[i] = 0;

        // Calculate the jth frequency sample sequentially
        for (j = 0; j < SIZE; j += 1)
        {
            // Multiply the current phasor with the appropriate input sample and keep
            // running sum
            index = i * j % SIZE;
			c = cos_coefficients_1024[index];
			s = sin_coefficients_1024[index];
			temp_real[i] += real_sample[j] * c - imag_sample[j] * s;
			temp_imag[i] += real_sample[j] * s + imag_sample[j] * c;
        }
    }
    /*
     w0 w0 w0 w0   in0    out0
     w0 w1 w2 w3   in1    out1
     w0 w2 w4 w6   in2    out2
     w0 w3 w6 w9   in3    out3
     */

    // Copy result into the output arrays
    for (i = 0; i < SIZE; i += 1)
    {
        real_op[i] = temp_real[i];
        imag_op[i] = temp_imag[i];
    }
}

#ifdef _LEGACY_
int main()
{
    DTYPE In_R[SIZE], In_I[SIZE], Out_R[SIZE], Out_I[SIZE], gold_R[SIZE], gold_I[SIZE];

    FILE *fp = fopen("out.gold.dat", "r");
    // getting input data and golden data
    for (int i = 0; i < 1024; i++)
    {
        fscanf(fp, "%f %f %f", &In_R[i], &gold_R[i], &gold_I[i]);
        In_I[i] = 0;
    }

    // DFT
    struct timeval t1, t2;
    gettimeofday(&t1, NULL);

    dft(In_R, In_I, Out_R, Out_I);

    gettimeofday(&t2, NULL);
    printf("time elapsed: %ld us\n", (t2.tv_sec - t1.tv_sec) * 1000000 + t2.tv_usec - t1.tv_usec);

    fclose(fp);

    return 0;
}
#endif

#ifdef _WITH_TB_
struct Rmse
{
    int num_sq;
    float sum_sq;
    float error;

    Rmse()
    {
        num_sq = 0;
        sum_sq = 0;
        error = 0;
    }

    float add_value(float d_n)
    {
        num_sq++;
        sum_sq += (d_n * d_n);
        error = sqrtf(sum_sq / num_sq);
        return error;
    }
};

Rmse rmse_R, rmse_I;

DTYPE In_R[1024], In_I[1024], Out_R[1024], Out_I[1024];

int main()
{
    int index;
    float gold_R, gold_I;

    FILE *fp = fopen("out.gold.dat", "r");

    // getting input data
    for (int i = 0; i < 1024; i++)
    {
        In_R[i] = i;
        In_I[i] = 0.0;
    }

    // DFT
    struct timeval t1, t2;
    gettimeofday(&t1, NULL);
    dft(In_R, In_I, Out_R, Out_I);
    gettimeofday(&t2, NULL);
    printf("time used: %ld us\n", (t2.tv_sec - t1.tv_sec) * 1000000 + t2.tv_usec - t1.tv_usec);

    // comparing with golden output
    for (int i = 0; i < 1024; i++)
    {
        fscanf(fp, "%d %f %f", &index, &gold_R, &gold_I);
        rmse_R.add_value((float)Out_R[i] - gold_R);
        rmse_I.add_value((float)Out_I[i] - gold_I);
    }
    fclose(fp);

    // printing error results
    printf("----------------------------------------------\n");
    printf("   RMSE(R)           RMSE(I)\n");
    printf("%0.15f %0.15f\n", rmse_R.error, rmse_I.error);
    printf("----------------------------------------------\n");

    if (rmse_R.error > 0.1 || rmse_I.error > 0.1)
    {
        fprintf(stdout, "*******************************************\n");
        fprintf(stdout, "FAIL: Output DOES NOT match the golden output\n");
        fprintf(stdout, "*******************************************\n");
        return 1;
    }
    else
    {
        fprintf(stdout, "*******************************************\n");
        fprintf(stdout, "PASS: The output matches the golden output!\n");
        fprintf(stdout, "*******************************************\n");
        return 0;
    }
}
#endif