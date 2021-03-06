#include "pch.h"
#include <iostream>
#include <locale>

#define EXP1 28
#define EXP2 50
#define EXP3 66
#pragma warning(disable: 4996)
using namespace std;

bool PolishNotation(int/*, LT::LexTable&, IT::IdTable&*/);				//Построение польской записи в таблице лексем(позиция выражения в lextable, табл лексем, табл ид)
//true - построение польской записи выполнено успешно
//false - построение польской записи не выполнено

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	//LT::LexTable ltable;
	//IT::IdTable itable;
	cout << 28 << ": польская запись построена" << endl;
	if (PolishNotation(EXP1/*, ltable, itable*/))
		cout << EXP1 << ": польская запись построена" << endl;
	else
		cout << EXP1 << ": польская запись не построена" << endl;
	if (PolishNotation(EXP2/*, ltable, itable*/))
		cout << EXP2 << ": польская запись построена" << endl;
	else
		cout << EXP2 << ": польская запись не построена" << endl;
	if (PolishNotation(EXP3/*, ltable, itable*/))
		cout << EXP3 << ": польская запись построена" << endl;
	else
		cout << EXP3 << ": польская запись не построена" << endl;
	return 0;
}