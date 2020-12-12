using System;

namespace CourseProject
{
	class ZEI2020
	{
		static int foo(string str)
		{
			Console.WriteLine("symblen");
			int p  = ZEI2020stdlib.StandartLibrary.Symblen(str);
			return p ;
		}
		static void Main(string[] args)
		{
			int x  = 4;
			int y  = 22;
			y  = x  >> 2;
			int a  = x  + y  + 34;
			string str  = "sp ace";
			string mystr  = "а бв?гдежзикла	мопростуфхцч";
			bool mb  = false;
			int foolen  = foo(mystr);
			if(x  == y)
			{
				a  = 101;
				Console.WriteLine(a);
			}
			else
			{
				Console.WriteLine(foolen);
				Console.WriteLine(str);
			}
			int fef  = (x  * 12) * (a  / y);
			while(fef  < 5)
			{
				fef  = fef  + 1;
			}
		while (Console.ReadKey().Key != ConsoleKey.Enter) {}
		}
			
	}
}