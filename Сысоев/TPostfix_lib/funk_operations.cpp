#include "funk_operations.h"
#include <math.h>

// Реализация функций операций

double sum(double a, double b) {
	return a + b;
}

double sub(double a, double b) {
	return a - b;
}

double mul(double a, double b) {
	return a * b;
}

double div(double a, double b) {
	return a / b;
}

double sum_un(double a, double b)
{
	return ++a;
}

double sub_un(double a, double b)
{
	return --a;
}

double sin(double a, double b)
{
	return sin(a);
}

double cos(double a, double b)
{
	return cos(a);
}

double tg(double a, double b)
{
	return tan(a);
}

double ctg(double a, double b)
{
	return 1/tan(a);
}

double ln(double a, double b)
{
	return log(a);
}

