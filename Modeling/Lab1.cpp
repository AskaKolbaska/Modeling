#include "Lab1.h"

void Lab1() {
	RusConsole();
	int p = 1, q = 1; // исх. данные 

	cout << "Ћабораторна€ работа є1" << endl << "ћоделирование средств на вкладе" << endl << "–ыжкова ≈.ј." << endl << endl;

	cout << "¬ведите p: ";
	cin >> p;
	cout << "¬ведите q: ";
	cin >> q;

	Zad1(p, q);
	Zad2(p, q);
}

// приращение вклада
double CountR(int p, int q) {
	return ((double)p + (double)q + 1) / 100;
}

// задача 1 (найти врем€ дл€ увеличени€ вклада)
void Zad1(int p, int q) {
	int z0 = 100 + 4 * p + 3 * q + 1; // начальный вклад

	cout << endl << "«адание 1: найти кол-во лет" << endl << endl;

	cout << "—лучай 1 (без доп. взносов)" << endl << endl;
	cout << "¬рем€ увеличени€ вклада в 2 раза: " << TimeFor2(z0, p, q) << endl;
	cout << "¬рем€ увеличени€ вклада в 5 раз: " << TimeFor5(z0, p, q) << endl;
	cout << endl << "—лучай 2 (с доп. взносами)" << endl << endl;
	cout << "¬рем€ увеличени€ вклада в 2 раза: " << TimeFor2_Add(z0, p, q) << endl;
	cout << "¬рем€ увеличени€ вклада в 5 раз: " << TimeFor5_Add(z0, p, q) << endl;
}

// задача 2 (найти начальный вклад)
void Zad2(int p, int q) {
	int t = 5; // 5 лет
	double y = 10 * (100 + 4 * p + 3 * q + 1); // итогова€ сумма

	cout << endl << "«адание 2: найти первоначальный вклад" << endl << endl;

	double z0 = 10 * y * pow(CountR(p, q), 2) / (10 * CountR(p, q) * (1 + 1 / (10 * CountR(p, q))) * pow(1 + CountR(p, q), t + 1) - t * CountR(p, q) - 1);
	cout << "Ќачальный вклад должен составл€ть: " << z0 << endl;
}

// случай увеличени€ вклада в 2 раза (без доп. внесений)
int TimeFor2(int z0, int p, int q) {
	double y = (double)z0 * 2; // итого получилось денег
	double t = ceil(log10(y / (double)z0) / log10(1 + CountR(p, q)));

	return t;
}

// случай увеличени€ вклада в 5 раза (без доп. внесений)
int TimeFor5(int z0, int p, int q) {
	double y = (double)z0 * 5; // итого получилось денег
	double t = ceil(log10(y / (double)z0) / log10(1 + CountR(p, q)));

	return t;
}

// случай увеличени€ вклада в 2 раза (c доп. внесени€ми)
int TimeFor2_Add(int z0, int p, int q) {
	double y = (double)z0 * 2; // итого получилось денег
	double y_t = 0; // деньги за каждый год
	int i = 0; // индекс (года)
	double r = CountR(p, q);

	do
	{
		i++;
		y_t = (z0 / r) * (1 + 1 / (10 * r)) * pow(1 + r, i + 1)
			- (z0 * i) / (10 * r) - (z0 / (10 * pow(r, 2))) * (1 + 11 * r);

	} while (y_t < y);

	return i;
}

// случай увеличени€ вклада в 5 раза (c доп. внесени€ми)
int TimeFor5_Add(int z0, int p, int q) {
	double y = (double)z0 * 5; // итого получилось денег

	double y_t = 0; // деньги за каждый год
	int i = 0; // индекс (года)
	double r = CountR(p, q);

	do
	{
		i++;
		y_t = (z0 / r) * (1 + 1 / (10 * r)) * pow(1 + r, i + 1)
			- (z0 * i) / (10 * r) - (z0 / (10 * pow(r, 2))) * (1 + 11 * r);

	} while (y_t < y);

	return i;
}

void RusConsole() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}