﻿#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"
#include "operation.h"
#include "variable.h"
#include <vector>
#include <algorithm>

using namespace std;

class TPostfix
{
public:
	// Конструкторы ----------------------------------------------------------------------------------------
	TPostfix(const string& s) : infix(s), postfix("") // Конструктор инициализатор (привидение типа)
	{ 
		initialise_operations(); 
		infix.erase(remove(infix.begin(), infix.end(), ' '), infix.end());
	}  
	TPostfix(const TPostfix& copy) :  // Конструктор копирования
		infix(copy.infix), postfix(copy.postfix), arr(copy.arr) {}

	// Методы ----------------------------------------------------------------------------------------------
	string GetInfix() { return infix; }  // Доступ к инфексной форме записи
	string GetPostfix();  // Доступ к постфиксной форме записи
	double Calculate();  // Ввод переменных, вычисление по постфиксной форме
	string getTableBrackets();  // Получение таблицы соответствия скобок

	// Деструктор ------------------------------------------------------------------------------------------
	~TPostfix() {
		for (operand* t : exp) {
			if (!t->getType()) {  // Удаляем только переменные
				delete t;
			}
		}
		for (operand* t: arr) {  // Удаляем все операции
			delete t;
		}
	}
private:
	// Поля ------------------------------------------------------------------------------------------------
	string infix;  // Строка, хранящая выражение в инфексной форме
	string postfix;  // Строка, хранящая выражение в постфиксной форме
	vector<operation*> arr; // Набор всех поддерживаемых операций
	vector<operand*> exp;  // Выражение в виде операндов и операций в постфиксном виде

	// Скрытые методы --------------------------------------------------------------------------------------
	void initialise_operations(); // Инициализация массива всех поддерживаемых операций
	void isCorrectBrakets(const vector<operand*>* v);  // Проверка скобок на корректность
	vector<operand*> split(); // Разбор строки на операнды и операции
	void ToPostfix();  // Перевод инфексной строки в постфиксную запись

};

#endif
