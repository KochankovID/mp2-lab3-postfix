﻿#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"

using namespace std;

class TPostfix
{
public:
	// Конструкторы ----------------------------------------------------------------------------------------
	TPostfix(const string& s) : infix(s), postfix("") {}  // Конструктор инициализатор (привидение типа)
	TPostfix(const TPostfix& copy) : infix(copy.infix), postfix(copy.postfix) {}  // Конструктор копирования

	// Методы ----------------------------------------------------------------------------------------------
	string& GetInfix() { return infix; }  // Доступ к инфексной форме записи
	string GetPostfix() { return postfix; }  // Доступ к постфиксной форме записи
	void ToPostfix();  // Перевод инфексной строки в постфиксную запись
	double Calculate(); // Ввод переменных, вычисление по постфиксной форме
	string getTableBrackets();  // Получение таблицы соответствия скобок

	// Деструктор ------------------------------------------------------------------------------------------
	~TPostfix() {}
private:
	// Поля ------------------------------------------------------------------------------------------------
	string infix;  // Строка, хранящая выражение в инфексной форме
	string postfix;  // Строка, хранящая выражение в постфиксной форме

	// Скрытые методы --------------------------------------------------------------------------------------
	void isCorrect();  // Проверка выражения на корректность

};

#endif
