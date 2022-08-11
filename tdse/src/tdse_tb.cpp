#include "tdse.h"
#include <math.h>
#include <stdio.h>

int main()
{
	DTYPE psi_re[SIZE][SIZE];
	DTYPE psi_im[SIZE][SIZE];
	DTYPE potential[SIZE][SIZE] = {0};

	DTYPE tau = 0.01;
	DTYPE time = 5;
	DTYPE dx = 0.1;

	DTYPE size = 10;
	DTYPE inipos_x = 1. / 3;
	DTYPE inipos_y = 1. / 2;
	DTYPE sigma_x = size / 25.;
	DTYPE sigma_x_i = sigma_x / dx;
	DTYPE sigma_y = size / 25.;
	DTYPE sigma_y_i = sigma_y / dx;
	DTYPE k = PI / (2 * dx);
	DTYPE b;

	int i, j;
	int i0 = SIZE * inipos_x;
	int j0 = SIZE * inipos_y;
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			b = - (i-i0)*(i-i0) / (sigma_x_i*sigma_x_i) / 2 - (j-j0)*(j-j0) / (sigma_y_i*sigma_y_i) / 2;
			psi_re[i][j] = cos(k*i*dx) * exp(b) / sqrt(PI*sigma_x_i*sigma_y_i);
			psi_im[i][j] = sin(k*i*dx) * exp(b) / sqrt(PI*sigma_x_i*sigma_y_i);
		}
	}

	int thickness = 4;
	int aperture = 6;
	for (i = 0; i < SIZE; i++)
	{
		if (i > (SIZE - thickness) / 2 && i < (SIZE + thickness) / 2)
		{
			for (j = 0; j < SIZE; j++)
			{
				if (j > (SIZE + aperture) / 2 || j < (SIZE - aperture) / 2)
				{
					potential[i][j] = 1e30;
				}
			}
		}
	}

	FILE* f;
	f = fopen("psi_re.txt", "w");
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			fprintf(f, "%f ", psi_re[i][j]);
		}
		fprintf(f, "\n");
	}
	fclose(f);

	f = fopen("psi_im.txt", "w");
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			fprintf(f, "%f ", psi_im[i][j]);
		}
		fprintf(f, "\n");
	}
	fclose(f);

	tdse(psi_re, psi_im, potential,
			500
			);

	
	f = fopen("psi_new_re.txt", "w");
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			fprintf(f, "%f ", psi_re[i][j]);
		}
		fprintf(f, "\n");
	}
	fclose(f);

	f = fopen("psi_new_im.txt", "w");
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			fprintf(f, "%f ", psi_im[i][j]);
		}
		fprintf(f, "\n");
	}
	fclose(f);

	f = fopen("potential.txt", "w");
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			fprintf(f, "%f ", potential[i][j]);
		}
		fprintf(f, "\n");
	}
	fclose(f);

	return 0;
}
