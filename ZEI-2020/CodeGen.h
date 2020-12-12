#pragma once
#include "LT.h"
#include "IT.h"
#include "Out.h"
//C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\MSBuild\Current\Bin\Roslyn
#define START  *(out.stream) << "using System;\n\nnamespace CourseProject\n{\n\tclass ZEI2020\n\t{\n\t\t"; 

#define END    *(out.stream)  << std::endl << "\t" << "}" << std::endl  << "}";

namespace CodeGeneration
{
	void StartGeneration(LT::LexTable & ltable, IT::IdTable& itable, Out::OUT out);
}
