#include "Lab2.h"
#include "Lab3.h"
#include "Includes.h"

void Lab3()
{
	cout << "Лабораторная работа №3" << endl << "Анализ временных рядов" << endl << "Рыжкова Е.А." << endl << endl;

	// исх. данные
	int p = 0;
	int q = 0;

	cout << "Введите p: ";
	cin >> p;
	cout << "Введите q: ";
	cin >> q;

	double* t = new double[6]; // временной массив
	double* y = new double[5]; // массив объемов продукции
	double* linear = new double[2]; // вектор коэффициентов линейного тренда
	double* kvadra = new double[3]; // коэффициенты квадратичного тренда

	// результат
	double* trL = new double[6]; // массив значений линейного тренда
	double* erL = new double[5]; // массив значений погрешностей
	double trKv[6]; // массив значений квадратичного тренда
	double erKv[5]; // массив значений погрешностей
	double maxEr = 0; // максимальная погрешность
	double maxEr_kv = 0; // максимальная погрешность

	// вычисления
	
	// заполенение исх. данных
	for (int i = 0; i < 5; i++)
	{
		t[i] = i + 1;
		y[i] = 10 + 0.05 * (p + 2 * q + 1) * t[i] + 0.01 * (p + q + 1) * pow(t[i], 2) + 0.02 * (2 * p + q + 1) * pow(-1, t[i]);
	}
	t[5] = 6;

	// получение линейного тренда
	linear = MNK(t, y, 1, 5);

	// вывод промежуточного отчета
	cout << endl << "Коэффициенты линейного тренда" << endl;
	for (int k = 0; k  < 2; k ++)
	{
		cout << linear[k] << endl;
	}

	// Вычисляем значения линейного тренда с использованием найденных коэффициентов
	for (int k = 0; k < 6; k++)
	{
		trL[k] = linear[0] + linear[1] * t[k];
	}

	// погрешности линейного тренда
	for (int i = 0; i < 5; i++)
	{
		double x = abs(trL[i] - y[i]) / y[i];
		erL[i] = round(x * 10000) / 10000;
	}

	// максимальная погрешность
	for (int i = 0; i < 5; i++)
	{
		if (maxEr < erL[i]) {
			maxEr = erL[i];
		}
	}

	kvadra = MNK(t, y, 2, 5);
	// вывод промежуточного отчета
	cout << endl << "Коэффициенты квадратичного тренда" << endl;
	for (int k = 0; k < 2; k++)
	{
		cout << kvadra[k] << endl;
	}

	// значения квадратичного тренда
	for (int k = 0; k < 6; k++)
	{
		trKv[k] = kvadra[0] + kvadra[1] * t[k] + kvadra[2] * pow(t[k], 2);
	}

	// погрешности квадратичного тренда
	for (int i = 0; i < 5; i++)
	{
		double x = abs(trKv[i] - y[i]) / y[i];
		erKv[i] = round(x * 10000) / 10000;
	}

	// максимальная погрешность
	for (int i = 0; i < 5; i++)
	{
		if (maxEr_kv < erKv[i]) {
			maxEr_kv = erKv[i];
		}
	}

	cout << "РЕЗУЛЬТАТЫ" << endl << endl;
	cout << setw(50) << left << "Месяцы:";
	for (int i = 0; i < 6; i++)
	{
		cout << setw(10) << t[i];
	}
	cout << endl;
	cout << setw(50) << left << "Объем выпуска (y[k]), тыс. шт.:";
	for (int i = 0; i < 5; i++)
	{
		cout << setw(10) << y[i];
	}
	cout << endl;

	cout << setw(50) << left << "Линейный тренд:";
	for (int i = 0; i < 6; i++)
	{
		cout << setw(10) << trL[i];
	}
	cout << endl;

	cout << setw(50) << left << "Квадратичный тренд:";
	for (int i = 0; i < 6; i++)
	{
		cout << setw(10) << trKv[i];
	}
	cout << endl;

	cout << setw(50) << left << "Погрешность линейного тренда в точках:";
	for (int i = 0; i < 5; i++)
	{
		cout << setw(10) << erL[i];
	}
	cout << endl;

	cout << setw(50) << left << "Погрешность квадратичного тренда в точках:";
	for (int i = 0; i < 5; i++)
	{
		cout << setw(10) << erKv[i];
	}
	cout << endl;

	cout << setw(50) << left << "Погрешность линейного тренда:" << setw(10) << maxEr<<endl;
	cout << setw(50) << left << "Погрешность квадратичного тренда:" << setw(10) << maxEr_kv << endl;
}

// коэффициенты полинома
double* MNK(double* t, double* y, int m, int y_n) {
	// Количество коэффициентов в полиноме на единицу больше, чем максимальная степень
	int n = m + 1;

	// выделяем память под СЛАУ (сатане)
	double** A{ new double* [n] {} };
	for (int i = 0; i < n; i++)
	{
		A[i] = new double[n];
	}
	double* b = new double[n];

	// формируем СЛАУ
	for (int i = 0; i < n; i++)
	{
		double s;
		for (int j = 0; j < n; j++)
		{
			// элемент A[i][j]
			s = 0;
			for (int k = 0; k < y_n; k++)
			{
				s += pow(t[k], i + j);
			}
			A[i][j] = s;
		}

		// элемент b[i]
		double s_2 = 0;
		for (int k = 0; k < y_n; k++)
		{
			s_2 += pow(t[k], i) * y[k];
		}
		b[i] = s_2;
	}

	double* c{ new double {} };
	c = Gaousse(A, b, n);

	return c;
}