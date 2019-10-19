#pragma once
#include "operand.h"

/*
����� ��������. ����������� �� ������ �������.
����������� ������������� �������������� ��������
*/

class operation :
	public operand
{
public:
	// ������������ ----------------------------------------------------------------------------------------
	operation( std::string name, int priority_, double(*funk_)(double, double), int koll_of_operands_ = 2)
		:priority(priority_), operand(name),funk(funk_),
		koll_of_operands(koll_of_operands_) {}  // ����������� �������������
	operation(const operation& copy):priority(copy.priority), operand(copy){}  // ����������� �����������

	// ������ ----------------------------------------------------------------------------------------------
	bool getType() { return true; }  // ��������� ���� �������
	int get_koll_of_operands() { return koll_of_operands; }  // ��������� ������� ��������
	int getPriority() { return priority; }  // ��������� ���������� ��������
	void setPriority(int priority_) { priority = priority_; }  // ��������� ���������� ��������

	// ��������� ���������� --------------------------------------------------------------------------------
	double operator()(double a, double b) {  // ���������� ��������� ()
		return funk(a, b);
	}

	// ���������� ------------------------------------------------------------------------------------------
	~operation() {};
private:
	// ���� ------------------------------------------------------------------------------------------------
	int priority;  // ��������� ��������
	double (*funk)(double, double);  // �������, ������� �������� ���������
	int koll_of_operands;  // ������� ��������
};