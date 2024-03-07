#include "Lab2.h"

// расчет распределения токов в электрической цепи
void Lab2() {
	// исх. данные
	int p = 0;
	int q = 0;
	int m = 5; // кол-во ветвей
	
	cout << "Лабораторная работа №2" << endl << "Расчет распределения токов в электрической цепи" << endl << "Рыжкова Е.А." << endl << endl;
	cout << "Введите p: ";
	cin >> p;
	cout << "Введите q: ";
	cin >> q;

	// массив сопротивлений
	double* r{ new double[m] };

	for (int i = 0; i < m; i++)
	{
		r[i] = p + q + i+1;
		cout << "r[" << i << "] = " << r[i] << endl;
	}

	// массив ЭДС (напряжений на аккумуляторах)
	double* e{ new double[m] };
	e[0] = 2 * (p + q) + 30;
	e[1] = 2 * (p + q) + 60;
	e[2] = 3 * (p + q) + 80;
	e[3] = 8 * (p + q) + 100;

	// вектор-столбец b
	vector<double> b{ 0, 0,  e[0] + e[2], e[1], e[2] + e[3] };

	// CЛАУ (сатане)
	double** A{ new double* [m] {} };
	
	A[0] = new double[m] {1, -1, 0, 0, 1};
	A[1] = new double[m] {-1, 0, 1, -1, 0};
	A[2] = new double[m] {r[0], 0, r[2], 0, -r[4]};
	A[3] = new double[m] {0, r[1], 0, 0, r[4]};
	A[4] = new double[m] {0, 0, r[2], r[3], 0 };

}