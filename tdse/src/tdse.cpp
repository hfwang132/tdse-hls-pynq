#include "tdse.h"
#include <math.h>
#include <stdio.h> //

#define _S_BASELINE_

#ifdef _S_BASELINE_
// baseline
void tdse(DTYPE psi_re[SIZE][SIZE],
		  DTYPE psi_im[SIZE][SIZE],
		  DTYPE potential[SIZE][SIZE],
		  DTYPE tau,
		  DTYPE time,
		  DTYPE dx)
{
#pragma HLS INTERFACE s_axilite port=return
	DTYPE b48 = -1. / (48 * PI * PI * dx * dx)  * tau;
	DTYPE b3 = 1. / (3 * PI * PI * dx * dx)  * tau;
	DTYPE c48 = cos(b48);
	DTYPE s48 = sin(b48);
	DTYPE c3 = cos(b3);
	DTYPE s3 = sin(b3);

	DTYPE v60;
	DTYPE c60;
	DTYPE s60;

	int iter_step = (int) time / tau;

	int i, j, k, i_ini, j_ini;

	DTYPE psi_tmp_1_re;
	DTYPE psi_tmp_1_im;

	DTYPE psi_tmp_2_re;
	DTYPE psi_tmp_2_im;

	top:for (k = 0; k < iter_step; k++)
	{
		R1_ini:for (i_ini = 0; i_ini < 4; i_ini++)
		{
			R1_o:for (i = i_ini; i < SIZE - 2; i += 4)
			{
//#pragma HLS PIPELINE II=1
				R1_i:for (j = 0; j < SIZE; j++)
#pragma HLS PIPELINE II=1
				{
					psi_tmp_1_re = psi_re[i][j];
					psi_tmp_1_im = psi_im[i][j];
					psi_tmp_2_re = psi_re[i+2][j];
					psi_tmp_2_im = psi_im[i+2][j];

					psi_re[i][j] = psi_tmp_1_re * c48 - psi_tmp_2_im * s48;
					psi_im[i][j] = psi_tmp_1_im * c48 + psi_tmp_2_re * s48;
					psi_re[i+2][j] = -psi_tmp_1_im * s48 + psi_tmp_2_re * c48;
					psi_im[i+2][j] = psi_tmp_1_re * s48 + psi_tmp_2_im * c48;
				}
			}
		}
		
		R2_ini:for (i_ini = 0; i_ini < 2; i_ini++)
		{
			R2_o:for (i = i_ini; i < SIZE - 1; i += 2)
			{
//#pragma HLS PIPELINE II=1
				R2_i:for (j = 0; j < SIZE; j++)
#pragma HLS PIPELINE II=1
				{
					psi_tmp_1_re = psi_re[i][j];
					psi_tmp_1_im = psi_im[i][j];
					psi_tmp_2_re = psi_re[i+1][j];
					psi_tmp_2_im = psi_im[i+1][j];

					psi_re[i][j] = psi_tmp_1_re * c3 - psi_tmp_2_im * s3;
					psi_im[i][j] = psi_tmp_1_im * c3 + psi_tmp_2_re * s3;
					psi_re[i+1][j] = -psi_tmp_1_im * s3 + psi_tmp_2_re * c3;
					psi_im[i+1][j] = psi_tmp_1_re * s3 + psi_tmp_2_im * c3;
				}
			}
		}

		R3_ini:for (j_ini = 0; j_ini < 4; j_ini++)
		{
			R3_o:for (j = j_ini; j < SIZE - 2; j += 4)
			{
//#pragma HLS PIPELINE II=1
				R3_i:for (i = 0; i < SIZE; i++)
				{
#pragma HLS PIPELINE II=1
					psi_tmp_1_re = psi_re[i][j];
					psi_tmp_1_im = psi_im[i][j];
					psi_tmp_2_re = psi_re[i][j+2];
					psi_tmp_2_im = psi_im[i][j+2];
					psi_re[i][j] = psi_tmp_1_re * c48 - psi_tmp_2_im * s48;
					psi_im[i][j] = psi_tmp_1_im * c48 + psi_tmp_2_re * s48;
					psi_re[i][j+2] = -psi_tmp_1_im * s48 + psi_tmp_2_re * c48;
					psi_im[i][j+2] = psi_tmp_1_re * s48 + psi_tmp_2_im * c48;
				}
			}
		}

		R4_ini:for (j_ini = 0; j_ini < 2; j_ini++)
		{
			R4_o:for (j = j_ini; j < SIZE - 1; j += 2)
			{
//#pragma HLS PIPELINE II=1
				R4_i:for (i = 0; i < SIZE; i++)
#pragma HLS PIPELINE II=1
				{
					psi_tmp_1_re = psi_re[i][j];
					psi_tmp_1_im = psi_im[i][j];
					psi_tmp_2_re = psi_re[i][j+1];
					psi_tmp_2_im = psi_im[i][j+1];
					psi_re[i][j] = psi_tmp_1_re * c3 - psi_tmp_2_im * s3;
					psi_im[i][j] = psi_tmp_1_im * c3 + psi_tmp_2_re * s3;
					psi_re[i][j+1] = -psi_tmp_1_im * s3 + psi_tmp_2_re * c3;
					psi_im[i][j+1] = psi_tmp_1_re * s3 + psi_tmp_2_im * c3;
				}
			}
		}

		R5_o:for (i = 0; i < SIZE; i++)
		{
//#pragma HLS PIPELINE II=1
			R5_i:for (j = 0; j < SIZE; j++)
			{
#pragma HLS PIPELINE II=1
				v60 = -tau * (60 * (-b48) + potential[i][j]);
				c60 = cos(v60);
				s60 = sin(s60);
				psi_tmp_1_re = psi_re[i][j];
				psi_tmp_1_im = psi_im[i][j];
				psi_re[i][j] = psi_tmp_1_re * c60 - psi_tmp_1_im * s60;
				psi_im[i][j] = psi_tmp_1_re * s60 + psi_tmp_1_im * c60;
			}
		}
	}


}
#endif
