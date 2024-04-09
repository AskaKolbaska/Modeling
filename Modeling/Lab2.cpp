#include "Lab2.h"

// ������ ������������� ����� � ������������� ����
void Lab2() {
	// ���. ������
	int p = 0;
	int q = 0;
	int m = 5; // ���-�� ������
	
	cout << "������������ ������ �2" << endl << "������ ������������� ����� � ������������� ����" << endl << "������� �.�." << endl << endl;
	cout << "������� p: ";
	cin >> p;
	cout << "������� q: ";
	cin >> q;

	// ������ �������������
	double* r{ new double[m] };

	for (int i = 0; i < m; i++)
	{
		r[i] = p + q + i+1;
		cout << "r[" << i << "] = " << r[i] << endl;
	}

	// ������ ��� (���������� �� �������������)
	double* e{ new double[m] };
	e[0] = 2 * (p + q) + 30;
	e[1] = 2 * (p + q) + 60;
	e[2] = 3 * (p + q) + 80;
	e[3] = 8 * (p + q) + 100;

	// ������-������� b
	double* b{ new double[m] { 0, 0,  e[0] + e[2], e[1], e[2] + e[3] } };

	// C��� (������)
	double** A{ new double* [m] {} };
	
	A[0] = new double[m] {1, -1, 0, 0, 1};
	A[1] = new double[m] {-1, 0, 1, -1, 0};
	A[2] = new double[m] {r[0], 0, r[2], 0, -r[4]};
	A[3] = new double[m] {0, r[1], 0, 0, r[4]};
	A[4] = new double[m] {0, 0, r[2], r[3], 0 };

	double* i = Gaousse(A, b, m);
	cout << "�������� ���� � �����:" << endl;
	for (int k = 0; k < m; k++)
	{
		cout << "i[" << k + 1 << "] = " << i[k] << endl;
	}
	
	// ������ ���������� �� �������� ����������� ������ ������������
	Zad2(r, e, i, m);
}

// ����� ���������
double* Gaousse(double** a, double* b, int n) {
		
	for (int k = 0; k < n; k++)
	{
		if (a[k][k] == 0) { // �������� �������� ��������
			double max = 0;
			int imax = k;

			for (int i = k + 1; i < n; i++)
			{
				if (abs(a[i][k]) > max) {
					max = abs(a[i][k]);
					imax = i;
				}
			}
			// ������ ��������� �������
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
		b[k] /= akk; // ����� ������ ����� �� ������� �������
		for (int j = k; j < n; j++)
		{
			a[k][j] /= akk; // ����� ������� ������ �� ������� �������
		}

		for (int i = k + 1; i < n; i++)
		{
			//���������� ����������� ������, �������� 0 � k-�� ������� 
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

// ������ ��� (����: ������ ����������, 
void Zad2(double* r, double* e, double* i, int m) {
	// ���������� �2
	double e2;
	// ������ ������ ��� � ������ ���������� �� 80%
	for (int k = 0; k < m; k++)
	{
		e[k] *= 0.8;
	}
	// ��������� �������� ���� � ������ �����
	double i1 = i[0] * 0.8;

	double** A{ new double* [m] {} };

	A[0] = new double[m] {0, 0, 1, -1, 0};
	A[1] = new double[m] {0, -1, 0, 0, 1};
	A[2] = new double[m] {0, 0, r[2], 0, -r[4]};
	A[3] = new double[m] {-1, r[1], 0, 0, r[4]};
	A[4] = new double[m] {0, 0, r[2], r[3], 0};

	// ������-������� b
	double* b{ new double[m] { i1, -i1,  e[0] + e[2] - (r[0] * i1), 0, e[2] + e[3] } };

	double* i_2 = Gaousse(A, b, m);
	cout << "�������� ���� � �����:" << endl;
	for (int k = 0; k < m; k++)
	{
		cout << "i[" << k + 1 << "] = " << i_2[k] << endl;
	}

	cout << "���: " << i_2[0] << endl;
}