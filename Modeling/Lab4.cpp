#include "Lab4.h"
#include "Includes.h"
#define ro 0.00785 // плотность

void Lab4()
{
	// исх. данные
	int p = 0;
	int q = 0;
	int n = 20; // кол-во точек разбиения

	cout << "Лабораторная работа №4" << endl << "Расчет массы стальной детали" << endl << "Рыжкова Е.А." << endl << endl;
	cout << "Введите p: ";
	cin >> p;
	cout << "Введите q: ";
	cin >> q;

	double l = 10 + p + q; // длина детали и заготовки
	double Vrect = V_rectangle(f, l, n, p, q); // объем по прямоугольникам
	double Vtrapez = V_trapezoid(f, l, n, p, q); // объем по трапециям
	double Mass_detale_rect = Vrect * ro; // масса детали по прямоугольникам
	double mass_detale_trapez = Vtrapez * ro; // масса детали по трапециям

	// из цилиндра
	double mass_preparat_cyl = Mass_preparation_cyl(f, l, p, q); // масса заготовки цилиндра
	double Mass_wastes_cyl_rect = mass_preparat_cyl - Mass_detale_rect; // масса отходов по прямоугольникам
	double mass_wastes_cyl_trapez = mass_preparat_cyl - mass_detale_trapez; // масса отходов по трапециям

	// из конуса
	double mass_preparat_konus = Mass_preparation_konus(f, l, p, q); // масса заготовки конуса
	double mass_wastes_konus_rect = mass_preparat_konus - Mass_detale_rect; // масса отходов по прямоугольникам
	double mass_wastes_konus_trapez = mass_preparat_konus - mass_detale_trapez; // масса отходов по трапециям

	//// ПРОВЕРКА //
	//cout << "V rectangle: " << Vrect << endl;
	//cout << "V trapezoid: " << Vtrapez << endl;

	// ВЫВОД РЕЗУЛЬТАТОВ //

	cout << setw(60) << left << "Масса детали по формуле" << setw(70) << "Масса заготовки / масса отходов цилиндрическая" << setw(20)<< "Расхождения" << endl;
	cout << setw(60) << " " << setw(35) << "цилиндрическая" << setw(35) << "конусообразныя" << endl;
	cout << setw(60) << " " << setw(35) << mass_preparat_cyl << setw(35)<< mass_preparat_konus << endl;
	cout << setw(40) << left << "Прямоугольников" << setw(20) << Mass_detale_rect << setw(35) << Mass_wastes_cyl_rect <<setw(35)<< mass_wastes_konus_rect << setw(20) << (Mass_wastes_cyl_rect - mass_wastes_konus_rect) << endl;
	cout << setw(40) << left << "Трапеций" << setw(20) << mass_detale_trapez << setw(35) << mass_wastes_cyl_trapez << setw(35) << mass_wastes_konus_trapez << (mass_wastes_cyl_trapez - mass_wastes_konus_trapez) << endl;

	cout << setw(60) << left << "Масса детали по формуле" << setw(70) << "Масса заготовки / доля отходов цилиндрическая (%)" << setw(20) << "Расхождения" << endl;
	cout << setw(60) << " " << setw(35) << "цилиндрическая" << setw(35) << "конусообразныя" << endl;
	cout << setw(60) << " " << setw(35) << mass_preparat_cyl << setw(35) << mass_preparat_konus << endl;
	cout << setw(40) << left << "Прямоугольников" << setw(20) << Mass_detale_rect << setw(35) << round(((Mass_wastes_cyl_rect * 100) / mass_preparat_cyl) * 100) / 100
		<< setw(35) << round(((mass_wastes_konus_rect * 100) / mass_preparat_konus) * 100) / 100 <<setw(20)<< (round(((Mass_wastes_cyl_rect * 100) / mass_preparat_cyl) * 100) / 100 - (round(((mass_wastes_konus_rect * 100) / mass_preparat_konus) * 100) / 100)) << endl;
	cout << setw(40) << left << "Трапеций" << setw(20) << mass_detale_trapez << setw(35) << round(((mass_wastes_cyl_trapez * 100) / mass_preparat_cyl) * 100) / 100
		<< setw(35) << round(((mass_wastes_konus_trapez * 100) / mass_preparat_konus) * 100) / 100 << setw(20)<< (round(((mass_wastes_cyl_trapez * 100) / mass_preparat_cyl) * 100) / 100)-(round(((mass_wastes_konus_trapez * 100) / mass_preparat_konus) * 100) / 100) << endl;

	cout << endl << "Относительная погрешность численных методов вычисления объема детали:" << endl;
	cout << setw(40) << left << "Для квадратуры прямоугольников: " << setw(20) << Error_rate(p, q, l, Vrect) << endl;
	cout << setw(40) << left << "Для квадратуры трапеций: " << setw(20) << Error_rate(p, q, l, Vtrapez) << endl;
}

// функция f(x)
double f(double x, int p, int q) {
	double alpha = 1 + 0.1 * ((double)p + (double)q + 2);
	double A = (0.2 * ((double)p + (double)q + 1)) ; // cм
	double B = (5 + (double)p + (double)q); // cм

	return A * pow(x, alpha) + B;
}

// масса заготовки цилиндра
double Mass_preparation_cyl(function<double(double, int, int)> f, double l, int p, int q) {
	double R = f(l, p, q); // радиус основания цилиндра
	double V0 = M_PI * pow(R, 2) * l; // объем заготовки

	return ro * V0; // масса заготовки
}

// масса заготовки конуса
double Mass_preparation_konus(function<double(double, int, int)> f, double l, int p, int q) {
	double R = f(l, p, q); // радиус большого основания
	double r = f(0, p, q); // радиус меньшего основания
	double V0 = 0.3333 * M_PI * l * (pow(R, 2) + R * r + pow(r, 2)); // объем конуса

	return ro * V0; // масса заготовки
}

// объем через формулу прямоугольников
double V_rectangle(function<double(double, int, int)> f, double L, int n, int p, int q) {
	double h = L / n;
	double s = 0;
	double x = 0;
	for (int k = 1; k <= n; k++)
	{
		x = k * h;
		s += pow(f(x, p, q),2);
	}
	return M_PI * h * s;
}

// объем через формулу трапеций
double V_trapezoid(function<double(double, int, int)> f, double L, int n, int p, int q) {
	double h = L / n;
	double F_x0 = pow(f(0, p, q),2); // F(x0) при х = 0
	
	double s = 0;
	for (int k = 1; k <= n-1; k++)
	{
		double x = k * h;
		s += pow(f(x, p, q), 2);
	}

	double F_xn = pow(f(L, p, q),2);
	return M_PI * h * (0.5*F_x0 + s + 0.5*F_xn);
}

// точный объем детали
double V_correct(double l, int p, int q) {
	double alpha = 1 + 0.1 * ((double)p + (double)q + 2);
	double A = (0.2 * ((double)p + (double)q + 1)); // cм
	double B = (5 + (double)p + (double)q); // cм

	double x = pow(A, 2) * (pow(l, 2 * alpha + 1) / (2 * alpha + 1));
	double y = 2 * A * B * (pow(l, alpha + 1) / (alpha + 1));
	double z = pow(B, 2) * l;

	return M_PI * (x+y+z);
}

// процент расхождения
double Error_rate(int p, int q, double l, double V_about) {
	double V = V_correct(l, p, q);
	double x = abs(V - V_about) / V;

	return x*100;
}