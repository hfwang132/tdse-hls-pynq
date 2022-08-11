#include "tdse.h"
#include <math.h>
#include "sets.h"


DTYPE tau = 0.01;
DTYPE dx = 0.1;
DTYPE b48 = -1. / (48 * PI * PI * dx * dx)  * tau;
DTYPE c48 = 0.999997772140095;
DTYPE s48 = -0.002110856424983;
DTYPE c3 = 0.999429721863621;
DTYPE s3 = 0.033767307497130;

void tdse(DTYPE psi_re[SIZE][SIZE],
		  DTYPE psi_im[SIZE][SIZE],
		  DTYPE potential[SIZE][SIZE],
		  int iter_num)
{
#pragma HLS INTERFACE s_axilite port=iter_num
#pragma HLS INTERFACE m_axi depth=10000 port=psi_re offset=slave
#pragma HLS INTERFACE m_axi depth=10000 port=psi_im offset=slave
#pragma HLS INTERFACE m_axi depth=10000 port=potential offset=slave
#pragma HLS INTERFACE s_axilite port=return

	DTYPE v60;
	DTYPE c60;
	DTYPE s60;

	int i, j, k, i_ini, j_ini, ii, jj;

	DTYPE psi_re_tmp[SIZE][SIZE];
	DTYPE psi_im_tmp[SIZE][SIZE];

	top:for (k = 0; k < iter_num; k++)
	{
#pragma HLS LOOP_TRIPCOUNT avg=1000 max=2000 min=100
		R11_o:for (ii = 0; ii < SIZE / 2; ii++)
		{
			i = S11[ii];
			R11_i:for (j = 0; j < SIZE; j++)
#pragma HLS PIPELINE II=1
			{
				psi_re_tmp[i][j] = psi_re[i][j] * c48 - psi_im[i+2][j] * s48;
				psi_im_tmp[i][j] = psi_im[i][j] * c48 + psi_re[i+2][j] * s48;
				psi_re_tmp[i+2][j] = -psi_im[i][j] * s48 + psi_re[i+2][j] * c48;
				psi_im_tmp[i+2][j] = psi_re[i][j] * s48 + psi_im[i+2][j] * c48;
			}
		}


		R12_o:for (ii = 0; ii < SIZE / 2 - 2; ii++)
		{
			i = S12[ii];
			R12_i:for (j = 0; j < SIZE; j++)
#pragma HLS PIPELINE II=1
			{
				psi_re[i][j] = psi_re_tmp[i][j] * c48 - psi_im_tmp[i+2][j] * s48;
				psi_im[i][j] = psi_im_tmp[i][j] * c48 + psi_re_tmp[i+2][j] * s48;
				psi_re[i+2][j] = -psi_im_tmp[i][j] * s48 + psi_re_tmp[i+2][j] * c48;
				psi_im[i+2][j] = psi_re_tmp[i][j] * s48 + psi_im_tmp[i+2][j] * c48;
			}
		}

		R21_o:for (i = 0; i < SIZE - 1; i += 2)
		{
			R21_i:for (j = 0; j < SIZE; j++)
#pragma HLS PIPELINE II=1
			{
				psi_re_tmp[i][j] = psi_re[i][j] * c3 - psi_im[i+1][j] * s3;
				psi_im_tmp[i][j] = psi_im[i][j] * c3 + psi_re[i+1][j] * s3;
				psi_re_tmp[i+1][j] = -psi_im[i][j] * s3 + psi_re[i+1][j] * c3;
				psi_im_tmp[i+1][j] = psi_re[i][j] * s3 + psi_im[i+1][j] * c3;
			}
		}

		R22_o:for (i = 1; i < SIZE - 1; i += 2)
		{
			R22_i:for (j = 0; j < SIZE; j++)
#pragma HLS PIPELINE II=1
			{
				psi_re[i][j] = psi_re_tmp[i][j] * c3 - psi_im_tmp[i+1][j] * s3;
				psi_im[i][j] = psi_im_tmp[i][j] * c3 + psi_re_tmp[i+1][j] * s3;
				psi_re[i+1][j] = -psi_im_tmp[i][j] * s3 + psi_re_tmp[i+1][j] * c3;
				psi_im[i+1][j] = psi_re_tmp[i][j] * s3 + psi_im_tmp[i+1][j] * c3;
			}
		}

		R31_o:for (jj = 0; jj < SIZE / 2; jj++)
		{
			j = S11[jj];
			R31_i:for (i = 0; i < SIZE; i++)
			{
#pragma HLS PIPELINE II=1
				psi_re_tmp[i][j] = psi_re[i][j] * c48 - psi_im[i][j+2] * s48;
				psi_im_tmp[i][j] = psi_im[i][j] * c48 + psi_re[i][j+2] * s48;
				psi_re_tmp[i][j+2] = -psi_im[i][j] * s48 + psi_re[i][j+2] * c48;
				psi_im_tmp[i][j+2] = psi_re[i][j] * s48 + psi_im[i][j+2] * c48;
			}
		}

		R32_o:for (jj = 0; jj < SIZE / 2 - 2; jj++)
		{
			j = S12[jj];
			R32_i:for (i = 0; i < SIZE; i++)
			{
#pragma HLS PIPELINE II=1
				psi_re[i][j] = psi_re_tmp[i][j] * c48 - psi_im_tmp[i][j+2] * s48;
				psi_im[i][j] = psi_im_tmp[i][j] * c48 + psi_re_tmp[i][j+2] * s48;
				psi_re[i][j+2] = -psi_im_tmp[i][j] * s48 + psi_re_tmp[i][j+2] * c48;
				psi_im[i][j+2] = psi_re_tmp[i][j] * s48 + psi_im_tmp[i][j+2] * c48;
			}
		}

		R41_o:for (j = 0; j < SIZE - 1; j += 2)
		{
			R41_i:for (i = 0; i < SIZE; i++)
#pragma HLS PIPELINE II=1
			{
				psi_re_tmp[i][j] = psi_re[i][j] * c3 - psi_im[i][j+1] * s3;
				psi_im_tmp[i][j] = psi_im[i][j] * c3 + psi_re[i][j+1] * s3;
				psi_re_tmp[i][j+1] = -psi_im[i][j] * s3 + psi_re[i][j+1] * c3;
				psi_im_tmp[i][j+1] = psi_re[i][j] * s3 + psi_im[i][j+1] * c3;
			}
		}

		R42_o:for (j = 1; j < SIZE - 1; j += 2)
		{
			R42_i:for (i = 0; i < SIZE; i++)
#pragma HLS PIPELINE II=1
			{
				psi_re[i][j] = psi_re_tmp[i][j] * c3 - psi_im_tmp[i][j+1] * s3;
				psi_im[i][j] = psi_im_tmp[i][j] * c3 + psi_re_tmp[i][j+1] * s3;
				psi_re[i][j+1] = -psi_im_tmp[i][j] * s3 + psi_re_tmp[i][j+1] * c3;
				psi_im[i][j+1] = psi_re_tmp[i][j] * s3 + psi_im_tmp[i][j+1] * c3;
			}
		}

		R5_o:for (i = 0; i < SIZE; i++)
		{
			R5_i:for (j = 0; j < SIZE; j++)
			{
#pragma HLS PIPELINE II=1
				v60 = -tau * (60 * (-b48) + potential[i][j]);
				c60 = cos(v60);
				s60 = sin(v60);
				psi_re_tmp[i][j] = psi_re[i][j] * c60 - psi_im[i][j] * s60;
				psi_im_tmp[i][j] = psi_re[i][j] * s60 + psi_im[i][j] * c60;
			}
		}

		R5_copy_o:for (i = 0; i < SIZE; i++)
		{
			R5_copy_i:for (j = 0; j < SIZE; j++)
			{
#pragma HLS PIPELINE II=1
				psi_re[i][j] = psi_re_tmp[i][j];
				psi_im[i][j] = psi_im_tmp[i][j];
			}
		}

	}


}
#endif
