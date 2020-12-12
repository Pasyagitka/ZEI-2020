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
            return Convert.ToSByte(symbolic);
        }
    }
}
