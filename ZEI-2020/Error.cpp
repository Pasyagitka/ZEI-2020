#include "Error.h"

namespace Error
{
	//����� ������ : 0 - 99 - ��������� ������
	//				100 - 109 - ������ ����������
	//				110 - 119 - ������ �������� � ������ ������
	//				300 - 399 - ������ ������������ �������
	//				400 - 499 - ������ ��������������� �������
	//				500 - 599 - ������ �������������� ������� - ��������������� ��������� ���������� Error
	ERROR errors[ERROR_MAX_ENTRY] = //������� ������
	{
		ERROR_ENTRY(0, "������������ ��� ������"), // ��� ������ ��� ��������� 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1, "��������� ����"),
		
		ERROR_ENTRY(100, "[!] �������� -in ������ ���� �����"),
		ERROR_ENTRY(101, "[!] ��������� ����� �������� ���������"),

		ERROR_ENTRY(110, "[!] ������ ��� �������� ����� � �������� ����� (-in)"),
		ERROR_ENTRY(111, "[!] ������������ ������ � �������� ����� (-in)"),
		ERROR_ENTRY(112, "[!] ������ ��� �������� ����� ���������(-log)"),
		ERROR_ENTRY(113, "[!] ������ ��� �������� ����� � �������� ������(-lex)"),
		ERROR_ENTRY(114, "[!] ������ ��� �������� ����� � �������� ���������������(-id)"),

		ERROR_ENTRY(300, "[LA|L] �������� ������������ ������ ������� ������"),
		ERROR_ENTRY(301, "[LA|I] ������� ������ �����������"),
		ERROR_ENTRY(302, "[LA|L] ������� ������, ��������, ��� �� �������"),
		ERROR_ENTRY(303, "[LA|L] ������������ ����� ������ ������� ������"),
		ERROR_ENTRY(304, "[LA|I] �������� ������������ ������ ������� ���������������"),
		ERROR_ENTRY(305, "[LA|I] ������� ��������������� �����������"),
		ERROR_ENTRY(306, "[LA|I] ������� ���������������, ��������, ��� �� �������"),
		ERROR_ENTRY(307, "[LA|I] ������������ ����� ������ ������� ���������������"),

		ERROR_ENTRY(500, "[SEM] �������� ��������� ���������"),
		ERROR_ENTRY(501, "[SEM] ��������� ��������"),
		ERROR_ENTRY(502, "[SEM] ������ � ���������"),
		ERROR_ENTRY(503, "[SEM] ������ � ���������� �������"),
		ERROR_ENTRY(504, "[SEM] ������ � ���������� ���������� �������"),
	};
	ERROR geterror(int id)
	{
		ERROR newError{};
		(id < 0 && id > ERROR_MAX_ENTRY) ?	newError = errors[0] : newError = errors[id];
		return newError;
	}
	ERROR geterrorin(int id, short line = -1, short col = -1)
	{
		ERROR newError{};
		if (id < 0 && id > ERROR_MAX_ENTRY) {
			newError = errors[0];
		}
		else {
			newError = errors[id];
			newError.inext.line = line;
			newError.inext.col = col;
		}
		return newError;
	}
};