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
	double* b{ new double[m] { 0, 0,  e[0] + e[2], e[1], e[2] + e[3] } };

	// CЛАУ (сатане)
	double** A{ new double* [m] {} };
	
	A[0] = new double[m] {1, -1, 0, 0, 1};
	A[1] = new double[m] {-1, 0, 1, -1, 0};
	A[2] = new double[m] {r[0], 0, r[2], 0, -r[4]};
	A[3] = new double[m] {0, r[1], 0, 0, r[4]};
	A[4] = new double[m] {0, 0, r[2], r[3], 0 };

	double* i = Gaousse(A, b, m);
	cout << "Значение тока в цепях:" << endl;
	for (int k = 0; k < m; k++)
	{
		cout << "i[" << k + 1 << "] = " << i[k] << endl;
	}
	
	// расчет напряжения на частично разряженном втором аккумуляторе
	Zad2(r, e, i, m);
}

// метод гауссенка
double* Gaousse(double** a, double* b, int n) {
		
	for (int k = 0; k < n; k++)
	{
		if (a[k][k] == 0) { // Проверка ведущего элемента
			double max = 0;
			int imax = k;

			for (int i = k + 1; i < n; i++)
			{
				if (abs(a[i][k]) > max) {
					max = abs(a[i][k]);
					imax = i;
				}
			}
			// Меняем уравнения местами
			double v;
			for (int j = k; j < n; j++)
			{
				v = a[k][j];
				a[k][j] = a[imax][j];
				a[imax][j] = v;
			}

			v = b[k];
			b[k] = b[imax];
			b[imax] = v;

		}

		double akk = a[k][k];
		b[k] /= akk; // Делим правую часть на ведущий элемент
		for (int j = k; j < n; j++)
		{
			a[k][j] /= akk; // Делим текущую строку на ведущий элемент
		}

		for (int i = k + 1; i < n; i++)
		{
			//Перебираем последующие строки, получаем 0 в k-ом столбце 
			if (a[i][k] != 0)
			{
				double aik = a[i][k];
				b[i] /= aik;
				b[i] -= b[k];
				for (int j = k; j < n; j++)
				{
					a[i][j] /= aik;
					a[i][j] -= a[k][j];
				}
			}
		}

		
	}

	for (int i = n - 2; i >= 0; i--)
	{
		for (int j = i + 1; j < n; j++)
		{
			b[i] -= a[i][j] * b[j];
		}
	}

	return b;
}

// расчет ЭДС (вход: массив напряжений, 
void Zad2(double* r, double* e, double* i, int m) {
	// напряжение е2
	double e2;
	// Задаем массив ЭДС с учетом уменьшения до 80%
	for (int k = 0; k < m; k++)
	{
		e[k] *= 0.8;
	}
	// Фиксируем значение тока в первой ветви
	double i1 = i[0] * 0.8;

	double** A{ new double* [m] {} };

	A[0] = new double[m] {0, 0, 1, -1, 0};
	A[1] = new double[m] {0, -1, 0, 0, 1};
	A[2] = new double[m] {0, 0, r[2], 0, -r[4]};
	A[3] = new double[m] {-1, r[1], 0, 0, r[4]};
	A[4] = new double[m] {0, 0, r[2], r[3], 0};

	// вектор-столбец b
	double* b{ new double[m] { i1, -i1,  e[0] + e[2] - (r[0] * i1), 0, e[2] + e[3] } };

	double* i_2 = Gaousse(A, b, m);
	cout << "Значение тока в цепях:" << endl;
	for (int k = 0; k < m; k++)
	{
		cout << "i[" << k + 1 << "] = " << i_2[k] << endl;
	}

	cout << "ЕДС: " << i_2[0] << endl;
}