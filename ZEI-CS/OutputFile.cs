using System;

namespace CourseProject
{
	class ZEI2020
	{
		static string foo(string str)
		{
			Console.WriteLine("symblen");
			sbyte p = ZEI2020stdlib.StandartLibrary.Symblen(str);
			Console.WriteLine(str);
			return str;
		}
		static void Main(string[] args)
		{
			sbyte x = -100;
			Console.WriteLine(x);
			sbyte y = 31;
			Console.WriteLine(y);
			y = (sbyte)(x >> 2);
			Console.WriteLine(y);
			sbyte a = (sbyte)(x + y + 34);
			Console.WriteLine(a);
			string str = "sp ace";
			Console.WriteLine(str);
			string mystr = "� ��?���������	������������";
			bool mb = true;
			Console.WriteLine(mb);
			Console.WriteLine("convert to tiny mystr");
			sbyte convert = ZEI2020stdlib.StandartLibrary.SymbToTiny(mystr);
			Console.WriteLine(convert);
			sbyte converttwo = ZEI2020stdlib.StandartLibrary.SymbToTiny("124");
			Console.WriteLine(converttwo);
			if(mb != false)
			{
				a = 101;
				a = (sbyte)(101 + 1);
				Console.WriteLine(a);
			}
			else
			{
				Console.WriteLine(str);
			}
			sbyte fef = (sbyte)((x - 12) / (a + y));
			while(fef > 5)
			{
				fef = (sbyte)(fef + 1);
			}
			Console.WriteLine(fef);
		while (Console.ReadKey().Key != ConsoleKey.Enter) {}
		}
			
	}
}