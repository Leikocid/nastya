#pragma once
#include "stdafx.h"
#define STD_SUBSTR "substr"
#define STD_STRLEN "strlen"
#define STD_BIBLE_SIZE 2
const char* const StdBible[STD_BIBLE_SIZE] = {STD_SUBSTR, STD_STRLEN};

namespace LA
{
	bool newLex(FST::FST&, char*, char);
	void LexAnalizator(char inText[], Log::LOG);
	bool isLetter(char);
	void addLex(char);
	void addId(char*, IT::IDDATATYPE, IT::IDTYPE);
	bool isThatLexem(char*);
}