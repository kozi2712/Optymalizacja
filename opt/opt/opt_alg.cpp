#include"opt_alg.h"
double* expansion(matrix(*ff)(matrix, matrix, matrix), double x0, double d, double alpha, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		double* p = new double[2]{ 0,0 };
		//Tu wpisz kod funkcji

		solution X0(x0);
		solution X1(matrix(x0 + d));
		
		X0.fit_fun(ff1T);
		X1.fit_fun(ff1T);

		if (X0.y == X1.y) {
			p[0] = m2d(X0.x);
			p[1] = m2d(X1.x);
			return p;
		}

		if (X1.y > X0.y) {
			d = -d;
			X1.x = x0 + d;

			if (X1.fit_fun(ff1T) >= X0.fit_fun(ff1T)) {
				p[0] = m2d(X1.x);
				p[1] = m2d(X0.x-d);
				return p;
			}
		}
		solution X2;
		int i = 1;

		while(true){
			
			
			X2.x = x0 + pow(alpha, i) * d;
			X2.fit_fun(ff1T);
			//cout << "X0: " << X0.x() << " " << X0.y() << "X1: " << X1.x() <<" " << X1.y() << " X2: " << X2.x() << " " << X2.y() << endl;
			if (X2.y >= X1.y || solution::f_calls>Nmax) {
				break;
			}

			X0 = X1;
			X1 = X2;
			
			++i;
		}
		if (d > 0) {
			p[0] = X0.x();
			p[1] = X2.x();
		}
		else {
			p[0] = X2.x();
			p[1] = X0.x();
		}

		return p;
	}
	catch (string ex_info)
	{
		throw ("double* expansion(...):\n" + ex_info);
	}
}

double fibonacci(int n) {
	if (n == 0) return 1;
	if (n == 1) return 1;
	return (fibonacci(n - 1) + fibonacci(n - 2));
}

solution fib(matrix(*ff)(matrix, matrix, matrix), double a, double b, double epsilon, matrix ud1, matrix ud2)
{


	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji
		int i = 0, k = 0, fi = 0;
		double tmp2 = 0.;

		solution A(a);
		solution B(b);

		double tmp = (b - a) / (epsilon);

		while (true) {
			if (fibonacci(i) > tmp) {
				//fi = fibonacci(i);
				break;
			}
			i++;
			k++;
		}
		k++;
		//cout <<"\ntmp2: " << tmp2;
		solution C;
		C.x = B.x - ((fibonacci(k - 2) / fibonacci(k - 1)) * (B.x - A.x));
		C.fit_fun(ff, ud1, ud2);
		//cout << "\ntmp2: " << tmp2;
		solution D;
		D.x = A.x + B.x - C.x;
		D.fit_fun(ff, ud1, ud2);


		//cout <<"\nc.x: " << c.x << " d.x: " << d.x << endl;
		//cout << "A.x: " << A.x << "\nB.x: " << B.x << endl;
		for (i = 0; i <= k - 3; ++i) {
			if (C.y < D.y) {
				B.x = D.x;
			}
			else {
				A.x = C.x;
			}
			//A.fit_fun(ff);
			//B.fit_fun(ff);

			C.x = B.x - (fibonacci(k - i - 2) / fibonacci(k - i - 1)) * (B.x - A.x);
			D.x = A.x + B.x - C.x;
			//cout << C.x << endl;
			C.fit_fun(ff, ud1, ud2);
			D.fit_fun(ff, ud1, ud2);

			//cout << "---------\nA.x: " << A.x << "\nB.x: " << B.x << "\nC.x: " << C.x << "\nD.x: " << D.x << endl;
			cout << B.x - A.x << endl;
		}

		Xopt = C;
		

		//cout << "\nk: " << k << " fi: " << fi << " tmp: " << tmp;
		cout << "minimum funkcji(metoda fibonacciego): ";
		cout << "\nx: " << Xopt.x << " y: " << Xopt.y << endl;
		cout << "f_calls: " << solution::f_calls << endl;

		return Xopt;
	
	}
	catch (string ex_info)
	{
		throw ("solution fib(...):\n" + ex_info);
	}

}

solution lag(matrix(*ff)(matrix, matrix, matrix), double a, double b, double epsilon, double gamma, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		Xopt.ud = b - a;
		//Tu wpisz kod funkcji

		solution A(a);
		solution B(b);
		solution C;
		solution D;
		solution D2(a);

		double L;
		double M;

		C.x = (a + b) / 2;

		A.fit_fun(ff, ud1, ud2);
		B.fit_fun(ff, ud1, ud2);
		C.fit_fun(ff, ud1, ud2);
		cout << B.x - A.x << endl;

		while (true) {


			
			L = m2d(A.y * (pow(B.x) - pow(C.x)) + B.y * (pow(C.x) - pow(A.x)) + C.y * (pow(A.x) - pow(B.x)));
			M = m2d(A.y * (B.x - C.x) + B.y * (C.x - A.x) + C.y * (A.x - B.x));

			if (M <= 0) {
				Xopt = D2;
				Xopt.flag = 2;
				cout << "\nminimum funkcji(metoda legendra)1: ";
				cout << "\nx: " << Xopt.x << " y: " << Xopt.y << endl;
				cout << "f_calls: " << solution::f_calls << endl;
				return Xopt;
			}

			D.x = 0.5 * L / M;
			D.fit_fun(ff, ud1, ud2);

			if (A.x <= D.x && D.x <= C.x) {
				if (D.y < C.y) {
					B = C;
					C = D;
				}
				else {
					A = D;
				}
			}
			else if (C.x <= D.x && D.x <= B.x)
			{
				if (D.y < C.y) {
					A = C;
					C = D;
				}
				else {
					B = D;
				}
			}
			else {
				Xopt = D2;
				Xopt.flag = 2;
				cout << "\nminimum funkcji(metoda lagrange'a)2: ";
				cout << "\nx: " << Xopt.x << " y: " << Xopt.y << endl;
				cout << "f_calls: " << solution::f_calls << endl;
				cout << B.x - A.x << endl;
				return Xopt;
			}
			Xopt.ud.add_row((B.x - A.x)());
			if (B.x - A.x < epsilon || abs(D.x() - D2.x()) < gamma)
			{
				Xopt = D;
				Xopt.flag = 0;
				cout << B.x - A.x << endl;
				break;
			}
			if (solution::f_calls > Nmax) {
				Xopt = D;
				Xopt.flag = 1;
				cout << B.x - A.x << endl;
				break;
			}
			D2 = D;
			cout << B.x - A.x << endl;
		}
		//cout << B.x - A.x << endl;

		cout << "\nminimum funkcji(metoda legendra): ";
		cout << "\nx: " << Xopt.x << " y: " << Xopt.y << endl;
		cout << "f_calls: " << solution::f_calls << endl;
		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution lag(...):\n" + ex_info);
	}
}

solution HJ(matrix(*ff)(matrix, matrix, matrix), matrix x0, double s, double alpha, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution HJ(...):\n" + ex_info);
	}
}

solution HJ_trial(matrix(*ff)(matrix, matrix, matrix), solution XB, double s, matrix ud1, matrix ud2)
{
	try
	{
		//Tu wpisz kod funkcji

		return XB;
	}
	catch (string ex_info)
	{
		throw ("solution HJ_trial(...):\n" + ex_info);
	}
}

solution Rosen(matrix(*ff)(matrix, matrix, matrix), matrix x0, matrix s0, double alpha, double beta, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution Rosen(...):\n" + ex_info);
	}
}

solution pen(matrix(*ff)(matrix, matrix, matrix), matrix x0, double c, double dc, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try {
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution pen(...):\n" + ex_info);
	}
}

solution sym_NM(matrix(*ff)(matrix, matrix, matrix), matrix x0, double s, double alpha, double beta, double gamma, double delta, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution sym_NM(...):\n" + ex_info);
	}
}

solution SD(matrix(*ff)(matrix, matrix, matrix), matrix(*gf)(matrix, matrix, matrix), matrix x0, double h0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution SD(...):\n" + ex_info);
	}
}

solution CG(matrix(*ff)(matrix, matrix, matrix), matrix(*gf)(matrix, matrix, matrix), matrix x0, double h0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution CG(...):\n" + ex_info);
	}
}

solution Newton(matrix(*ff)(matrix, matrix, matrix), matrix(*gf)(matrix, matrix, matrix),
	matrix(*Hf)(matrix, matrix, matrix), matrix x0, double h0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution Newton(...):\n" + ex_info);
	}
}

solution golden(matrix(*ff)(matrix, matrix, matrix), double a, double b, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution golden(...):\n" + ex_info);
	}
}

solution Powell(matrix(*ff)(matrix, matrix, matrix), matrix x0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution Powell(...):\n" + ex_info);
	}
}

solution EA(matrix(*ff)(matrix, matrix, matrix), int N, matrix limits, int mi, int lambda, matrix sigma0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution EA(...):\n" + ex_info);
	}
}
