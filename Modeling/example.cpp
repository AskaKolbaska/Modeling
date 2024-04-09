#include "example.h"
#include "Includes.h"

void example()
{
	double modul = abs(10.146 - 10.16);
	double res = (modul / 10.16) * 100;
	cout << modul << endl << 10.16 << endl << res;
}
