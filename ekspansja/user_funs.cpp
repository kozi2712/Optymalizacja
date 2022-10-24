#include"user_funs.h"

#define _USE_MATH_DEFINES
#include <math.h>



matrix ff(matrix x, matrix ud1, matrix ud2) {
	matrix y;

	y = -cos(0.1 * x()) * exp(-pow((0.1 * x() - 2 * M_PI), 2)) + 0.002 * pow((0.1 * x()),2);
	return y;
}

