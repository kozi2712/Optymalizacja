/*********************************************
Kod stanowi uzupe�nienie materia��w do �wicze�
w ramach przedmiotu metody optymalizacji.
Kod udost�pniony na licencji CC BY-SA 3.0
Autor: dr in�. �ukasz Sztangret
Katedra Informatyki Stosowanej i Modelowania
Akademia G�rniczo-Hutnicza
*********************************************/

#include"opt_alg.h"

void lab1();
void lab2();
void lab3();
void lab4();
void lab5();
void lab6();

int main()
{
	try
	{
		lab1();
	}
	catch (string EX_INFO)
	{
		cerr << "ERROR:\n";
		cerr << EX_INFO << endl << endl;
	}
	system("pause");
	return 0;
}

void lab1()
{
	double* p = new double[2]{ 0,0 };
	p = expansion(ff1T, 10, 1.0, 1.5, 1000);
	cout << p[1] << "\n";
	cout << p[0] << "\n";

	solution x = fib(ff1T, 10, 100, 1e-5);
	x = lag(ff1T, -100, 100, 0.001, 1e-7, 1000);
}

void lab2()
{

}

void lab3()
{

}

void lab4()
{

}

void lab5()
{

}

void lab6()
{

}
