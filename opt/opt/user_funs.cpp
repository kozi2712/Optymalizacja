#include"user_funs.h"

matrix ff1T(matrix x, matrix ud1, matrix ud2)
{
	matrix y;
	y = -cos(0.1 * x()) * exp(-pow(0.1 * x() - 2 * 3.14, 2)) + 0.002 * pow(0.1 * x(), 2);
	return y;
}

matrix df1(double t, matrix Y, matrix ud1, matrix ud2) {
	double a = 0.98;
	double b = 0.63;
	double D = 0;
	double g = 9.81;

	double Pa = 0.75;
	double Pb = 1.0;
	double Va = 5.0;
	double Vb = 1.0;
	double Ta = 90.0;
	double Tb = 10.0;
	double Db = 0.00365665;
	double FbIn = 0.01;

	matrix dY(3, 1);

	double FaOut = a * b * m2d(ud2) * sqrt(2 * g * Y(0) / Pa);
	double FbOut = a * b * Db * sqrt(2 * g * Y(1) / Pb);

	dY(0) = -FaOut;
	dY(1) = FaOut + FbIn - FbOut;
	dY(2) = (FbIn / Y(1)) * (Tb - Y(2)) + (FaOut / Y(1)) * (Ta - Y(2));

	return dY;
}


matrix FR(matrix x, matrix ud1, matrix ud2) {
	matrix y;

	matrix Y0 = matrix(3, new double[3]{ 5,1,10 });
	matrix* Y = solve_ode(df1, 0, 1, 1000, Y0, ud1, x);
	double max = Y[1](0 , 2);
	for (int i = 0; i < get_len(Y[0]); i++) {
		if (Y[1](i, 2) > max)max = Y[1](i, 2);
		//y = abs(max - 50);
		y = abs(max - 60);
		//y = abs(max - 40);
		
	}
	return y;
}