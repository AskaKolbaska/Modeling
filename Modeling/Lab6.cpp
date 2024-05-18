#include "Lab6.h"

void Lab6()
{
	int p = 0;
	int q = 0;

	cout << "������������ ������ �6" << endl << "������ ����������������� ������������" << endl << "������� �.�." << endl << endl;
	cout << "������� p: ";
	cin >> p;
	cout << "������� q: ";
	cin >> q;

	// ����� ������ ������� �� 4 ���� ������
	int** a = new int* [5]; // 5 ����� ��������
	for (int i = 0; i < 5; i++)
	{
		a[i] = new int[4]; // 4 ���� ������
	}
	// ���������� ������� � �������
	{
		a[0][0] = 12;
		a[0][1] = 18;
		a[0][2] = 16;
		a[0][3] = 24;

		a[1][0] = 10;
		a[1][1] = 4;
		a[1][2] = 8;
		a[1][3] = 7;

		a[2][0] = 64;
		a[2][1] = 56;
		a[2][2] = 60;
		a[2][3] = 80;

		a[3][0] = 30;
		a[3][1] = 0;
		a[3][2] = 18;
		a[3][3] = 24;

		a[4][0] = 21;
		a[4][1] = 15;
		a[4][2] = 8;
		a[4][3] = 30;
	}

	// ������ �������� ������� (���)
	int* b = new int[6] {
		72000 * (1 + 2 * p + q),
			56000 * (1 + 2 * p + q),
			111760 * (1 + 2 * p + q),
			36000 * (1 + 2 * p + q),
			42000 * (1 + 2 * p + q),
			0 // ��� ����� �������� ������� Z
		};

	// ������� � 1 �� ������� ���� ������
	double* c = new double[4] {
		12 * (10 + (double)p + 0.5 * (double)q),
			8 * (10 + (double)p + 0.4* (double)q),
			10 * (10 + (double)p + 0.3*(double)q),
			13 * (10 + (double)p + 0.2*(double)q)
		};

	// ����� �������� �� ����������
	int* d = new int[4] {
		1000 * (1 + 2 * p + q),
			200 * (1 + 2 * p + q),
			20 * (1 + 2 * p + q),
			10 * (1 + 2 * p + q)
		};

	// ������������ ��������� z
	double* z = new double[4];
	for (int i = 0; i < 4; i++)
	{
		z[i] = -1 * a[0][i];
	}

	// y
	double* y = new double[5];
	for (int i = 0; i < 5; i++)
	{
		y[i] = 0;
	}

	// ������� ���������
	double* x = new double[5];
	for (int i = 0; i < 5; i++)
	{
		x[i] = 0;
	}

	// ����� �������� ������ //
	{
		cout << "\n�������� ������:" << endl << endl;
		cout << "���������: ";
		for (int i = 0; i < 4; i++)
		{
			cout << a[0][i] << "\t";
		}
		cout << endl;
		cout << "��������� ��������: ";
		for (int i = 0; i < 4; i++)
		{
			cout << a[1][i] << "\t";
		}
		cout << endl;
		cout << "����������� ��������� � ������: ";
		for (int i = 0; i < 4; i++)
		{
			cout << a[2][i] << "\t";
		}
		cout << endl;
		cout << "��������������: ";
		for (int i = 0; i < 4; i++)
		{
			cout << a[3][i] << "\t";
		}
		cout << endl;
		cout << "��������� � ��������: ";
		for (int i = 0; i < 4; i++)
		{
			cout << a[4][i] << "\t";
		}
		cout << endl;

		cout << "����� ������ �������� �������: ";
		for (int i = 0; i < 5; i++)
		{
			cout << b[i] << "\t";
		}
		cout << endl;
		cout << "������� �� ������ 1 �� ������: ";
		for (int i = 0; i < 4; i++)
		{
			cout << c[i] << "\t";
		}
		cout << endl;
		cout << "����� �������� �� ����������� ����� ����������: ";
		for (int i = 0; i < 4; i++)
		{
			cout << b[i] << "\t";
		}
		cout << endl;
	}

	// �������� ����� //
	// ���������� � ������������ ���������
	for (int i = 0; i < 5; i++)
	{
		// ���� b_i �������������, �� ��� ��������� �������� �� -1
		if (b[i] < 0) {
			for (int j = 0; j < 4; j++)
			{
				a[i][j] *= -1;
			}
		}
	}
	// ������� �������
	double** matrix = new double* [6];
	for (int i = 0; i < 6; i++)
	{
		matrix[i] = new double[10];
		for (int j = 0; j < 10; j++)
		{
			matrix[i][j] = 0;
		}
	}

	// ���������� ������� ������� (�)
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matrix[i][j] = a[i][j];
		}
	}

	// (y)
	matrix[0][4] = 1;
	matrix[1][5] = 1;
	matrix[2][6] = 1;
	matrix[3][7] = 1;
	matrix[4][8] = 1;

	// (b)
	for (int j = 0; j < 5; j++)
	{
		matrix[j][9] = b[j];
	}
	// (z)
	for (int i = 0; i < 4; i++)
	{
		matrix[5][i] = z[i];
	}

	cout << endl << "����������� �������:" << endl << endl;
	show_matrix(matrix, y);

	bool is_minus = true; // ���� ������ ������������� � z
	int number = 0; // ������� �����
	do
	{
		is_minus = false;
		number++;
		double min = 0; // ���������� ��� ������������ ����� z
		double max = 0; // ���������� ��� ������������� ����� b_i / a_i_j
		int ind_i = 0; // ����� ������
		int ind_j = 0; // ����� �������

		double* b_a = new double[5]; // ������ �� ���������� b_i / a_i_j

		// ������� ����� ����������� ����� z
		for (int j = 0; j < 10; j++)
		{
			if (matrix[5][j] < min)
			{
				min = matrix[5][j];
				ind_j = j;
			}
		}

		// ����� b_i / a_i_j
		for (int i = 0; i < 5; i++)
		{
			b_a[i] = static_cast<double>(b[i]) / matrix[i][ind_j];

			// ����� ������������� ����� b_i / a_i_j
			if (b_a[i] > max)
			{
				max = b_a[i];
				ind_i = i;
			}
		}

		/*cout << endl << endl;
		cout << "b_i / a_i_j" << endl;
		for (int i = 0; i < 5; i++)
		{
			cout << b_a[i] << "\t";
		}
		cout << endl << endl;*/

		// ������ ������������ a � ������ �������
		y[ind_i] = matrix[ind_i][ind_j];
		if (ind_j<5)
		{
			x[ind_j] = 1;
		}

		//show_matrix(matrix, y);

		// "�����������" �������� ������������ � 1
		double a = matrix[ind_i][ind_j];
		for (int j = 0; j < 10; j++)
		{
			double _m = matrix[ind_i][j];
			matrix[ind_i][j] = _m / a;
		}

		/*cout << endl;
		show_matrix(matrix, y);

		cout << endl;*/

		// "���������" ������ ������������� � ������� �������
		for (int i = 0; i < 6; i++)
		{
			// ���� ��� �� ������� ������
			if (i != ind_i) {
				for (int j = 0; j < 10; j++)
				{
					matrix[i][j] = matrix[ind_i][j] * matrix[i][ind_j] - matrix[i][j];
				}
			}
		}

		/*cout << endl;
		show_matrix(matrix, y);
		cout << endl;*/

		for (int j = 0; j < 10; j++)
		{
			bool flag = true;

			// ���� ������� �������������
			if (matrix[5][j]< 0) {
				flag = true;
				is_minus = flag;
				break;
			}
		}

		cout << number << " ���:" << endl << endl;
		show_matrix(matrix, y);

		// ������������ ������
		delete[] b_a;
	} while (is_minus);

	cout << endl << endl;
	for (int i = 0; i < 4; i++)
	{
		//cout << x[i] << endl;
		x[i] = x[i] * matrix[i][9];
	}

	// ����� ����������� //
	{
		//cout << "����� ������� ��������� ��������: " << matrix[5][9] << endl;
		for (int i = 0; i < 4; i++)
		{
			cout << "x_" << i << ": " << x[i] << endl;
		}
		double res = 0;
		for (int i = 0; i < 4; i++)
		{
			res += c[i] * x[i];
		}
		cout << "������������ ����� �������: " << res << endl;
	}
}

void show_matrix(double** matrix, double* y) {
	cout << setw(10) << " " << setw(10) << "x_1" << setw(10) << "x_2" << setw(10) << "x_3" << setw(10) << "x_4" << setw(10)
		<< setw(10) << "y_1" << setw(10) << "y_2" << setw(10) << "y_3" << setw(10) << "y_4" << setw(10) << "y_5" << setw(10) << "b_i" << endl;
	for (int i = 0; i < 6; i++)
	{
		if (i<5)
		{
			cout << setw(10) << y[i];
		}
		else {
			cout << setw(10) << " ";
		}

		for (int j = 0; j < 10; j++)
		{
			cout << setw(10) << matrix[i][j];
		}
		cout << endl;
	}
}