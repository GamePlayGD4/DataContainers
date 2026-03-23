#include<iostream>
using std::cout;
using std::cin;
using std::endl;

void Elevator(int floor);
int Factorial(int n);
double Power(double a, int n);

void main()
{
	setlocale(LC_ALL, "");
	//cout << "Hello world!";
	int n;
	int a;
	cout << "Введите основание степени: "; cin >> a;
	cout << "Введите показатель степени: "; cin >> n;
	//Elevator(n);
	//main();
	cout << Power(a, n) << endl;
}

void Elevator(int floor)
{
	if (floor == 0)
	{
		cout << "Вы в подвале" << endl;
		return;
	}
	cout << "Вы на " << floor << " этаже" << endl;
	Elevator(floor - 1);
	cout << "Вы на " << floor << " этаже" << endl;
}

int Factorial(int n)
{
	/*if (n == 0)return 1;
	else return n* Factorial(n - 1);*/
	return n == 0 ? 1 : n * Factorial(n - 1);
}

double Power(double a, int n)
{
	return n == 0 ? 1 : a * Power(a, n - 1);
}