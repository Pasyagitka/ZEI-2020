#include "Error.h"

namespace Error
{
	//TODO ���� ����� ��������� - ������� ��� ����������
	//����� ������ : 0 - 99 - ��������� ������
	//				100 - 109 - ������ ����������
	//				110 - 119 - ������ �������� � ������ ������
	//				300 - 399 - ������ ������������ �������
	//				400 - 499 - ������ ��������������� �������
	//				500 - 599 - ������ �������������� ������� - ��������������� ��������� ���������� Error
	ERROR errors[ERROR_MAX_ENTRY] = //������� ������
	{
		ERROR_ENTRY(0, "[!] ������������ ��� ������"), // ��� ������ ��� ��������� 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1, "[!] ��������� ����"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5), ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "[!] �������� -in ������ ���� �����"),
		ERROR_ENTRY(101, "[!] ��������� ����� �������� ���������"),
		ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103), ERROR_ENTRY_NODEF(104), ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107), ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "[!] ������ ��� �������� ����� � �������� ����� (-in)"),
		ERROR_ENTRY(111, "[!] ������������ ������ � �������� ����� (-in)"),
		ERROR_ENTRY(112, "[!] ������ ��� �������� ����� ���������(-log)"),
		ERROR_ENTRY(113, "[!] ������ ��� �������� ����� � �������� ������(-lex)"),
		ERROR_ENTRY(114, "[!] ������ ��� �������� ����� � �������� ���������������(-id)"),
		ERROR_ENTRY_NODEF(115), ERROR_ENTRY_NODEF(116),ERROR_ENTRY_NODEF(117),ERROR_ENTRY_NODEF(118),ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200),
		ERROR_ENTRY(300, "[LA] �������� ������������ ������ ������� ������"),
		ERROR_ENTRY(301, "[LA] ������� ������ �����������"),
		ERROR_ENTRY(302, "[LA] ������� ������, ��������, ��� �� �������"),
		ERROR_ENTRY(303, "[LA] ������������ ����� ������ ������� ������"),
		ERROR_ENTRY(304, "[LA] �������� ������������ ������ ������� ���������������"),
		ERROR_ENTRY(305, "[LA] ������� ��������������� �����������"),
		ERROR_ENTRY(306, "[LA] ������� ���������������, ��������, ��� �� �������"),
		ERROR_ENTRY(307, "[LA] ������������ ����� ������ ������� ���������������"),
		ERROR_ENTRY(308, "[LA] ��������� ������������ ����� ����� ��������������"),	
		ERROR_ENTRY(309, "[LA] �������� ��� ��������� ��� �������� ���� tiny [-128; +127]d"),
		ERROR_ENTRY(310, "[LA] ��������� ������������ ����� �������� ���� symbolic"),
		ERROR_ENTRY(311, "[LA] ������ ������������ �������"),	
		ERROR_ENTRY_NODEF(312),ERROR_ENTRY_NODEF(313),ERROR_ENTRY_NODEF(314),ERROR_ENTRY_NODEF(315),
		ERROR_ENTRY_NODEF(316),ERROR_ENTRY_NODEF(317),ERROR_ENTRY_NODEF(318),ERROR_ENTRY_NODEF(319),
		ERROR_ENTRY_NODEF10(320), ERROR_ENTRY_NODEF10(330), ERROR_ENTRY_NODEF10(340), ERROR_ENTRY_NODEF10(350),
		ERROR_ENTRY_NODEF10(360), ERROR_ENTRY_NODEF10(370), ERROR_ENTRY_NODEF10(380), ERROR_ENTRY_NODEF10(390),
		ERROR_ENTRY_NODEF100(400),
		ERROR_ENTRY(500, "[SX] �������� ��������� ���������"),
		ERROR_ENTRY(501, "[SX] �������� ������ ���������� �������"),
		ERROR_ENTRY(502, "[SX] �������� ������ ���������� ������� ��� � ����������"),
		ERROR_ENTRY(503, "[SX] ����������� ���� �������"),
		ERROR_ENTRY(504, "[SX] �������� ���������. ��������� ������ �������������� � ��������"),
		ERROR_ENTRY(505, "[SX] ������ � ���� ��������� "),
		ERROR_ENTRY(506, "[SX] �������� ����������� � ���� �������"),
		ERROR_ENTRY(507, "[SX] ������ � �������� ���������"),
		ERROR_ENTRY(508, "[SX] ������ � ������ �������"),
		ERROR_ENTRY(509, "[SX] ������ � ���������� ���������� �������"),
		ERROR_ENTRY(510, "[SX] ������ ��� �������������� ��� ��������� ���������"),
		ERROR_ENTRY(511, "[SX] �������� ����������� � ���� �����/��������� ���������"),
	
		ERROR_ENTRY_NODEF(512), ERROR_ENTRY_NODEF(513),ERROR_ENTRY_NODEF(514),ERROR_ENTRY_NODEF(515),
		ERROR_ENTRY_NODEF(516),ERROR_ENTRY_NODEF(517),ERROR_ENTRY_NODEF(518),ERROR_ENTRY_NODEF(519),
		ERROR_ENTRY_NODEF10(520), ERROR_ENTRY_NODEF10(530), ERROR_ENTRY_NODEF10(540), ERROR_ENTRY_NODEF10(550),
		ERROR_ENTRY_NODEF10(560), ERROR_ENTRY_NODEF10(570), ERROR_ENTRY_NODEF10(580), ERROR_ENTRY_NODEF10(590),

		ERROR_ENTRY(600, "[SM] "),	//����� �������������� ������
		ERROR_ENTRY(601, "[SM] �������� ���������. ��������� ���������� ��� logical"),	
		/**/ERROR_ENTRY(602, "[SM] ����������� ����� ����� � ��������� perform"),
		/**/ERROR_ENTRY(603, "[SM] ������������ ����� ����� ����� ����� � ��������� perform"),
		/**/ERROR_ENTRY(604, "[SM] ������������� �� ��������"),
		/*!!!*/ERROR_ENTRY(605, "[SM] ���������� ������� ������� � ����������� ���������������"),
		/**/ERROR_ENTRY(606, "[SM] ������������� ��� ���������"),
		ERROR_ENTRY(607, "[SM]"),
		/**/ERROR_ENTRY(608, "[SM] ������������ ���� ������� � ���� ������������� ��������"),
		ERROR_ENTRY(607, "[SM]"),
		/**/ERROR_ENTRY(610, "[SM] �������� ��������� ���������� �������"),
		/**/ERROR_ENTRY(611, "[SM] ������� ����� ���������� � ������ �������"),
		/**/ERROR_ENTRY(612, "[SM] ������� ���� ���������� � ������ �������"),
		/**/ERROR_ENTRY(613, "[SM] ���� ������ � ��������� �� ���������"),
		/**/ERROR_ENTRY(614, "[SM] �������������� �������� ����� ����������� ������ ��� ����� tiny"),
		/**/ERROR_ENTRY(615, "[SM] ���������� �������� ����� ����������� ������ ��� ����� tiny"),
		/**/ERROR_ENTRY(616, "[SM] ��������� �������� ����� ����������� ������ ��� ����� tiny"),
		/**/ERROR_ENTRY(617, "[SM] �������� ���������. ������������ ����� � ���������"),
		/**/ERROR_ENTRY(618, "[SM] �������� ���������. ������� �� 0")
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