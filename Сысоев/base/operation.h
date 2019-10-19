#pragma once
#include "operand.h"

/*
Класс операция. Унаследован от класса операнд.
Абстрактное представление арифметической операции
*/

class operation :
	public operand
{
public:
	// Конструкторы ----------------------------------------------------------------------------------------
	operation( std::string name, int priority_, double(*funk_)(double, double), int koll_of_operands_ = 2)
		:priority(priority_), operand(name),funk(funk_),
		koll_of_operands(koll_of_operands_) {}  // Конструктор инициализатор
	operation(const operation& copy):priority(copy.priority), operand(copy){}  // Конструктор копирования

	// Методы ----------------------------------------------------------------------------------------------
	bool getType() { return true; }  // Получение типа потомка
	int get_koll_of_operands() { return koll_of_operands; }  // Получение арности операции
	int getPriority() { return priority; }  // Получение приоритета операции
	void setPriority(int priority_) { priority = priority_; }  // Установка приоритета операции

	// Перегруза операторов --------------------------------------------------------------------------------
	double operator()(double a, double b) {  // Перегрузка оператора ()
		return funk(a, b);
	}

	// Деструктор ------------------------------------------------------------------------------------------
	~operation() {};
private:
	// Поля ------------------------------------------------------------------------------------------------
	int priority;  // Приоритет операции
	double (*funk)(double, double);  // Функция, которую операция исполняет
	int koll_of_operands;  // Арность операции
};