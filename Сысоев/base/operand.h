#pragma once
#include <string>

class operand
{
public:
	operand(std::string str) :name(str) {};
	operand(const operand& copy) :name(copy.name){}

	virtual bool getType() = 0;

	std::string getName() { return name; }
	void setName(std::string str) { name = str; }

	~operand() {};
private:
	std::string name;
};

