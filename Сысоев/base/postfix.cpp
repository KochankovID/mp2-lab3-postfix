#include "postfix.h"
#include <stdexcept>
#include <iostream>
#include "funk_operations.h"


void TPostfix::ToPostfix()
{
	auto expression = split();  // Разбиение строки на операнды
	isCorrectBrakets(&expression);  // Проверка выражения на корректность скобок

	TStack<operation*> operations; // Стек операций

	for (operand* t : expression) {
		if (t->getType()) {  // Обработка операций
			operation* oper = static_cast<operation*>(t);  // Понижающее привидение типа
			if ((operations.isEmpty()) ||  // Если стек операций пуст
				(oper->getPriority() == 0) ||  // Если приоритет операции = 0 '('
				((operations.top()->getPriority() < oper->getPriority()) && // Если приоритет новой операции строго больше
				(operations.top()->getName() != "("))) // И предыдущая операция не открывающая стобка
			{
				operations.push(oper);  // Добавляем операция в стек операций
			}
			else {
				if (oper->getName() == ")") {  // Особая обработка закрывающей скобки
					while (operations.top()->getName() != "(")  
					{
						exp.push_back(operations.top()); // Достаем из стека все операции до первой '('
						postfix += operations.pop()->getName();  // Имена операций записываем в постфикс
					}
					operations.pop();  // Удаляем из стека '('
				}
				else {  // Если приоиртет меньше либо равен
					while ((!operations.isEmpty()) &&   // Выполняем пока стек не пуст
						(operations.top()->getPriority() >= oper->getPriority())) // И пока приоритет больше или равен
					{
						exp.push_back(operations.top());  // Записываем в вектор операндов
						postfix += operations.pop()->getName();  // Записываем в постфисную строку
					}
					operations.push(oper);  // Добавляем в стек текущую операцию
				}
			}
		}
		else {  // Обработка переменных
			if ((exp.size() > 0) &&  // Если вектор не пуст
				(!exp[exp.size() - 1]->getType()))  // И предыдущий операнд - перемнная
			{
				postfix += " ";  // Добавим пробел в постфиксную строку
			}
			exp.push_back(t);  // Добавим переменную в вектор операндов
			postfix += t->getName();  // Записываем имя переменной в постфисную строку
		}
	}

	while (!operations.isEmpty())  // Если в стеке остались операции извлекаем их
	{
		exp.push_back(operations.top());
		postfix += operations.pop()->getName();
	}
}

string TPostfix::GetPostfix()
{
	if (postfix == "")  // Если вызываем первый раз
	{ 
		ToPostfix();
	}
	return postfix;
}

double TPostfix::Calculate()
{
	if (postfix == "")  // Если вызываем первый раз
	{
		ToPostfix();
	}

	TStack<double> vars;  // Стек переменных

	double val;  // Результат выражения


	for (operand* t : exp)  // Считывание значений переменных
	{
		if (!t->getType()) {
			try {
				static_cast<variable*>(t)->setValue(std::stod(t->getName()));
			}
			catch (...) {
				cout << "Input value of variable " + t->getName() + ":";
				cin >> val;
				static_cast<variable*>(t)->setValue(val);
			}
		}
	}


	for (operand* t : exp)  // Вычисление результата
	{
		if (t->getType()) {
			operation* oper = static_cast<operation*>(t);
			switch (oper->get_koll_of_operands())
			{
			case 1:  // Унарные операции
				vars.push((*oper)(vars.pop(), 0));
				break;
			case 2:  // Бинарные операции
				if (vars.size() == 1) {
					throw std::runtime_error("Not enough operands!");
				}
				vars.push((*oper)(vars.pop(), vars.pop()));
				break;
			}
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
				str += "Открывающая " + std::to_string(stack.pop()) + " Закрывающая " + std::to_string(koll) + '\n';
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
	arr.push_back(new operation("++", 4, sum_un, 1));
	arr.push_back(new operation("--", 4, sub_un, 1));
	arr.push_back(new operation("sin", 4, sin, 1));
	arr.push_back(new operation("cos", 4, cos, 1));
	arr.push_back(new operation("tg", 4, tg, 1));
	arr.push_back(new operation("ctg", 4, ctg, 1));
	arr.push_back(new operation("ln", 4, ln, 1));
}

void TPostfix::isCorrectBrakets(const vector<operand*>* v) // Проверка выражения на корректность
{
	TStack<char> stack;
	for (operand* t : *v) {
		if (t->getType()) {
			switch (t->getName().c_str()[0])
			{
			case '(':
				stack.push(0);
				break;
			case ')':
				if (stack.isEmpty()) {
					throw std::runtime_error("Выражение заданно неверно! Скобки не открыты!");
				}
				stack.pop();
				break;
			default:
				continue;
			}
		}
	}
	if (!stack.isEmpty()) {
		throw std::runtime_error("Выражение заданно неверно! Скобки не закрыты!");
	}
}

vector<operand*> TPostfix::split()
{
	vector<operand*> expr_splitted;  // Вектор выражения в виде операндов в инфексной форме

	string current_variable = "";  // Строка имени переменной
	string current_operation;  // Строка имени операции
	bool flag;  // Флаг была ли найдена операция
	for (int i = 0; i < infix.length(); i++) {
		flag = true;

		if (infix.length() - i >= 3) {  // Т.к. в данной системе операция может иметь имя мксимальной длинной 3 символа
			current_operation.insert(current_operation.begin(), infix.begin() + i, infix.begin() + i + 3);
		}
		else {
			if (infix.length() - i >= 2) {
				current_operation.insert(current_operation.begin(), infix.begin() + i, infix.begin() + i + 2);
			}
			else {
				current_operation.insert(current_operation.begin(), infix.begin() + i, infix.begin() + i + 1);
			}
		}
		while (current_operation.length() >= 1)
		{
			for (operation* t : arr) {  // Проверяем совпадает ли текущее имя операции с каким-либо именем операции
				if (t->getName() == current_operation) {
					if (current_variable != "") {
						expr_splitted.push_back(new variable(current_variable));
						current_variable = "";
					}
					expr_splitted.push_back(t);
					i += current_operation.length() - 1;
					current_operation = "";
					flag = false;
					break;
				}
			}
			if (flag) {  // Если не совпадает уменьшаем кол-во символов
				current_operation.erase(current_operation.length() - 1, 1);
			}
		}
		if (flag) {  // Если операция не найдена текцщий символ добавляется к имени переменной
			current_variable += infix[i];
		}

	}
	if (current_variable != "") {  // Если имя переменной не пусто, добавляем переменную
		expr_splitted.push_back(new variable(current_variable));
	}
	return expr_splitted;
}
