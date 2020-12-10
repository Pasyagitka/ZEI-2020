#pragma once
#include "Log.h"
#include "LT.h"
#include "IT.h"
#define MINTINY -128
#define MAXTINY 127
#define SYMBMAXLEN 127

#define EMPTY_LITERAL " "
#define POSTFIXGLOBAL "GLB"
#define EMPTYSYMBLITERAL "\"\""

#define S		  inText[i] == LEX_ASSIGN	|| inText[i] == LEX_EXCLAMATION || inText[i] == LEX_LEFTHESIS || inText[i] == LEX_RIGHTHESIS || inText[i] == LEX_RIGHTBRACE || inText[i] == LEX_LEFTBRACE
#define SNEXT	  inText[i + 1] == LEX_ASSIGN || inText[i + 1] == LEX_EXCLAMATION || inText[i + 1] == LEX_LEFTHESIS || inText[i + 1] == LEX_RIGHTHESIS || inText[i + 1] == LEX_RIGHTBRACE || inText[i + 1] == LEX_LEFTBRACE

#define ARIFM	  inText[i] == LEX_MINUS || inText[i] == LEX_PLUS || inText[i] == LEX_STAR || inText[i] == LEX_DIVISION 
#define ARIFMNEXT inText[i+1] == LEX_MINUS || inText[i+1] == LEX_PLUS || inText[i+1] == LEX_STAR || inText[i+1] == LEX_DIVISION 

#define LOGIC	  inText[i] == LEX_EQUALITY || inText[i] == LEX_INEQUALITY || inText[i] == LEX_MORE || inText[i] == LEX_LESS || inText[i] == LEX_RIGHTSHIFT || inText[i] == LEX_LEFTSHIFT 
#define LOGICNEXT inText[i+1] == LEX_EQUALITY || inText[i + 1] == LEX_INEQUALITY  || inText[i + 1] == LEX_MORE || inText[i + 1] == LEX_LESS  || inText[i+1] == LEX_RIGHTSHIFT || inText[i+1] == LEX_LEFTSHIFT


namespace Lan {
	void Analysis(char inText[], Log::LOG, LT::LexTable& lextable, IT::IdTable& idtable);
}