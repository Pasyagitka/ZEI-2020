using System;

namespace CourseProject
{
	class ZEI2020
	{
		static string foo(string str, sbyte k, sbyte m)
		{
			Console.WriteLine("symblen");
			sbyte p = (sbyte)(ZEI2020stdlib.StandartLibrary.Symblen(str));
			Console.WriteLine(str);
			return str;
		}
		static sbyte boo()
		{
			Console.WriteLine("boo function");
			return (sbyte)(29);
		}
		static void Main(string[] args)
		{
			sbyte x = -100;
			Console.WriteLine(x);
			sbyte y = 0;
			y = (sbyte)(x >> 2);
			y = (sbyte)(1 + ZEI2020stdlib.StandartLibrary.GenerTiny() + 2);
			Console.WriteLine(y);
			sbyte a = (sbyte)(x + y + 34);
			Console.WriteLine(a);
			string str = "sp ace";
			Console.WriteLine(str);
			string mystr = "а бв?гдежзикла	мопростуфхцч";
			string w = ZEI2020stdlib.StandartLibrary.GetTime(str);
			Console.WriteLine(w);
			bool mb = true;
			bool k = false;
			bool mbd = ZEI2020stdlib.StandartLibrary.GenerLogical();
			Console.WriteLine(mb);
			sbyte convert = (sbyte)(2 + ZEI2020stdlib.StandartLibrary.SymbToTiny(str) + 1);
			Console.WriteLine(convert);
			if(mb != false)
			{
				a = (sbyte)(19 + 1);
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
		
		}
			
	}
}