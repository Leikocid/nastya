#pragma once
#define LT_TABLE_SIZE 300
#define LT_MAXSIZE 4096					//������������ ���-�� ����� � ������� ������
#define LT_TI_NULLIDX 0xffffffff		//��� ��-�� ������� ����������������
#define LEX_INTEGER 't'
#define LEX_STRING 't'
#define LEX_ID 'i'
#define LEX_LITERAL 'l'
#define LEX_MAIN 'm'
#define LEX_FUNCTION 'f'
#define LEX_DECLARE 'd'
#define LEX_RETURN 'r'
#define LEX_PRINT 'p'
#define LEX_SEMICOLON ';'
#define LEX_COMMA ','
#define LEX_LEFTBRACE '{'
#define LEX_BRACELET '}'
#define LEX_LEFTHESIS '('
#define LEX_RIGHTHESIS ')'
#define LEX_COMPARE '='
#define LEX_PLUS '+'
#define LEX_MINUS '-'
#define LEX_STAR '*'
#define LEX_DIRSLASH '/'
#define LEX_SIGN 'v'
#define LEX_TAB '\t'
#define LEX_ENDL '\n'
#define LEX_END '\0'
#define LEX_APOS '\''
#define LEX_SPACE ' '


namespace LT
{
	struct Entry						//������ ������� ������
	{
		char lexema;
		int sn;							//����� ������ � ������
		int indxTI;						//������ � ������� ��������������� ��� LT_TI_NULLIDX
	};

	struct LexTable						//�������� ������� ������
	{
		int maxsize;					//������� ������� ������( < LT_MAXSIZE)
		int size;						//������� ������ ������� ������ ( < maxsize)
		Entry* table;					//������ ����� ������� ������
	};
	LexTable Create(int);				//������� ������� ������(������� ������� ������ < LT_MAXSIZE)
	void Add(LexTable&, Entry&);			//�������� ������ � ������� ������(lextable, entry)
	Entry GetEntry(LexTable&, int);		//�������� ������ ������� ������(lextable, '����� ���������� ������')
	void Delete(LexTable&);				//������� ������� ������
}