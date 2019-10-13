#pragma once
#include "operand.h"
class variable :
	public operand
{
public:
	variable(std::string str, double val = 0) :operand(str), value(val) {}

	bool getType() { return false; }

	double getValue() { return value; }
	void setValue(double val) { value = val; }

private:
	double value;
};

