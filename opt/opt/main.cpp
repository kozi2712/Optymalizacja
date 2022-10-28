/*********************************************
Kod stanowi uzupe³nienie materia³ów do æwiczeñ
w ramach przedmiotu metody optymalizacji.
Kod udostêpniony na licencji CC BY-SA 3.0
Autor: dr in¿. £ukasz Sztangret
Katedra Informatyki Stosowanej i Modelowania
Akademia Górniczo-Hutnicza
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
	//p = expansion(FR, 0, 1.0, 1, 1000);
	//cout << p[1] << "\n";
	//cout << p[0] << "\n";


	double epsilon = 1e-7;
	double gamma = 1e-200;
	int Nmax = 1000;

	//zakomentowane jedno bo f_calls sie sumuje gdy sa obie metody wlaczone
	//solution x = fib(FR, 1e-4, 1e-2, epsilon);
	solution x = lag(FR, 1e-4, 1e-2, epsilon, gamma, Nmax);
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
