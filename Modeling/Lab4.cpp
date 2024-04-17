#include "Lab4.h"
#include "Includes.h"
#define ro 0.00785 // ���������

void Lab4()
{
	// ���. ������
	int p = 0;
	int q = 0;
	int n = 20; // ���-�� ����� ���������

	cout << "������������ ������ �4" << endl << "������ ����� �������� ������" << endl << "������� �.�." << endl << endl;
	cout << "������� p: ";
	cin >> p;
	cout << "������� q: ";
	cin >> q;

	double l = 10 + p + q; // ����� ������ � ���������
	double Vrect = V_rectangle(f, l, n, p, q); // ����� �� ���������������
	double Vtrapez = V_trapezoid(f, l, n, p, q); // ����� �� ���������
	double Mass_detale_rect = Vrect * ro; // ����� ������ �� ���������������
	double mass_detale_trapez = Vtrapez * ro; // ����� ������ �� ���������

	// �� ��������
	double mass_preparat_cyl = Mass_preparation_cyl(f, l, p, q); // ����� ��������� ��������
	double Mass_wastes_cyl_rect = mass_preparat_cyl - Mass_detale_rect; // ����� ������� �� ���������������
	double mass_wastes_cyl_trapez = mass_preparat_cyl - mass_detale_trapez; // ����� ������� �� ���������

	// �� ������
	double mass_preparat_konus = Mass_preparation_konus(f, l, p, q); // ����� ��������� ������
	double mass_wastes_konus_rect = mass_preparat_konus - Mass_detale_rect; // ����� ������� �� ���������������
	double mass_wastes_konus_trapez = mass_preparat_konus - mass_detale_trapez; // ����� ������� �� ���������

	//// �������� //
	//cout << "V rectangle: " << Vrect << endl;
	//cout << "V trapezoid: " << Vtrapez << endl;

	// ����� ����������� //

	cout << setw(60) << left << "����� ������ �� �������" << setw(70) << "����� ��������� / ����� ������� ��������������" << setw(20)<< "�����������" << endl;
	cout << setw(60) << " " << setw(35) << "��������������" << setw(35) << "��������������" << endl;
	cout << setw(60) << " " << setw(35) << mass_preparat_cyl << setw(35)<< mass_preparat_konus << endl;
	cout << setw(40) << left << "���������������" << setw(20) << Mass_detale_rect << setw(35) << Mass_wastes_cyl_rect <<setw(35)<< mass_wastes_konus_rect << setw(20) << (Mass_wastes_cyl_rect - mass_wastes_konus_rect) << endl;
	cout << setw(40) << left << "��������" << setw(20) << mass_detale_trapez << setw(35) << mass_wastes_cyl_trapez << setw(35) << mass_wastes_konus_trapez << (mass_wastes_cyl_trapez - mass_wastes_konus_trapez) << endl;

	cout << setw(60) << left << "����� ������ �� �������" << setw(70) << "����� ��������� / ���� ������� �������������� (%)" << setw(20) << "�����������" << endl;
	cout << setw(60) << " " << setw(35) << "��������������" << setw(35) << "��������������" << endl;
	cout << setw(60) << " " << setw(35) << mass_preparat_cyl << setw(35) << mass_preparat_konus << endl;
	cout << setw(40) << left << "���������������" << setw(20) << Mass_detale_rect << setw(35) << round(((Mass_wastes_cyl_rect * 100) / mass_preparat_cyl) * 100) / 100
		<< setw(35) << round(((mass_wastes_konus_rect * 100) / mass_preparat_konus) * 100) / 100 <<setw(20)<< (round(((Mass_wastes_cyl_rect * 100) / mass_preparat_cyl) * 100) / 100 - (round(((mass_wastes_konus_rect * 100) / mass_preparat_konus) * 100) / 100)) << endl;
	cout << setw(40) << left << "��������" << setw(20) << mass_detale_trapez << setw(35) << round(((mass_wastes_cyl_trapez * 100) / mass_preparat_cyl) * 100) / 100
		<< setw(35) << round(((mass_wastes_konus_trapez * 100) / mass_preparat_konus) * 100) / 100 << setw(20)<< (round(((mass_wastes_cyl_trapez * 100) / mass_preparat_cyl) * 100) / 100)-(round(((mass_wastes_konus_trapez * 100) / mass_preparat_konus) * 100) / 100) << endl;

	cout << endl << "������������� ����������� ��������� ������� ���������� ������ ������:" << endl;
	cout << setw(40) << left << "��� ���������� ���������������: " << setw(20) << Error_rate(p, q, l, Vrect) << endl;
	cout << setw(40) << left << "��� ���������� ��������: " << setw(20) << Error_rate(p, q, l, Vtrapez) << endl;
}

// ������� f(x)
double f(double x, int p, int q) {
	double alpha = 1 + 0.1 * ((double)p + (double)q + 2);
	double A = (0.2 * ((double)p + (double)q + 1)) ; // c�
	double B = (5 + (double)p + (double)q); // c�

	return A * pow(x, alpha) + B;
}

// ����� ��������� ��������
double Mass_preparation_cyl(function<double(double, int, int)> f, double l, int p, int q) {
	double R = f(l, p, q); // ������ ��������� ��������
	double V0 = M_PI * pow(R, 2) * l; // ����� ���������

	return ro * V0; // ����� ���������
}

// ����� ��������� ������
double Mass_preparation_konus(function<double(double, int, int)> f, double l, int p, int q) {
	double R = f(l, p, q); // ������ �������� ���������
	double r = f(0, p, q); // ������ �������� ���������
	double V0 = 0.3333 * M_PI * l * (pow(R, 2) + R * r + pow(r, 2)); // ����� ������

	return ro * V0; // ����� ���������
}

// ����� ����� ������� ���������������
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

// ����� ����� ������� ��������
double V_trapezoid(function<double(double, int, int)> f, double L, int n, int p, int q) {
	double h = L / n;
	double F_x0 = pow(f(0, p, q),2); // F(x0) ��� � = 0
	
	double s = 0;
	for (int k = 1; k <= n-1; k++)
	{
		double x = k * h;
		s += pow(f(x, p, q), 2);
	}

	double F_xn = pow(f(L, p, q),2);
	return M_PI * h * (0.5*F_x0 + s + 0.5*F_xn);
}

// ������ ����� ������
double V_correct(double l, int p, int q) {
	double alpha = 1 + 0.1 * ((double)p + (double)q + 2);
	double A = (0.2 * ((double)p + (double)q + 1)); // c�
	double B = (5 + (double)p + (double)q); // c�

	double x = pow(A, 2) * (pow(l, 2 * alpha + 1) / (2 * alpha + 1));
	double y = 2 * A * B * (pow(l, alpha + 1) / (alpha + 1));
	double z = pow(B, 2) * l;

	return M_PI * (x+y+z);
}

// ������� �����������
double Error_rate(int p, int q, double l, double V_about) {
	double V = V_correct(l, p, q);
	double x = abs(V - V_about) / V;

	return x*100;
}