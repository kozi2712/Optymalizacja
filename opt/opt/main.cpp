/*********************************************
Kod stanowi uzupe³nienie materia³ów do æwiczeñ
w ramach przedmiotu metody optymalizacji.
Kod udostêpniony na licencji CC BY-SA 3.0
Autor: dr in¿. £ukasz Sztangret
Katedra Informatyki Stosowanej i Modelowania
Akademia Górniczo-Hutnicza
*********************************************/

#include"opt_alg.h"
#include <stdlib.h>  
#include <time.h>

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
	double x0 = 0;
	double d = 1;
	double alpha = 3;
	double epsilon = 1e-10;
	double gamma = 1e-200;
	int Nmax = 1000;
	double* p = new double[2]{ 0,0 };
	srand(time(NULL));

	// Macierz do przechowania wyniku
		matrix ab_F(1, 1, 200);

	//Wywo³anie metody Fibonacciego dla przedzia³i -100, 100
	solution opt_F = fib(ff1T, -100.0, 100.0, 1e-5, ab_F);

	//Wypisanie wszystkich iteracji
	std::cout << ab_F << endl;

	int fibCalls = solution::f_calls;
	solution::clear_calls();
	std::cout << std::endl;

	//Wypisanie znalezionego minimum
	std::cout << opt_F.x << ";" << opt_F.y << ";" << fibCalls << std::endl;

	//Macierz do przechowania wyniku
	matrix ab_L(1, 1, 200);

	//Wywo³anie metody Lagrange’a dla przedzia³i -100, 100
	solution opt_L = lag(ff1T, -100.0, 100.0, 1e-5, 1e-200, 1000, ab_L);

	//Wypisanie wszystkich iteracji
	std::cout << ab_L << endl;

	int lagCalls = solution::f_calls;
	solution::clear_calls();
	std::cout << std::endl;

	//Wypisanie znalezionego minimum
	std::cout << opt_L.x << ";" << opt_L.y << ";" << lagCalls << std::endl;

	//Metoda Fibonacciego

//Wyznaczenie optymalnego DA z przedzia³u 1cm^2 do 100cm^2
	/*
	solution opt_F = fib(FR, 0.0001, 0.01, 1e-5);

	int fibCalls = solution::f_calls;

	solution::clear_calls();

	//Metoda Lagrange’a

	//Wyznaczenie optymalnego DA z przedzia³u 1cm^2 do 100cm^2

	solution opt_L = lag(FR, 0.0001, 0.01, 1e-5, 1e-200, 1000);

	int lagCalls = solution::f_calls;

	solution::clear_calls();

	//Otwarcie pliku i zapis do pliku

	ofstream S("rzeczywisty.csv");
	S << "Fib;" << opt_F.x << opt_F.y << fibCalls << "\n";
	S << "Lag;" << opt_L.x << opt_L.y << lagCalls << "\n";
	S << "\n";

	//Warunki pocz¹tkowe

	matrix Y0 = matrix(3, new double[3]{ 5, 1, 10 });

	//Symulacja dla znalezionego optymalnego otworu metod¹ Fibonacciego

	matrix* Y_fib = solve_ode(df1, 0, 1, 1000, Y0, 0, opt_F.x);

	//Symulacja dla znalezionego optymalnego otworu metod¹ Lagrange’a

	matrix* Y_lag = solve_ode(df1, 0, 1, 1000, Y0, 0, opt_L.x);

	//Zapis wyników do pliku
	S << "Fib\nt\n" << Y_fib[0] << "\nVA;VB;TB\n" << Y_fib[1] << "Lag\nt\n"
		<< Y_lag[0] << "\nVA;VB;TB\n" << Y_lag[1];
	S.close();*/

	
	
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
