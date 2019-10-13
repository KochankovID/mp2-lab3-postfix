﻿#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
  string expression;
  double res;

  setlocale(LC_ALL, "Russian");
  cout << "Введите арифметическое выражение: ";
 getline(cin, expression);
  cout << expression << endl;

  TPostfix postfix(expression);
  cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
  cout << postfix.getTableBrackets() << endl;
  cout << postfix.GetPostfix() << endl;
  cout << postfix.Calculate() << endl;

  return 0;
}
