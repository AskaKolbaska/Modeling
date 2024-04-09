#include "Lab2.h"
#include "Lab3.h"
#include "Includes.h"

void Lab3()
{
	cout << "������������ ������ �3" << endl << "������ ��������� �����" << endl << "������� �.�." << endl << endl;

	// ���. ������
	int p = 0;
	int q = 0;

	cout << "������� p: ";
	cin >> p;
	cout << "������� q: ";
	cin >> q;

	double* t = new double[6]; // ��������� ������
	double* y = new double[5]; // ������ ������� ���������
	double* linear = new double[2]; // ������ ������������� ��������� ������
	double* kvadra = new double[3]; // ������������ ������������� ������

	// ���������
	double* trL = new double[6]; // ������ �������� ��������� ������
	double* erL = new double[5]; // ������ �������� ������������
	double trKv[6]; // ������ �������� ������������� ������
	double erKv[5]; // ������ �������� ������������
	double maxEr = 0; // ������������ �����������
	double maxEr_kv = 0; // ������������ �����������

	// ����������
	
	// ����������� ���. ������
	for (int i = 0; i < 5; i++)
	{
		t[i] = i + 1;
		y[i] = 10 + 0.05 * (p + 2 * q + 1) * t[i] + 0.01 * (p + q + 1) * pow(t[i], 2) + 0.02 * (2 * p + q + 1) * pow(-1, t[i]);
	}
	t[5] = 6;

	// ��������� ��������� ������
	linear = MNK(t, y, 1, 5);

	// ����� �������������� ������
	cout << endl << "������������ ��������� ������" << endl;
	for (int k = 0; k  < 2; k ++)
	{
		cout << linear[k] << endl;
	}

	// ��������� �������� ��������� ������ � �������������� ��������� �������������
	for (int k = 0; k < 6; k++)
	{
		trL[k] = linear[0] + linear[1] * t[k];
	}

	// ����������� ��������� ������
	for (int i = 0; i < 5; i++)
	{
		double x = abs(trL[i] - y[i]) / y[i];
		erL[i] = round(x * 10000) / 10000;
	}

	// ������������ �����������
	for (int i = 0; i < 5; i++)
	{
		if (maxEr < erL[i]) {
			maxEr = erL[i];
		}
	}

	kvadra = MNK(t, y, 2, 5);
	// ����� �������������� ������
	cout << endl << "������������ ������������� ������" << endl;
	for (int k = 0; k < 2; k++)
	{
		cout << kvadra[k] << endl;
	}

	// �������� ������������� ������
	for (int k = 0; k < 6; k++)
	{
		trKv[k] = kvadra[0] + kvadra[1] * t[k] + kvadra[2] * pow(t[k], 2);
	}

	// ����������� ������������� ������
	for (int i = 0; i < 5; i++)
	{
		double x = abs(trKv[i] - y[i]) / y[i];
		erKv[i] = round(x * 10000) / 10000;
	}

	// ������������ �����������
	for (int i = 0; i < 5; i++)
	{
		if (maxEr_kv < erKv[i]) {
			maxEr_kv = erKv[i];
		}
	}

	cout << "����������" << endl << endl;
	cout << setw(50) << left << "������:";
	for (int i = 0; i < 6; i++)
	{
		cout << setw(10) << t[i];
	}
	cout << endl;
	cout << setw(50) << left << "����� ������� (y[k]), ���. ��.:";
	for (int i = 0; i < 5; i++)
	{
		cout << setw(10) << y[i];
	}
	cout << endl;

	cout << setw(50) << left << "�������� �����:";
	for (int i = 0; i < 6; i++)
	{
		cout << setw(10) << trL[i];
	}
	cout << endl;

	cout << setw(50) << left << "������������ �����:";
	for (int i = 0; i < 6; i++)
	{
		cout << setw(10) << trKv[i];
	}
	cout << endl;

	cout << setw(50) << left << "����������� ��������� ������ � ������:";
	for (int i = 0; i < 5; i++)
	{
		cout << setw(10) << erL[i];
	}
	cout << endl;

	cout << setw(50) << left << "����������� ������������� ������ � ������:";
	for (int i = 0; i < 5; i++)
	{
		cout << setw(10) << erKv[i];
	}
	cout << endl;

	cout << setw(50) << left << "����������� ��������� ������:" << setw(10) << maxEr<<endl;
	cout << setw(50) << left << "����������� ������������� ������:" << setw(10) << maxEr_kv << endl;
}

// ������������ ��������
double* MNK(double* t, double* y, int m, int y_n) {
	// ���������� ������������� � �������� �� ������� ������, ��� ������������ �������
	int n = m + 1;

	// �������� ������ ��� ���� (������)
	double** A{ new double* [n] {} };
	for (int i = 0; i < n; i++)
	{
		A[i] = new double[n];
	}
	double* b = new double[n];

	// ��������� ����
	for (int i = 0; i < n; i++)
	{
		double s;
		for (int j = 0; j < n; j++)
		{
			// ������� A[i][j]
			s = 0;
			for (int k = 0; k < y_n; k++)
			{
				s += pow(t[k], i + j);
			}
			A[i][j] = s;
		}

		// ������� b[i]
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