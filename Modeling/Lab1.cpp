#include "Lab1.h"

void Lab1() {
	RusConsole();
	int p = 1, q = 1; // ���. ������ 

	cout << "������������ ������ �1" << endl << "������������� ������� �� ������" << endl << "������� �.�." << endl << endl;

	cout << "������� p: ";
	cin >> p;
	cout << "������� q: ";
	cin >> q;

	Zad1(p, q);
	Zad2(p, q);
}

// ���������� ������
double CountR(int p, int q) {
	return ((double)p + (double)q + 1) / 100;
}

// ������ 1 (����� ����� ��� ���������� ������)
void Zad1(int p, int q) {
	int z0 = 100 + 4 * p + 3 * q + 1; // ��������� �����

	cout << endl << "������� 1: ����� ���-�� ���" << endl << endl;

	cout << "������ 1 (��� ���. �������)" << endl << endl;
	cout << "����� ���������� ������ � 2 ����: " << TimeFor2(z0, p, q) << endl;
	cout << "����� ���������� ������ � 5 ���: " << TimeFor5(z0, p, q) << endl;
	cout << endl << "������ 2 (� ���. ��������)" << endl << endl;
	cout << "����� ���������� ������ � 2 ����: " << TimeFor2_Add(z0, p, q) << endl;
	cout << "����� ���������� ������ � 5 ���: " << TimeFor5_Add(z0, p, q) << endl;
}

// ������ 2 (����� ��������� �����)
void Zad2(int p, int q) {
	int t = 5; // 5 ���
	double y = 10 * (100 + 4 * p + 3 * q + 1); // �������� �����

	cout << endl << "������� 2: ����� �������������� �����" << endl << endl;

	double z0 = 10 * y * pow(CountR(p, q), 2) / (10 * CountR(p, q) * (1 + 1 / (10 * CountR(p, q))) * pow(1 + CountR(p, q), t + 1) - t * CountR(p, q) - 1);
	cout << "��������� ����� ������ ����������: " << z0 << endl;
}

// ������ ���������� ������ � 2 ���� (��� ���. ��������)
int TimeFor2(int z0, int p, int q) {
	double y = (double)z0 * 2; // ����� ���������� �����
	double t = ceil(log10(y / (double)z0) / log10(1 + CountR(p, q)));

	return t;
}

// ������ ���������� ������ � 5 ���� (��� ���. ��������)
int TimeFor5(int z0, int p, int q) {
	double y = (double)z0 * 5; // ����� ���������� �����
	double t = ceil(log10(y / (double)z0) / log10(1 + CountR(p, q)));

	return t;
}

// ������ ���������� ������ � 2 ���� (c ���. ����������)
int TimeFor2_Add(int z0, int p, int q) {
	double y = (double)z0 * 2; // ����� ���������� �����
	double y_t = 0; // ������ �� ������ ���
	int i = 0; // ������ (����)
	double r = CountR(p, q);

	do
	{
		i++;
		y_t = (z0 / r) * (1 + 1 / (10 * r)) * pow(1 + r, i + 1)
			- (z0 * i) / (10 * r) - (z0 / (10 * pow(r, 2))) * (1 + 11 * r);

	} while (y_t < y);

	return i;
}

// ������ ���������� ������ � 5 ���� (c ���. ����������)
int TimeFor5_Add(int z0, int p, int q) {
	double y = (double)z0 * 5; // ����� ���������� �����

	double y_t = 0; // ������ �� ������ ���
	int i = 0; // ������ (����)
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