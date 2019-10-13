#ifndef __POSTFIX_H__
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
	TPostfix(const string& s) : infix(s), postfix("") { 
		initialise_operations(); 
		infix.erase(remove(infix.begin(), infix.end(), ' '), infix.end());
	}  // Конструктор инициализатор (привидение типа)
	TPostfix(const TPostfix& copy) : infix(copy.infix), postfix(copy.postfix), arr(copy.arr) { }  // Конструктор копирования

	// Методы ----------------------------------------------------------------------------------------------
	string& GetInfix() { return infix; }  // Доступ к инфексной форме записи
	string GetPostfix();  // Доступ к постфиксной форме записи
	double Calculate();  // Ввод переменных, вычисление по постфиксной форме
	string getTableBrackets();  // Получение таблицы соответствия скобок

	// Деструктор ------------------------------------------------------------------------------------------
	~TPostfix() {
		for (operand* t: arr) {
			delete t;
		}
	}
private:
	// Поля ------------------------------------------------------------------------------------------------
	string infix;  // Строка, хранящая выражение в инфексной форме
	string postfix;  // Строка, хранящая выражение в постфиксной форме
	vector<operation*> arr; // Набор всех поддерживаемых операций

	// Скрытые методы --------------------------------------------------------------------------------------
	void initialise_operations();
	void isCorrect();  // Проверка выражения на корректность
	vector<operand*> split(const string& expr); // Разбор строки на операнды и операции
	void ToPostfix();  // Перевод инфексной строки в постфиксную запись

};

#endif
