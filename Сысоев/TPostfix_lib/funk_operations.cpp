#include "funk_operations.h"
#include <math.h>
#include <stdexcept>

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
	if ((b - 0)<0.0001) {
		throw std::runtime_error("Деление на ноль запрещено!");
	}
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

