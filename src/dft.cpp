#include <math.h>
#include "dft.h"
#include "coefficients1024.h"

//#define _S_BASELINE_
#define _S_LOOP_INTERCHANGE_

#ifdef _S_BASELINE_
// baseline
void dft(DTYPE real_sample[SIZE], DTYPE imag_sample[SIZE],DTYPE real_op[SIZE],DTYPE imag_op[SIZE])
{
	int i, j;
	int index;
	DTYPE c, s;

	// Temporary arrays to hold the intermediate frequency domain results
	DTYPE temp_real[SIZE];
	DTYPE temp_imag[SIZE];

	// Calculate each frequency domain sample iteratively
	for (i = 0; i < SIZE; i += 1) {
		temp_real[i] = 0;
		temp_imag[i] = 0;

		// Calculate the jth frequency sample sequentially
		for (j = 0; j < SIZE; j += 1) {
			// Multiply the current phasor with the appropriate input sample and keep
			// running sum
			index = i * j % SIZE;
			c = cos_coefficients_1024[index];
			s = sin_coefficients_1024[index];
			temp_real[i] += real_sample[j] * c + imag_sample[j] * s;
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
	for (i = 0; i < SIZE; i += 1) {
		real_op[i] = temp_real[i];
		imag_op[i] = temp_imag[i];
	}
}
#endif

#ifdef _S_LOOP_INTERCHANGE_
void dft(DTYPE real_sample[SIZE], DTYPE imag_sample[SIZE],DTYPE real_op[SIZE],DTYPE imag_op[SIZE])
{
	int i, j;
	int index;

	// Temporary arrays to hold the intermediate frequency domain results
	DTYPE temp_real[SIZE] = {0};
	DTYPE temp_imag[SIZE] = {0};

	// Calculate each frequency domain sample iteratively
	loop1: for (i = 0; i < SIZE; i += 1) { // use loop interchange strategy

		// Calculate the jth frequency sample sequentially
		loop2: for (j = 0; j < SIZE; j += 1) {
			// Multiply the current phasor with the appropriate input sample and keep
			// running sum
			index = i * j % SIZE;
			temp_real[j] += real_sample[i] * cos_coefficients_1024[index] - imag_sample[i] * sin_coefficients_1024[index];
			temp_imag[j] += real_sample[i] * sin_coefficients_1024[index] + imag_sample[i] * cos_coefficients_1024[index];
		}
	}
	/*
	 w0 w0 w0 w0   in0    out0
	 w0 w1 w2 w3   in1    out1
	 w0 w2 w4 w6   in2    out2
	 w0 w3 w6 w9   in3    out3
	 */

	// Copy result into the output arrays
	copy_loop: for (i = 0; i < SIZE; i += 1) {
		real_op[i] = temp_real[i];
		imag_op[i] = temp_imag[i];
	}
}
#endif
