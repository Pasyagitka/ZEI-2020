using System;

namespace ZEI2020stdlib
{
    public class StandartLibrary
    {
        public static sbyte Symblen(string symbolic)
        {
            return (sbyte)symbolic.Length;
        }

        public static sbyte SymbToTiny(string symbolic)
        {
            for (int i = 0; i < symbolic.Length; i++)
            {
                if (!Char.IsDigit(symbolic[i]))
                    return -1;
            }
            return Convert.ToSByte(symbolic);
        }

        public static string GetTime(string symbolic)
        {
            return symbolic+DateTime.Now.ToShortTimeString();
        }

        public static sbyte GenerTiny()
        {
            var rnd = new Random();
            return (sbyte)rnd.Next(-129, 128);
        }

        public static bool GenerLogical()
        {
            var rnd = new Random();
            if (rnd.Next(0, 10) % 2 == 0)
                return false;
            else return true;
        }
    }
}
