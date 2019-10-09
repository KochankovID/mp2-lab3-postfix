#include "postfix.h"
#include <stdexcept>

void TPostfix::ToPostfix()
{
}

double TPostfix::Calculate()
{
	return 0.0;
}

string TPostfix::getTableBrackets()
{
	return string();
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
		if (!stack.isEmpty()) {
			throw std::runtime_error("Выражение заданно неверно! Скобк" + (stack.top > 0? "и":"а") + " не закрыт" + (stack.top > 0 ? "ы!" : "а!"));
		}
	}
}
