#include "example.h"
#include "Includes.h"
#define g 9.8
#define m 200
#define k1 0.2
#define k2 0.04
#define H 2000
#define tau 0.2

void example()
{
	vector<double> v;
	vector<double> x;
	vector<double> h;
	My_func(&v, &x, &h);
	for (int i = 0; i < v.size(); i++)
	{
		cout <<i<<"\t" << v[i] <<"\t"<<x[i]<<"\t"<<h[i] << endl;
	}
}

void My_func(vector<double>* v, vector<double>* x, vector<double>* h) {
	v->push_back(0);
	x->push_back(0);
	h->push_back(H);

	do
	{
		double v_ex = v->back() + 0.2 * (g - (1 / m) * (k1 * v->back() + k2 * pow(v->back(), 2)));
		double x_ex = x->back() + tau * v->back();
		v->push_back(v_ex);
		x->push_back(x_ex);

		h->push_back(h->back() - x->back());
	} while (h->back() >0);
}