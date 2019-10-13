#pragma once
#include "operand.h"
class operation :
	public operand
{
public:
	operation( std::string str, int priority_, double(*funk_)(double, double)) :priority(priority_), operand(str),funk(funk_) {}
	operation(const operation& copy):priority(copy.priority), operand(copy){}

	bool getType() { return true; }

	double operator()(double a, double b) {
		return funk(a, b);
	}

	int getPriority() { return priority; }
	void setPriority(int priority_) { priority = priority_; }

	~operation() {};
private:
	int priority;
	double (*funk)(double, double);
};

