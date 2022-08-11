#ifndef _TDSE_H_
#define _TDSE_H_

#define SIZE 100

#define PI 3.1415926

typedef float DTYPE;

void tdse(DTYPE psi_re[SIZE][SIZE],
		  DTYPE psi_im[SIZE][SIZE],
		  DTYPE potential[SIZE][SIZE],
		  int iter_num);

#endif
