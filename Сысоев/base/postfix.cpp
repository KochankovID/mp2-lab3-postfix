#include "postfix.h"
#include <stdexcept>
#include <iostream>

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

void TPostfix::ToPostfix()
{
	isCorrect();
	auto expression = split();

	TStack<operation*> operations;

	for (operand* t : expression) {
		if (t->getType()) {
			operation* oper = static_cast<operation*>(t);
			if ((operations.isEmpty()) || (oper->getPriority() == 0) || (operations.top()->getPriority() < oper->getPriority())){
				operations.push(oper);
			}
			else {
				if (oper->getName() == ")") {
					while (operations.top()->getName() != "(")
					{
						exp.push_back(operations.top());
						postfix += operations.pop()->getName();
					}
					operations.pop();
				}
				else {
					while ((!operations.isEmpty()) && (operations.top()->getPriority() >= oper->getPriority()))
					{
						exp.push_back(operations.top());
						postfix += operations.pop()->getName();
					}
					operations.push(oper);
				}
			}
		}
		else {
			if ((exp.size()>0)&&(!exp[exp.size() - 1]->getType())) {
				postfix += " ";
			}
			exp.push_back(t);
			postfix += t->getName();
		}
	}
	while (!operations.isEmpty())
	{
		exp.push_back(operations.top());
		postfix += operations.pop()->getName();
	}
}

string TPostfix::GetPostfix()
{
	if (postfix == "") {
		ToPostfix();
	}
	return postfix;
}

double TPostfix::Calculate()
{
	TStack<double> vars;

	if (postfix == "") {
		ToPostfix();
	}

	double val;
	for (operand* t : exp) {
		if (!t->getType()) {
			try {
				static_cast<variable*>(t)->setValue(std::stod(t->getName()));
			}
			catch(...){
				cout << "Input value of variable " + t->getName() + ":";
				cin >> val;
				static_cast<variable*>(t)->setValue(val);
			}
		}
	}

	for (operand* t : exp) {
		if (t->getType()) {
			if (vars.size() == 1) {
				throw std::runtime_error("Not enough operands!");
			}
			vars.push((*static_cast<operation*>(t))(vars.pop(), vars.pop()));
		}
		else {
			vars.push(static_cast<variable*>(t)->getValue());
		}
	}
	return vars.pop();
}

string TPostfix::getTableBrackets()
{
	TStack<int> stack;
	string str = "";
	int koll = 0;
	for (int i = 0; i < infix.length(); i++) {
		switch (infix[i])
		{
		case '(':
			stack.push(koll);
			koll++;
			break;
		case ')':
			if (stack.isEmpty()) {
				str += "Открывающая - Закрывающая " + std::to_string(koll) + '\n';
			}
			else {
				str += "Открывающая " + std::to_string(stack.pop()) +" Закрывающая " + std::to_string(koll) + '\n';
			}
			koll++;
			break;
		default:
			continue;
		}
	}
	while (!stack.isEmpty())
	{
		str += "Открывающая " + std::to_string(stack.pop()) + " Закрывающая " + "- \n";
	}
	return str;
}

void TPostfix::initialise_operations()
{
	arr.push_back(new operation("(", 0, nullptr));
	arr.push_back(new operation(")", 1, nullptr));
	arr.push_back(new operation("+", 2, sum));
	arr.push_back(new operation("-", 2, sub));
	arr.push_back(new operation("*", 3, mul));
	arr.push_back(new operation("/", 3, div));
}

void TPostfix::isCorrect()
{
	TStack<int> stack;
	for (int i = 0; i < infix.length(); i++) {
		switch (infix[i])
		{
		case '(':
			stack.push(i);
			break;
		case ')':
			if (stack.isEmpty()) {
				throw std::runtime_error("Выражение заданно неверно! Закрывающая скобка идет до открывающей в " + std::to_string(i) + " позиции.");
			}
			stack.pop();
			break;
		default:
			continue;
		}
	}
	if (!stack.isEmpty()) {
		throw std::runtime_error("Выражение заданно неверно! Скобки не закрыты!");
	}
}

vector<operand*> TPostfix::split()
{
	vector<operand*> expr_splitted;

	string str = "";
	string current_elem;
	bool flag;
	for (int i = 0; i < infix.length(); i++) {
		current_elem = infix[i];
		flag = true;

		for (operation* t : arr) {
			if (t->getName() == current_elem) {
				if (str != "") {
					expr_splitted.push_back(new variable(str));
					str = "";
				}
				expr_splitted.push_back(t);
				flag = false;
			}
		}
		if (flag) {
			str += current_elem;
		}
	
	}
	if (str != "") {
		expr_splitted.push_back(new variable(str));
	}
	return expr_splitted;
}
