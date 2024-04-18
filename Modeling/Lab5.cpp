#include "Lab5.h"
#define g 9.8
#define tau 0.2

// �������������
void Lab5()
{
	int p = 0;
	int q = 0;

	cout << "������������ ������ �5" << endl << "������������� �������� �������������� ������� ��� ������������" << endl << "������� �.�." << endl << endl;
	cout << "������� p: ";
	cin >> p;
	cout << "������� q: ";
	cin >> q;

	// ���. ������
	double H = 5 * pow(20 + 2 * p + q, 2); // ������ ������ ��������
	double Vc = round(((600 + static_cast<double>(2) * p + 4 * q) * 10 / 36)*100)/100;// �������� ������ ��������
	double Vk = round(((static_cast<double>(60) + p + q) * 10 / 36)*100)/100; // �������� �������
	double m = 200 + 20 * p + 10 * q; // ����� �������
	double k1 = 0.2 + 0.1 * p, k2 = 0.04 + 0.01 * p;// ������������

	// ����������
	vector<double> k; // ����� ����
	vector<double> t; // ������� �������
	vector<double> x; // �-���������� �������� ������� (��� �� ���������� ����)
	vector<double> y; // �-���������� (��� �� ���������� �� �������� ��������)
	vector<double> h; // ������ ������� � ������ ������� t
	vector<double> v; // ��������

	// ����� �������� ������
	cout << "p = " << p << endl;
	cout << "q = " << q << endl;
	cout << "m = " << m << " ��" << endl;
	cout << "V ������� = " << Vk << " �/�" << endl;
	cout << "V �������� = " << Vc << " �/�" << endl << endl;

	cout << "k1 = " << k1 << endl;
	cout << "k2 = " << k2 << endl;
	cout << "tau = " << tau << endl;
	cout << "g = " << g << endl;
	cout << "H = " << H << " �" << endl<<endl;

	// ���������� ������ ����� ������
	Scheme_Euler(m, &H,Vc, k1, k2, &k, &t, &x, &y, &v, &h);

	// ����� ����������� //
	cout << setw(5) << "k" << setw(5) << "t, c" << setw(10) << "v, �/�" << setw(10) << "x, �" << setw(10) << "y, �" << setw(10) << "h, �" << endl;
	for (int i = 0; i < k.size(); i++)
	{
		cout << setw(5) << k[i] << setw(5) << t[i] << setw(10) << v[i] << setw(10) << x[i] << setw(10) << y[i] << setw(10) << h[i] << endl;
	}

	double t_padenie = t.end()[-2] - ((h.end()[-2] / (h.end()[-1] - h.end()[-2])) * (t.end()[-1] - t.end()[-2]));

	double l_snaryad = Vc * t_padenie; // ��������� ������ �������
	double l_kolonna = Vk * t_padenie; // ���������� ���������� ��������

	double l = l_snaryad - l_kolonna;

	cout << endl;
	cout << "����� ������� �������: " << t_padenie << " �" << endl;
	cout << "����������: " << l << " �" << endl;


}

// ������ ����� ������
void Scheme_Euler(double m, double* H, double Vc, double k1, double k2, vector<double>* k,vector<double>* t, vector<double>* x, vector<double>* y, vector<double>* v, vector<double>* h) {
	int k_ex = 0;
	double y_ex;

	t->push_back(k_ex); // t0 = 0
	k->push_back(k_ex);

	y->push_back(k_ex); // y0 = 0

	v->push_back(0);
	x->push_back(0);
	h->push_back(*H);

	do
	{
		k_ex++;
		k->push_back(k_ex);
		t->push_back(t->front() + tau * k_ex);

		double v_ex = v->back() + 0.2 * (g - (1 / m) * (k1 * v->back() + k2 * pow(v->back(), 2)));
		double x_ex = x->back() + tau * v->back();
		y_ex = Vc * t->back();
		x->push_back(x_ex);
		v->push_back(v_ex);
		y->push_back(y_ex);
		h->push_back(h->front() - x->back());
	} while (h->back() > 0);
}