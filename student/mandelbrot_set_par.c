#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <omp.h>

#include "mandelbrot_set.h"

void mandelbrot_draw(int x_resolution, int y_resolution, int max_iter,
                     double view_x0, double view_x1, double view_y0, double view_y1,
                     double x_stepsize, double y_stepsize,
                     int palette_shift, unsigned char (*img)[x_resolution][3],
							int numThreads) {
	
#pragma omp parallel for num_threads(numThreads) schedule(static,1)
    for(int counter=0;counter<x_resolution*y_resolution;counter++){
	//for (int i = 0; i < y_resolution; i++)
	//{
		//for (int j = 0; j < x_resolution; j++)
		//{
            int x_resolution_t=x_resolution;
            int y_resolution_t=y_resolution;
            int i=counter/x_resolution_t;
            int j=counter%x_resolution_t;
            int threads_maxiter=max_iter;
            int colors_division=(sizeof(colors) / sizeof(colors[0]));
            double view_x0_t=view_x0;
            double view_y1_t=view_y1;
            double y_stepsize_t=y_stepsize;
            double x_stepsize_t=x_stepsize;
            int palette_shift_t=palette_shift;

			double y = view_y1_t - i * y_stepsize_t;
			double x = view_x0_t + j * x_stepsize_t;

			complex double Z = 0 + 0 * I;
			complex double C = x + y * I;

			int k = 0;

			do
			{
				Z = Z * Z + C;
				k++;
			} while (cabs(Z) < 2 && k < threads_maxiter);

			if (k == threads_maxiter)
			{
				memcpy(img[i][j], "\0\0\0", 3);
			}
			else
			{
				int index = (k + palette_shift)
				            % colors_division;
				memcpy(img[i][j], colors[index], 3);
			}
		//}
	}
    //}
}
