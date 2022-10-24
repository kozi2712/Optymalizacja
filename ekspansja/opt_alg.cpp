#include"opt_alg.h"
#include"solution.h"
double* expansion(matrix(*ff)(matrix, matrix, matrix), double x0, double d, double alpha, int Nmax, matrix ud1, matrix ud2)
{

	try
	{
		
		double* p = new double[2]{ 0,0 };
		
		int i = 0;

		solution X0(x0), X1(x0+d);

		X0.fit_fun(ff, 0, 0);
		X1.fit_fun(ff, 0, 0);


		if (X0.y == X1.y) {
			p[0] = m2d(X0.x);
			p[1] = m2d(X0.x);

			return p;
		}
		
		if (X1.y > X0.y) {
			d = -d;
			X1.x = X0.x + d;
			X1.fit_fun(ff, 0, 0);
			if (X0.y <= X1.y) {
				p[0] = m2d(X1.x);
				p[1] = m2d(X0.x) - d;
				return p;
			}
		}
		solution X2;

		while(true){
			i++;
			X2.x = x0 + pow(alpha, i) * d;
			X2.fit_fun(ff, 0, 0);

			if (X2.y >= X1.y || solution::f_calls > Nmax) break;

			X0 = X1;
			X1 = X2;

		} 

		if (d > 0) {
			p[0] = m2d(X2.x);
			p[1] = m2d(X0.x);
			return p;
		}

		p[0] = m2d(X0.x);
		p[1] = m2d(X2.x);
		

		return p;
	}
	catch (string ex_info)
	{
		throw ("double* expansion(...):\n" + ex_info);
	}
}

double fibonacci(int n) {
	if (n == 0) return 0;
	if (n == 1) return 1;
	return (double)(fibonacci(n - 1) + fibonacci(n - 2));
}

solution fib(matrix(*ff)(matrix, matrix, matrix), double a, double b, double epsilon, matrix ud1, matrix ud2)
{
	/*
	L= b-a
	fik > L/epsilon
	*/
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji
		int i = 0, k = 0, fi = 0;
		double tmp2 = 0.;

		solution A(a);
		solution B(b);

		double tmp = (double)(b-a)/epsilon;
		while (true) {
			if (fibonacci(i) > tmp) {
				fi = fibonacci(i);
				break;
			}
			i++;
			k++;
		}
		tmp2 = b - ((fibonacci(k - 1) / fibonacci(k)) * (b - a));
		//cout <<"\ntmp2: " << tmp2;
		solution C(tmp2);
		C.fit_fun(ff);
		tmp2 = a + b - m2d(C.x);
		//cout << "\ntmp2: " << tmp2;
		solution D(tmp2);
		D.fit_fun(ff);


		//cout <<"\nc.x: " << c.x << " d.x: " << d.x << endl;
		//cout << "A.x: " << A.x << "\nB.x: " << B.x << endl;
		for (i = 0; i < k - 3; i++) {
			if (C.y < D.y) {
				A.x = A.x;
				B.x = D.x;
			}
			else {
				B.x = B.x;
				A.x = C.x;
			}
			A.fit_fun(ff);
			B.fit_fun(ff);

			C.x = B.x - ((fibonacci(k - i - 2) / fibonacci(k - i - 1)) * (B.x - A.x));
			D.x = A.x + B.x - C.x;

			C.fit_fun(ff);
			D.fit_fun(ff);
			
			//cout << "---------\nA.x: " << A.x << "\nB.x: " << B.x << "\nC.x: " << C.x << "\nD.x: " << D.x << endl;
		}
		
		Xopt = C;

		//cout << "\nk: " << k << " fi: " << fi << " tmp: " << tmp;
		cout << "minimum funkcji(metoda fibonacciego): ";
		cout << "\nx: " << Xopt.x << " y: " << Xopt.y;

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
		//Tu wpisz kod funkcji
		int i = 0;
		solution A(a);
		solution B(b);
		solution C((a+b)/2);
		solution D;

		double L;
		double M;
		double tmp;

		A.fit_fun(ff);
		B.fit_fun(ff);
		C.fit_fun(ff);

		do {


			L = (m2d(A.y) * (pow(m2d(B.x), 2) - pow(m2d(C.x), 2))) + (m2d(B.y) * (pow(m2d(C.x), 2) + pow(m2d(A.x), 2))) + (m2d(C.y) * (pow(m2d(A.x), 2) - pow(m2d(B.x), 2)));
			M = (m2d(A.y) * (m2d(B.x) - m2d(C.x))) + (m2d(B.y) * (m2d(C.x) - m2d(A.x))) + (m2d(C.y) * (m2d(A.x) - m2d(B.x)));
			cout << L;
			if (M <= 0) {
				cout << "napotkano blad - 1" << endl;
				return 0;
			}
			tmp = m2d(D.x);

			D.x = (0.5 * L) / M;
			D.fit_fun(ff);

			if (A.x < D.x < C.x) {
				if (D.y < C.y) {
					A.x = A.x;
					C.x = D.x;
					B.x = C.x;
				}
				else {
					A.x = D.x;
					C.x = C.x;
					B.x = B.x;
				}
			}
			else if (C.x < D.x < B.x) {
				if (D.y < C.y) {
					A.x = C.x;
					C.x = D.x;
					B.x = B.x;
				}
				else {
					A.x = A.x;
					C.x = C.x;
					B.x = D.x;
				}
			}
			else {
				cout << "Napotkano blad - 2" << endl;
				return 0;
			}
			i++;
			if (solution::f_calls > Nmax) {
				cout << "Napotkano blad - 3" << endl;
				return 0;
			}
			A.fit_fun(ff);
			B.fit_fun(ff);
			C.fit_fun(ff);
			D.fit_fun(ff);

		} while (abs(m2d(B.x) - m2d(A.x)) < epsilon || abs(m2d(D.x - tmp))<gamma);

		Xopt = D;
		cout << "\nminimum funkcji(metoda legendra): ";
		cout << "\nx: " << Xopt.x << " y: " << Xopt.y;
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
