#include "pch.h"
#include "stdafx.h"
#include <stdlib.h>
#pragma warning(disable: 4996)

/*
		;
		,
		-
		=
		+
		/
		*
		space
		\n
		)
		(
		}
		{
*/

char emptyStr[] = "";

FST::FST fstIntType(emptyStr, 8,
	FST::NODE(1, FST::RELATION('i', 1)),
	FST::NODE(1, FST::RELATION('n', 2)),
	FST::NODE(1, FST::RELATION('t', 3)),
	FST::NODE(1, FST::RELATION('e', 4)),
	FST::NODE(1, FST::RELATION('g', 5)),
	FST::NODE(1, FST::RELATION('e', 6)),
	FST::NODE(1, FST::RELATION('r', 7)),
	FST::NODE()
);

FST::FST fstStrType(emptyStr, 7,
	FST::NODE(1, FST::RELATION('s', 1)),
	FST::NODE(1, FST::RELATION('t', 2)),
	FST::NODE(1, FST::RELATION('r', 3)),
	FST::NODE(1, FST::RELATION('i', 4)),
	FST::NODE(1, FST::RELATION('n', 5)),
	FST::NODE(1, FST::RELATION('g', 6)),
	FST::NODE()
);

FST::FST fstDeclare(emptyStr, 8,
	FST::NODE(1, FST::RELATION('d', 1)),
	FST::NODE(1, FST::RELATION('e', 2)),
	FST::NODE(1, FST::RELATION('c', 3)),
	FST::NODE(1, FST::RELATION('l', 4)),
	FST::NODE(1, FST::RELATION('a', 5)),
	FST::NODE(1, FST::RELATION('r', 6)),
	FST::NODE(1, FST::RELATION('e', 7)),
	FST::NODE()
);

FST::FST fstFunction(emptyStr, 9,
	FST::NODE(1, FST::RELATION('f', 1)),
	FST::NODE(1, FST::RELATION('u', 2)),
	FST::NODE(1, FST::RELATION('n', 3)),
	FST::NODE(1, FST::RELATION('c', 4)),
	FST::NODE(1, FST::RELATION('t', 5)),
	FST::NODE(1, FST::RELATION('i', 6)),
	FST::NODE(1, FST::RELATION('o', 7)),
	FST::NODE(1, FST::RELATION('n', 8)),
	FST::NODE()
);

FST::FST fstV(emptyStr, 2,
	FST::NODE(5, FST::RELATION('-', 1), FST::RELATION('+', 1), FST::RELATION('/', 1), FST::RELATION('*', 1), FST::RELATION('=', 1)),
	FST::NODE()
);

FST::FST fstMain(emptyStr, 5,
	FST::NODE(1, FST::RELATION('m', 1)),
	FST::NODE(1, FST::RELATION('a', 2)),
	FST::NODE(1, FST::RELATION('i', 3)),
	FST::NODE(1, FST::RELATION('n', 4)),
	FST::NODE()
);

FST::FST fstPrint(emptyStr, 6,
	FST::NODE(1, FST::RELATION('p', 1)),
	FST::NODE(1, FST::RELATION('r', 2)),
	FST::NODE(1, FST::RELATION('i', 3)),
	FST::NODE(1, FST::RELATION('n', 4)),
	FST::NODE(1, FST::RELATION('t', 5)),
	FST::NODE()
);

FST::FST fstReturn(emptyStr, 7,
	FST::NODE(1, FST::RELATION('r', 1)),
	FST::NODE(1, FST::RELATION('e', 2)),
	FST::NODE(1, FST::RELATION('t', 3)),
	FST::NODE(1, FST::RELATION('u', 4)),
	FST::NODE(1, FST::RELATION('r', 5)),
	FST::NODE(1, FST::RELATION('n', 6)),
	FST::NODE()
);

FST::FST fstLeftThesis(emptyStr, 2,
	FST::NODE(1, FST::RELATION('(', 1)),
	FST::NODE()
);

FST::FST fstRightThesis(emptyStr, 2,
	FST::NODE(1, FST::RELATION(')', 1)),
	FST::NODE()
);

FST::FST fstSemiColon(emptyStr, 2,
	FST::NODE(1, FST::RELATION(';', 1)),
	FST::NODE()
);

FST::FST fstComma(emptyStr, 2,
	FST::NODE(1, FST::RELATION(',', 1)),
	FST::NODE()
);

FST::FST fstLeftBrace(emptyStr, 2,
	FST::NODE(1, FST::RELATION('{', 1)),
	FST::NODE()
);

FST::FST fstRightBrace(emptyStr, 2,
	FST::NODE(1, FST::RELATION('}', 1)),
	FST::NODE()
);

FST::FST fstIntegerLiteral(emptyStr, 2,
	FST::NODE(20, FST::RELATION('0', 1), FST::RELATION('0', 0),
		FST::RELATION('1', 1), FST::RELATION('1', 0),
		FST::RELATION('2', 1), FST::RELATION('2', 0),
		FST::RELATION('3', 1), FST::RELATION('3', 0),
		FST::RELATION('4', 1), FST::RELATION('4', 0),
		FST::RELATION('5', 1), FST::RELATION('5', 0),
		FST::RELATION('6', 1), FST::RELATION('6', 0),
		FST::RELATION('7', 1), FST::RELATION('7', 0),
		FST::RELATION('8', 1), FST::RELATION('8', 0),
		FST::RELATION('9', 1), FST::RELATION('9', 0)),
	FST::NODE()
);

FST::FST fstStringLiteral(emptyStr, 4,
	FST::NODE(1, FST::RELATION('\'', 1)),
	FST::NODE(164,
		FST::RELATION('à', 2), FST::RELATION('à', 1),
		FST::RELATION('á', 2), FST::RELATION('á', 1),
		FST::RELATION('â', 2), FST::RELATION('â', 1),
		FST::RELATION('ã', 2), FST::RELATION('ã', 1),
		FST::RELATION('ä', 2), FST::RELATION('ä', 1),
		FST::RELATION('å', 2), FST::RELATION('å', 1),
		FST::RELATION('¸', 2), FST::RELATION('¸', 1),
		FST::RELATION('æ', 2), FST::RELATION('æ', 1),
		FST::RELATION('ç', 2), FST::RELATION('ç', 1),
		FST::RELATION('è', 2), FST::RELATION('è', 1),
		FST::RELATION('é', 2), FST::RELATION('é', 1),
		FST::RELATION('ê', 2), FST::RELATION('ê', 1),
		FST::RELATION('ë', 2), FST::RELATION('ë', 1),
		FST::RELATION('ì', 2), FST::RELATION('ì', 1),
		FST::RELATION('í', 2), FST::RELATION('í', 1),
		FST::RELATION('î', 2), FST::RELATION('î', 1),
		FST::RELATION('ï', 2), FST::RELATION('ï', 1),
		FST::RELATION('ð', 2), FST::RELATION('ð', 1),
		FST::RELATION('ñ', 2), FST::RELATION('ñ', 1),
		FST::RELATION('ò', 2), FST::RELATION('ò', 1),
		FST::RELATION('ó', 2), FST::RELATION('ó', 1),
		FST::RELATION('ô', 2), FST::RELATION('ô', 1),
		FST::RELATION('õ', 2), FST::RELATION('õ', 1),
		FST::RELATION('ö', 2), FST::RELATION('ö', 1),
		FST::RELATION('÷', 2), FST::RELATION('÷', 1),
		FST::RELATION('ø', 2), FST::RELATION('ø', 1),
		FST::RELATION('ù', 2), FST::RELATION('ù', 1),
		FST::RELATION('û', 2), FST::RELATION('û', 1),
		FST::RELATION('ü', 2), FST::RELATION('ü', 1),
		FST::RELATION('ú', 2), FST::RELATION('ú', 1),
		FST::RELATION('ý', 2), FST::RELATION('ý', 1),
		FST::RELATION('þ', 2), FST::RELATION('þ', 1),
		FST::RELATION('ÿ', 2), FST::RELATION('ÿ', 1),
		FST::RELATION('\t', 2), FST::RELATION('\t', 1),
		FST::RELATION('{', 2), FST::RELATION('{', 1),
		FST::RELATION('}', 2), FST::RELATION('}', 1),
		FST::RELATION('(', 2), FST::RELATION('(', 1),
		FST::RELATION(')', 2), FST::RELATION(')', 1),
		FST::RELATION('=', 2), FST::RELATION('=', 1),
		FST::RELATION('-', 2), FST::RELATION('-', 1),
		FST::RELATION('+', 2), FST::RELATION('+', 1),
		FST::RELATION('*', 2), FST::RELATION('*', 1),
		FST::RELATION('/', 2), FST::RELATION('/', 1),
		FST::RELATION(',', 2), FST::RELATION(',', 1),
		FST::RELATION(';', 2), FST::RELATION(';', 1),
		FST::RELATION(' ', 2), FST::RELATION(' ', 1),
		FST::RELATION('0', 2), FST::RELATION('0', 1),						//72
		FST::RELATION('1', 2), FST::RELATION('1', 1),
		FST::RELATION('2', 2), FST::RELATION('2', 1),
		FST::RELATION('3', 2), FST::RELATION('3', 1),
		FST::RELATION('4', 2), FST::RELATION('4', 1),
		FST::RELATION('5', 2), FST::RELATION('5', 1),
		FST::RELATION('6', 2), FST::RELATION('6', 1),
		FST::RELATION('7', 2), FST::RELATION('7', 1),
		FST::RELATION('8', 2), FST::RELATION('8', 1),
		FST::RELATION('9', 2), FST::RELATION('9', 1),
		FST::RELATION('a', 2), FST::RELATION('a', 1),
		FST::RELATION('b', 2), FST::RELATION('b', 1),
		FST::RELATION('c', 2), FST::RELATION('c', 1),
		FST::RELATION('d', 2), FST::RELATION('d', 1),
		FST::RELATION('e', 2), FST::RELATION('e', 1),
		FST::RELATION('f', 2), FST::RELATION('f', 1),
		FST::RELATION('g', 2), FST::RELATION('g', 1),
		FST::RELATION('h', 2), FST::RELATION('h', 1),
		FST::RELATION('i', 2), FST::RELATION('i', 1),
		FST::RELATION('j', 2), FST::RELATION('j', 1),
		FST::RELATION('k', 2), FST::RELATION('k', 1),
		FST::RELATION('l', 2), FST::RELATION('l', 1),
		FST::RELATION('m', 2), FST::RELATION('m', 1),
		FST::RELATION('n', 2), FST::RELATION('n', 1),
		FST::RELATION('o', 2), FST::RELATION('o', 1),
		FST::RELATION('p', 2), FST::RELATION('p', 1),
		FST::RELATION('q', 2), FST::RELATION('q', 1),
		FST::RELATION('r', 2), FST::RELATION('r', 1),
		FST::RELATION('s', 2), FST::RELATION('s', 1),
		FST::RELATION('t', 2), FST::RELATION('t', 1),
		FST::RELATION('u', 2), FST::RELATION('u', 1),
		FST::RELATION('v', 2), FST::RELATION('v', 1),
		FST::RELATION('w', 2), FST::RELATION('w', 1),
		FST::RELATION('x', 2), FST::RELATION('x', 1),
		FST::RELATION('y', 2), FST::RELATION('y', 1),
		FST::RELATION('z', 2), FST::RELATION('z', 1)),
	FST::NODE(1, FST::RELATION('\'', 3)),
	FST::NODE()
);


//__________________________________________________________________________




namespace LA
{
	int line = 0, col = 0;
	int character = 0;
	char word[LT_MAXSIZE];
	LT::LexTable ltable;
	IT::IdTable itable;
	IT::IDDATATYPE dataType;
	IT::IDTYPE idType;
	bool scope;				//???????????????????????????????????????????????????

	bool newLex(FST::FST& fst, char* word, char lexema)
	{
		bool rc = false;
		FST::newFST(fst, word);
		if (FST::execute(fst))
		{
			rc = true;
			addLex(lexema);
		}
		return rc;
	}

	void addLex(char lexema)
	{
		LT::Entry lEntry = { lexema, line, (int)LT_TI_NULLIDX };
		if (lexema == LEX_ID)
			lEntry.indxTI = line;
		LT::Add(ltable, lEntry);
	}

	void addId(char* word, IT::IDDATATYPE dataType, IT::IDTYPE idType)
	{
		if (word[0] != '\'' && (word[0] <= 47 || word[0] >= 58))								//for ID
		{
			IT::Entry iEntry;
			bool std = false;
			for (int i = 0; i < STD_BIBLE_SIZE; i++)
				if (strcmp(StdBible[i], word) == 0)
				{
					std = true;
					break;
				}
			if ((strlen(word) > ID_MAXSIZE) && !std)
				word[ID_MAXSIZE] = '\0';
			bool isExecute = false;
			for (int i = 0; i <= itable.size; i++)
				if (strcmp(itable.table[i].id, word) == 0)
				{
					isExecute = true;
					break;
				}
			if (isExecute)
			{
				if (dataType != IT::NONE)
				{
					throw ERROR_THROW_IN(8, line, col);
				}
				else return;
			}
			else
			{
				if (dataType == IT::NONE)
					throw ERROR_THROW_IN(9, line, col);
				strcpy(iEntry.id, word);
				iEntry.iddatatype = dataType;
				iEntry.idtype = idType;
				iEntry.value.vint = TI_INT_DEFAULT;
				iEntry.value.vstr->len = TI_STR_DEFAULT;
				strcpy(iEntry.value.vstr->str, "");
				iEntry.idxfirstLE = ltable.table[ltable.size].indxTI;
				IT::Add(itable, iEntry);
			}
		}
		else																				//for literal
		{
			if (ltable.table[ltable.size - 3].lexema != LEX_INTEGER || ltable.table[ltable.size - 3].lexema != LEX_INTEGER)								//if literal is not for declarating of variable
			{
				IT::Entry iEntry;
				strcpy(iEntry.id, "LITERAL");
				iEntry.iddatatype = dataType;
				iEntry.idtype = idType;
				if (dataType == IT::INT)
				{
					long double bufNum = std::atoi(word);
					if (bufNum > INT_MAX)
						throw ERROR_THROW_IN(12, line, col);
					iEntry.value.vint = bufNum;
				}
				else
				{
					if (strlen(word) > 255)
						throw ERROR_THROW_IN(11, line, col);
					iEntry.value.vstr->len = strlen(word);
					strcpy(iEntry.value.vstr->str, word);
				}
				iEntry.idxfirstLE = line;
				IT::Add(itable, iEntry);
				return;
			}
			//if (ltable.table[ltable.size - 3].lexema != dataType)							//if type of literal doesnt compare with its id type
			//	throw ERROR_THROW_IN(13, line, col);
			if (word[0] > 47 && word[0] < 58)												//int literal
			{
				for (int i = 0; i < itable.size; i++)
					if (itable.table[i].idxfirstLE == line)
					{
						long double bufNum = std::atoi(word);
						if (bufNum > INT_MAX)
							throw ERROR_THROW_IN(12, line, col);
						itable.table[i].value.vint = (int)bufNum;
						return;
					}
			}
			else																			//string literal
				for (int i = 0; i < itable.size; i++)
					if (itable.table[i].idxfirstLE == line)
					{
						if (strlen(word) > 255)
							throw ERROR_THROW_IN(11, line, col);
						itable.table[i].value.vstr->len = strlen(word);
						strcpy(itable.table[i].value.vstr->str, word);
						return;
					}
		}
	}

	bool isLetter(char ch)
	{
		return ch == LEX_SPACE || ch == LEX_APOS || ch == LEX_ENDL || ch == LEX_MINUS || ch == LEX_PLUS || ch == LEX_COMPARE || ch == LEX_DIRSLASH || ch == LEX_STAR || ch == LEX_LEFTHESIS || ch == LEX_RIGHTHESIS || ch == LEX_LEFTBRACE || ch == LEX_BRACELET || ch == LEX_SEMICOLON || ch == LEX_COMMA || ch == LEX_END;
	}

	void LexAnalizator(char inText[IN_MAX_LEN_TEXT], Log::LOG log)
	{
		ltable = LT::Create(LT_TABLE_SIZE);
		itable = IT::Create(TI_TABLE_SIZE);
		dataType = IT::NONE;
		idType = IT::L;
		for (unsigned int i = 0; i < strlen(inText); i++)
		{
			bool rc = false;
			word[character] = inText[i];
			character++;
			if (isLetter(inText[i]))
			{
				word[1] = LEX_END;
				character = 0;
			}
			switch (inText[i])
			{
			case LEX_ENDL:
			{
				col = 0;
				line++;
				rc = true;
				continue;
			}
			case LEX_TAB:
			{
				rc = true;
				break;
			}
			case LEX_SPACE:
			{
				rc = true;
				while(inText[i + 1] == LEX_SPACE)
					i++;
				break;
			}
			case LEX_LEFTHESIS:
			{
				rc = newLex(fstLeftThesis, word, LEX_LEFTHESIS);
				break;
			}
			case LEX_RIGHTHESIS:
			{
				rc = newLex(fstRightThesis, word, LEX_RIGHTHESIS);
				break;
			}
			case LEX_LEFTBRACE:
			{
				rc = newLex(fstLeftBrace, word, LEX_LEFTBRACE);
				break;
			}
			case LEX_BRACELET:
			{
				rc = newLex(fstRightBrace, word, LEX_BRACELET);
				break;
			}
			case LEX_SEMICOLON:
			{
				rc = newLex(fstSemiColon, word, LEX_SEMICOLON);
				break;
			}
			case LEX_COMMA:
			{
				rc = newLex(fstComma, word, LEX_COMMA);
				break;
			}
			case LEX_PLUS:
			case LEX_STAR:
			case LEX_DIRSLASH:
			case LEX_MINUS:
				rc = newLex(fstV, word, LEX_SIGN);
				break;
			case LEX_COMPARE:
			{
				rc = newLex(fstV, word, LEX_COMPARE);
				break;
			}
			case LEX_APOS:
			{
				word[0] = LEX_END;
				character = 0;
				char strLex[TI_STR_MAXSIZE];
				int j = 0;
				do
				{
					strLex[j] = inText[i];
					j++;
					if (inText[i + 1] == LEX_END)
						throw ERROR_THROW_IN(7, line, col);
					i++;
				} while (inText[i] != LEX_APOS);
				strLex[j] = inText[i];
				strLex[j + 1] = LEX_END;
				newLex(fstStringLiteral, strLex, LEX_LITERAL);
				addId(strLex, IT::STR, IT::L);
				rc = true;
				break;
			}
			default:
				rc = true;
				if (isLetter(inText[i + 1]))
				{
					word[character] = LEX_END;
					bool wordLex = isThatLexem(word);
					if (!wordLex)													//when 'word' is id
					{
						if (word[0] > 47 && word[0] < 58)
							throw ERROR_THROW_IN(10, line, col);
						addLex(LEX_ID);
						addId(word, dataType, idType);
						dataType = IT::NONE;
					}
					word[0] = LEX_END;
					character = 0;
				}
				break;
			}
			col++;
			if (!rc)
				throw ERROR_THROW_IN(2, line, col);
		}

		Log::WriteLex(log, ltable);
		Log::WriteId(log, itable);
		IT::Delete(itable);
		LT::Delete(ltable);
	}

	bool isThatLexem(char word[])
	{
		bool rc = false;
		rc = newLex(fstIntType, word, LEX_INTEGER);
		if (rc)
		{
			dataType = IT::INT;
			if (idType == IT::F)
				idType = IT::P;
			return rc;
		}
		rc = newLex(fstStrType, word, LEX_STRING);
		if (rc)
		{
			dataType = IT::STR;
			if (idType == IT::F)
				idType = IT::P;
			return rc;
		}
		rc = newLex(fstDeclare, word, LEX_DECLARE);
		if (rc)
		{
			idType = IT::V;
			return rc;
		}
		rc = newLex(fstFunction, word, LEX_FUNCTION);
		if (rc)
		{
			idType = IT::F;
			return rc;
		}
		rc = newLex(fstMain, word, LEX_MAIN);
		if (rc) return rc;
		rc = newLex(fstPrint, word, LEX_PRINT);
		if (rc)
		{
			idType = IT::V;
			return rc;
		}
		rc = newLex(fstReturn, word, LEX_RETURN);
		if (rc)
		{
			idType = IT::V;
			return rc;
		}
		rc = newLex(fstIntegerLiteral, word, LEX_LITERAL);
		if (rc)
		{
			addId(word, IT::INT, IT::L);
			return rc;
		}
		return rc;
	}

}