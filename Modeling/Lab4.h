#pragma once
#include "Includes.h"

void Lab4();

double f(double, int, int);

double Mass_preparation_cyl(function<double(double, int, int)> f, double, int, int);
double Mass_preparation_konus(function<double(double, int, int)> f, double, int, int);
double V_rectangle(function<double(double, int, int)> f, double, int, int, int);
double V_trapezoid(function<double(double, int, int)> f, double, int, int, int);
double V_correct(double, int, int);
double Error_rate(int, int, double, double);