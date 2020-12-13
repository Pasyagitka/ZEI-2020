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
    }
}
