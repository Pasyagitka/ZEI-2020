//#include "SEM.h"
//#include "Error.h"
//#include "LT.h"
//#include "IT.h"
//
//namespace SM
//{
//	void DivideByZero(LT::LexTable& ltable, char* literal)
//	{
//		for (unsigned int i = 0; i < (unsigned int)ltable.size; i++)
//		{
//			if (ltable.table[i].lexema == LEX_LITERAL && ltable.table[i - 1].lexema == LEX_SLASH && strcmp(literal, "0") == 0)
//			{
//				throw ERROR_THROW(704, ltable.table[i].sn, ltable.table[i - 1].indxTI);
//			}
//		}
//	}
//	void OneLib(LT::LexTable& ltable, bool flag)
//	{
//		int k = 0;
//		if (flag)
//		{
//			k = 1;
//		}
//		if (k == 1)
//		{
//			for (unsigned int i = 0; i < (unsigned int)ltable.size; i++)
//			{
//				if (ltable.table[i].lexema == LEX_LIB)
//				{
//					throw ERROR_THROW(705, ltable.table[i].sn, ltable.table[i].indxTI);
//				}
//			}
//		}
//	}
//	void LogicalLiteral(LT::LexTable& ltable, IT::IdTable& itable)
//	{
//		for (unsigned int i = 0; i < (unsigned int)ltable.size; i++)
//		{
//			if (ltable.table[i].lexema == LEX_ID && ltable.table[i - 2].lexema == LEX_WHEN && ltable.table[i + 1].lexema == LEX_RIGHTHESIS)
//			{
//				for (unsigned int j = 0; j < (unsigned int)itable.size; j++)
//				{
//					if (strcmp(ltable.table[i].buf, itable.table[j].id) == 0)
//					{
//						if (itable.table[j].iddatatype != IT::LGCL)
//						{
//							throw ERROR_THROW(703, ltable.table[i].sn, ltable.table[i].indxTI);
//						}
//					}
//				}
//			}
//			if (ltable.table[i].lexema == LEX_LITERAL && ltable.table[i - 2].lexema == LEX_WHEN && ltable.table[i + 1].lexema == LEX_RIGHTHESIS)
//			{
//				for (unsigned int j = 0; j < (unsigned int)itable.size; j++)
//				{
//					if (strcmp(ltable.table[i].buf, itable.table[j].value.vstr->str) == 0)
//					{
//						if (itable.table[j].iddatatype != IT::LGCL)
//						{
//							throw ERROR_THROW(703, ltable.table[i].sn, ltable.table[i].indxTI);
//						}
//					}
//					if (ltable.table[i].sign == itable.table[j].value.vint)
//					{
//						if (itable.table[j].iddatatype != IT::LGCL)
//						{
//							throw ERROR_THROW(703, ltable.table[i].sn, ltable.table[i].indxTI);
//						}
//					}
//				}
//			}
//		}
//	}
//	void Operation(LT::LexTable& ltable, IT::IdTable& itable)
//	{
//		for (unsigned int i = 0; i < (unsigned int)ltable.size; i++)
//		{
//			char* buf[LT_MAXSIZE];
//			int k = 0, l = 0, m = 0, n = 0;
//			if (ltable.table[i].lexema == LEX_ID && ltable.table[i - 1].sign == 1 || ltable.table[i + 1].sign == 1)
//			{
//				if (ltable.table[i].lexema == LEX_ID)
//				{
//					n = ltable.table[i].sn;
//					m = ltable.table[i].indxTI;
//				}
//				while (ltable.table[i].lexema != LEX_POINT)
//				{
//					if (ltable.table[i].lexema == LEX_ID)
//					{
//						buf[k] = ltable.table[i].buf;
//						k++;
//					}
//					i++;
//				}
//				for (unsigned int l = 0; l < (unsigned int)k; l++)
//				{
//					for (unsigned int j = 0; j < (unsigned int)itable.size; j++)
//					{
//						if (strcmp(buf[l], itable.table[j].id) == 0)
//						{
//							if (itable.table[j].iddatatype != IT::TINY)
//							{
//								throw ERROR_THROW(706, n, m);
//							}
//						}
//					}
//				}
//			}
//			if (ltable.table[i].lexema == LEX_ID && ltable.table[i - 1].sign == 2 || ltable.table[i + 1].sign == 2)
//			{
//				if (ltable.table[i].lexema == LEX_ID)
//				{
//					n = ltable.table[i].sn;
//					m = ltable.table[i].indxTI;
//				}
//				while (ltable.table[i].lexema != LEX_RIGHTHESIS)
//				{
//					if (ltable.table[i].lexema == LEX_ID)
//					{
//						buf[k] = ltable.table[i].buf;
//						k++;
//					}
//					i++;
//				}
//				for (unsigned int l = 0; l < (unsigned int)k; l++)
//				{
//					for (unsigned int j = 0; j < (unsigned int)itable.size; j++)
//					{
//						if (strcmp(buf[l], itable.table[j].id) == 0)
//						{
//							if (itable.table[j].iddatatype != IT::TINY)
//							{
//								throw ERROR_THROW(707, n, m);
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//	void Operationl(LT::LexTable& ltable, IT::IdTable& itable)
//	{
//		for (unsigned int i = 0; i < (unsigned int)ltable.size; i++)
//		{
//			char* buf[LT_MAXSIZE];
//			int k = 0, z = 0, m = 0, n = 0;
//			if (ltable.table[i].lexema == LEX_LITERAL && ltable.table[i - 1].sign == 1 || ltable.table[i + 1].sign == 1)
//			{
//				if (ltable.table[i].lexema == LEX_LITERAL)
//				{
//					m = ltable.table[i].sn;
//					n = ltable.table[i].indxTI;
//				}
//				while (ltable.table[i].lexema != LEX_POINT)
//				{
//					if (ltable.table[i].lexema == LEX_LITERAL && ltable.table[i].sign == -1)
//					{
//						throw ERROR_THROW(706, m, n + 3);
//					}
//					i++;
//				}
//			}
//			if (ltable.table[i].lexema == LEX_LITERAL && ltable.table[i - 1].sign == 2 || ltable.table[i + 1].sign == 2)
//			{
//				if (ltable.table[i].lexema == LEX_LITERAL)
//				{
//					m = ltable.table[i].sn;
//					n = ltable.table[i].indxTI;
//				}
//				while (ltable.table[i].lexema != LEX_RIGHTHESIS)
//				{
//					if (ltable.table[i].lexema == LEX_LITERAL && ltable.table[i].sign == -1)
//					{
//						throw ERROR_THROW(706, m, n + 3);
//					}
//					i++;
//				}
//			}
//		}
//	}
//	void Pereobyavl(LT::LexTable& ltable, IT::IdTable& itable, char* buf, char* postfix, int line, int col)
//	{
//		for (unsigned int i = 0; i < (unsigned int)ltable.size; i++)
//		{
//			if (ltable.table[i].lexema == LEX_ID && ltable.table[i - 1].lexema == LEX_SYMBOLIC && line == ltable.table[i].sn && ltable.table[i].indxTI == col)
//			{
//				for (unsigned int j = 0; j < (unsigned int)itable.size; j++)
//				{
//					if (strcmp(buf, itable.table[j].id) == 0 && strcmp(postfix, itable.table[j].postfix) == 0)
//					{
//						throw ERROR_THROW(709, line, col);
//					}
//				}
//			}
//		}
//	}
//	void Proverka(LT::LexTable& ltable, IT::IdTable& itable)
//	{
//		for (unsigned int i = 0; i < (unsigned int)ltable.size; i++)
//		{
//			int k = 0;
//			if (ltable.table[i].lexema != LEX_TINY && ltable.table[i].lexema != LEX_FUNCTION && ltable.table[i + 1].lexema == LEX_ID)
//			{
//				for (unsigned int j = 0; j < (unsigned int)itable.size; j++)
//				{
//					if (strcmp(ltable.table[i + 1].buf, itable.table[j].id) == 0)
//					{
//						k++;
//					}
//				}
//				if (k == 0)
//					throw ERROR_THROW(710, ltable.table[i + 1].sn, ltable.table[i + 1].indxTI);
//			}
//		}
//	}
//	void RetValue(LT::LexTable& ltable, IT::IdTable& itable)
//	{
//		for (unsigned int i = 0; i < (unsigned int)ltable.size; i++)
//		{
//			IT::IDDATATYPE datatype;
//			if (ltable.table[i].lexema == LEX_FUNCTION && ltable.table[i + 1].lexema == LEX_ID)
//			{
//				for (unsigned int j = 0; j < (unsigned int)itable.size; j++)
//				{
//					if (strcmp(ltable.table[i + 1].buf, itable.table[j].id) == 0)
//					{
//						datatype = itable.table[j].iddatatype;
//					}
//				}
//				while (ltable.table[i].lexema != LEX_GIVEBACK)
//				{
//					i++;
//				}
//				if (ltable.table[i + 1].lexema == LEX_ID)
//				{
//					for (unsigned int l = 0; l < (unsigned int)itable.size; l++)
//					{
//						if (strcmp(ltable.table[i + 1].buf, itable.table[l].id) == 0)
//						{
//							if (datatype != itable.table[l].iddatatype)
//							{
//								throw ERROR_THROW(708, ltable.table[i + 1].sn, ltable.table[i + 1].indxTI);
//							}
//						}
//					}
//				}
//				if (ltable.table[i + 1].lexema == LEX_LITERAL)
//				{
//					for (unsigned int l = 0; l < (unsigned int)itable.size; l++)
//					{
//						if (strcmp(ltable.table[i + 1].buf, itable.table[l].value.vstr->str) == 0)
//						{
//							if (datatype != itable.table[l].iddatatype)
//							{
//								throw ERROR_THROW(708, ltable.table[i + 1].sn, ltable.table[i + 1].indxTI);
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//	void InicialId(LT::LexTable& ltable, IT::IdTable& itable)
//	{
//		IT::IDDATATYPE datatype;
//		for (unsigned int i = 0; i < (unsigned int)ltable.size; i++)
//		{
//			char* buf[LT_MAXSIZE];
//			IT::IDDATATYPE data[LT_MAXSIZE];
//			int k = 0;
//			int z = 0;
//			bool flag = true;
//			if (ltable.table[i].lexema == LEX_ID && ltable.table[i + 1].lexema == LEX_COMPARE && ltable.table[i + 2].lexema == LEX_LIBFUNC)
//			{
//				if (ltable.table[i + 2].parm == 1)
//				{
//					buf[0] = ltable.table[i].buf;
//					for (unsigned int j = 0; j < (unsigned int)itable.size; j++)
//					{
//						if (strcmp(buf[0], itable.table[j].id) == 0)
//						{
//							if (itable.table[j].iddatatype != IT::TINY)
//							{
//								throw ERROR_THROW(702, ltable.table[i].sn, ltable.table[i].indxTI);
//							}
//						}
//					}
//				}
//				if (ltable.table[i + 2].parm == 2)
//				{
//					buf[0] = ltable.table[i].buf;
//					for (unsigned int j = 0; j < (unsigned int)itable.size; j++)
//					{
//						if (strcmp(buf[0], itable.table[j].id) == 0)
//						{
//							if (itable.table[j].iddatatype != IT::SYMB)
//							{
//								throw ERROR_THROW(702, ltable.table[i].sn, ltable.table[i].indxTI);
//							}
//						}
//					}
//				}
//				continue;
//			}
//			if (ltable.table[i].lexema == LEX_ID && ltable.table[i + 1].lexema == LEX_COMPARE && ltable.table[i + 2].lexema == LEX_ID && ltable.table[i + 3].lexema == LEX_LEFTHESIS)
//			{
//				for (unsigned int j = 0; j < (unsigned int)itable.size; j++)
//				{
//					if (strcmp(ltable.table[i + 2].buf, itable.table[j].id) == 0)
//					{
//						if (itable.table[j].idtype == IT::F)
//						{
//							datatype = itable.table[j].iddatatype;
//							flag = false;
//						}
//					}
//				}
//				if (!flag)
//				{
//					for (unsigned int l = 0; l < (unsigned int)itable.size; l++)
//					{
//						if (strcmp(ltable.table[i].buf, itable.table[l].id) == 0)
//						{
//							if (datatype != itable.table[l].iddatatype)
//							{
//								throw ERROR_THROW(702, ltable.table[i].sn, ltable.table[i - 1].indxTI);
//							}
//						}
//					}
//				}
//				continue;
//			}
//			if (ltable.table[i].lexema == LEX_ID && ltable.table[i + 1].lexema == LEX_COMPARE && ltable.table[i + 2].lexema == LEX_ID)
//			{
//				while (ltable.table[i].lexema != LEX_POINT)
//				{
//					if (ltable.table[i].lexema == LEX_ID)
//					{
//						buf[k] = ltable.table[i].buf;
//						k++;
//					}
//					i++;
//				}
//				for (unsigned int l = 0; l < (unsigned int)k; l++)
//				{
//					for (unsigned int j = 0; j < (unsigned int)itable.size; j++)
//					{
//						if (strcmp(buf[l], itable.table[j].id) == 0)
//						{
//							data[z] = itable.table[j].iddatatype;
//							z++;
//						}
//					}
//				}
//				datatype = data[0];
//				for (unsigned int m = 0; m < (unsigned int)z; m++)
//				{
//					if (data[m] != datatype)
//					{
//						throw ERROR_THROW(702, ltable.table[i].sn, ltable.table[i].indxTI);
//					}
//				}
//			}
//
//		}
//	}
//	void InicialL(LT::LexTable& ltable, IT::IdTable& itable)
//	{
//		IT::IDDATATYPE datatype;
//		for (unsigned int i = 0; i < (unsigned int)ltable.size; i++)
//		{
//			char* buf[LT_MAXSIZE];
//			IT::IDDATATYPE data[LT_MAXSIZE];
//			int k = 0;
//			int z = 0;
//			bool flag = true;
//			if (ltable.table[i].lexema == LEX_ID && ltable.table[i + 1].lexema == LEX_COMPARE && ltable.table[i + 2].lexema == LEX_LITERAL)
//			{
//				for (unsigned int j = 0; j < (unsigned int)itable.size; j++)
//				{
//					if (strcmp(ltable.table[i].buf, itable.table[j].id) == 0)
//					{
//						datatype = itable.table[j].iddatatype;
//						break;
//					}
//				}
//				while (ltable.table[i].lexema != LEX_POINT)
//				{
//					if (ltable.table[i].lexema == LEX_LITERAL)
//					{
//						buf[k] = ltable.table[i].buf;
//						k++;
//					}
//					i++;
//				}
//				for (unsigned int l = 0; l < (unsigned int)k; l++)
//				{
//					for (unsigned int j = 0; j < (unsigned int)itable.size; j++)
//					{
//						if (strcmp(buf[l], itable.table[j].value.vstr->str) == 0)
//						{
//							data[z] = itable.table[j].iddatatype;
//							z++;
//						}
//					}
//				}
//				for (unsigned int m = 0; m < (unsigned int)z; m++)
//				{
//					if (data[m] != datatype)
//					{
//						throw ERROR_THROW(702, ltable.table[i].sn, ltable.table[i].indxTI);
//					}
//				}
//			}
//
//		}
//	}
//	void Parametrs(LT::LexTable& ltable)
//	{
//		int k = 0, m = 0, n = 0, z = 0;
//		bool flag = false;
//		char buffer[LT_MAXSIZE];
//		for (unsigned int i = 0; i < (unsigned int)ltable.size; i++)
//		{
//			if (ltable.table[i].lexema == LEX_LIBFUNC)
//			{
//				flag = true;
//				m = i;
//				k = 0;
//			}
//			if (flag)
//			{
//				while (ltable.table[i].lexema != LEX_RIGHTHESIS)
//				{
//					if (ltable.table[i].lexema == LEX_ID || ltable.table[i].lexema == LEX_LITERAL)
//					{
//						k++;
//					}
//					i++;
//					flag = false;
//				}
//				if (ltable.table[m].parm != k)
//				{
//					throw ERROR_THROW(701, ltable.table[i].sn, ltable.table[i].indxTI);
//				}
//			}
//			if (ltable.table[i].lexema == LEX_ID && ltable.table[i - 1].lexema == LEX_FUNCTION)
//			{
//				strcpy_s(buffer, ltable.table[i].buf);
//				while (ltable.table[i].lexema != LEX_RIGHTHESIS)
//				{
//					if (ltable.table[i].lexema == LEX_ID)
//					{
//						n++;
//					}
//					i++;
//				}
//			}
//			if (ltable.table[i].lexema == LEX_ID && strcmp(ltable.table[i].buf, buffer) == 0 && ltable.table[i + 1].lexema == LEX_LEFTHESIS)
//			{
//				int l = ltable.table[i].indxTI;
//				while (ltable.table[i].lexema != LEX_RIGHTHESIS)
//				{
//					if (ltable.table[i].lexema == LEX_ID || ltable.table[i].lexema == LEX_LITERAL)
//					{
//						z++;
//					}
//					i++;
//				}
//				if (z != n)
//				{
//					throw ERROR_THROW(701, ltable.table[i].sn, l);
//				}
//			}
//
//		}
//	}
//	void TypeofParameters(LT::LexTable& ltable, IT::IdTable& itable)
//	{
//		for (unsigned int i = 0; i < (unsigned int)ltable.size; i++)
//		{
//			if (ltable.table[i].lexema == LEX_LIBFUNC && ltable.table[i].parm == 1)
//			{
//				if (ltable.table[i + 2].lexema == LEX_ID)
//				{
//					for (unsigned int j = 0; j < (unsigned int)itable.size; j++)
//					{
//						if (strcmp(ltable.table[i + 2].buf, itable.table[j].id) == 0)
//						{
//							if (itable.table[j].iddatatype != IT::SYMB)
//							{
//								throw ERROR_THROW(700, ltable.table[i].sn, ltable.table[i].indxTI);
//							}
//						}
//					}
//				}
//				if (ltable.table[i + 2].lexema == LEX_LITERAL)
//				{
//					for (unsigned int j = 0; j < (unsigned int)itable.size; j++)
//					{
//						if (strcmp(ltable.table[i + 2].buf, itable.table[j].value.vstr->str) == 0)
//						{
//							if (itable.table[j].iddatatype != IT::SYMB)
//							{
//								throw ERROR_THROW(700, ltable.table[i].sn, ltable.table[i].indxTI);
//							}
//						}
//						if (strcmp(ltable.table[i + 2].buf, itable.table[j].value.vbool) == 0)
//						{
//							if (itable.table[j].iddatatype != IT::SYMB)
//							{
//								throw ERROR_THROW(700, ltable.table[i].sn, ltable.table[i].indxTI);
//							}
//						}
//					}
//				}
//			}
//			if (ltable.table[i].lexema == LEX_LIBFUNC && ltable.table[i].parm == 2)
//			{
//				while (ltable.table[i].lexema != LEX_RIGHTHESIS)
//				{
//					if (ltable.table[i].lexema == LEX_ID)
//					{
//						for (unsigned int j = 0; j < (unsigned int)itable.size; j++)
//						{
//							if (strcmp(ltable.table[i].buf, itable.table[j].id) == 0)
//							{
//								if (itable.table[j].iddatatype != IT::SYMB)
//								{
//									throw ERROR_THROW(700, ltable.table[i].sn, ltable.table[i].indxTI);
//								}
//							}
//						}
//					}
//					if (ltable.table[i].lexema == LEX_LITERAL)
//					{
//						for (unsigned int j = 0; j < (unsigned int)itable.size; j++)
//						{
//							if (strcmp(ltable.table[i].buf, itable.table[j].value.vstr->str) == 0)
//							{
//								if (itable.table[j].iddatatype != IT::SYMB)
//								{
//									throw ERROR_THROW(700, ltable.table[i].sn, ltable.table[i].indxTI);
//								}
//							}
//							if (strcmp(ltable.table[i].buf, itable.table[j].value.vbool) == 0)
//							{
//								if (itable.table[j].iddatatype != IT::SYMB)
//								{
//									throw ERROR_THROW(700, ltable.table[i].sn, ltable.table[i].indxTI);
//								}
//							}
//						}
//					}
//					i++;
//				}
//			}
//		}
//	}
//	void TypeofFuncParm(LT::LexTable& ltable, IT::IdTable& itable)
//	{
//		IT::IDDATATYPE data[LT_MAXSIZE];
//		IT::IDDATATYPE newdata[LT_MAXSIZE];
//		int m = 0, n = 0, z = 0, o = 0;
//		for (unsigned int i = 0; i < (unsigned int)ltable.size; i++)
//		{
//			if (ltable.table[i].lexema == LEX_ID && ltable.table[i - 1].lexema == LEX_FUNCTION)
//			{
//				while (ltable.table[i].lexema != LEX_RIGHTHESIS)
//				{
//					if (ltable.table[i].lexema == LEX_ID)
//					{
//						for (unsigned int j = 0; j < (unsigned int)itable.size; j++)
//						{
//							if (strcmp(ltable.table[i].buf, itable.table[j].id) == 0)
//							{
//								data[m] = itable.table[j].iddatatype;
//								m++;
//							}
//						}
//					}
//					i++;
//				}
//			}
//			if (ltable.table[i].lexema == LEX_ID && ltable.table[i + 1].lexema == LEX_LEFTHESIS)
//			{
//				o = ltable.table[i].indxTI;
//				for (unsigned int l = 0; l < (unsigned int)itable.size; l++)
//				{
//					if (strcmp(ltable.table[i].buf, itable.table[l].id) == 0)
//					{
//						while (ltable.table[i].lexema != LEX_RIGHTHESIS)
//						{
//							if (ltable.table[i].lexema == LEX_ID)
//							{
//								for (unsigned int q = 0; q < (unsigned int)itable.size; q++)
//								{
//									if (strcmp(ltable.table[i].buf, itable.table[q].id) == 0)
//									{
//										newdata[n] = itable.table[q].iddatatype;
//										n++;
//									}
//								}
//							}
//							if (ltable.table[i].lexema == LEX_LITERAL)
//							{
//								for (unsigned int y = 0; y < (unsigned int)itable.size; y++)
//								{
//									if (strcmp(ltable.table[i].buf, itable.table[y].value.vstr->str) == 0)
//									{
//										newdata[n] = itable.table[y].iddatatype;
//										n++;
//									}
//								}
//							}
//							i++;
//						}
//					}
//				}
//				while (z < n)
//				{
//					if (data[z] != newdata[z])
//					{
//						throw ERROR_THROW(700, ltable.table[i].sn, o);
//					}
//					z++;
//				}
//			}
//		}
//	}
//}
//
