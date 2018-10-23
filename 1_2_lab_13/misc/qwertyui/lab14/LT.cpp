#include "pch.h"
#include "stdafx.h"
#include <iostream>

namespace LT
{
	LexTable Create(int size)
	{
		if (size >= LT_MAXSIZE)
			throw ERROR_THROW(113);
		LexTable ltable = {size, -1, new Entry[size]};
		return ltable;
	}

	void Add(LexTable& ltable, Entry& lstr)
	{
		ltable.size++;
		if (ltable.size >= ltable.maxsize)
			throw ERROR_THROW(113);
		ltable.table[ltable.size] = lstr;
	}

	void Delete(LexTable& ltable)
	{
		if (!&ltable)
			throw ERROR_THROW(3);
		delete ltable.table;
		ltable.table = nullptr;
	}

	Entry GetEntry(LexTable& ltable, int nstr)
	{
		if (ltable.size > nstr)
			throw ERROR_THROW(5);
		return ltable.table[nstr];
	}
}