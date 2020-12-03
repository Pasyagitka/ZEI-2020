#include "In.h"
#include "Error.h"
#include <fstream>

namespace In
{
	IN In::getin(wchar_t infile[])
	{
		IN newIn{ 0, 1 };

		newIn.text = new unsigned char[IN_MAX_LEN_TEXT];
		unsigned char* newInPointer = newIn.text;
		unsigned char symbol;
		bool quotesFlag = false;
		bool commentFlag = false;

		std::ifstream fileIn(infile);
		if (!fileIn.is_open()) throw ERROR_THROW(110);

		int currentColumn = 1;
		for (int i = 0; !fileIn.eof(); i++)
		{
			symbol = fileIn.get();
			if (fileIn.eof()) {
				*newInPointer = IN_CODE_ENDL;
				newInPointer++;
				*newInPointer = IN_CODE_N;
				break;
			}

			if (symbol == IN_CODE_COMMENT){
				commentFlag = true;
			}

			if (symbol == IN_CODE_ENDL) {
				if (commentFlag) commentFlag = false;
				newIn.lines++;
				currentColumn = 1;
			}
			else
				currentColumn++;

			switch (newIn.code[symbol])
			{
				case IN::F: {
					if (quotesFlag) {
						*newInPointer = symbol;
						newInPointer++;
						if (symbol != IN_CODE_ENDL) newIn.size++;
						break;
					}
					if (commentFlag) {
						newIn.ignor++;
						break;
					}
					throw ERROR_THROW_IN(111, newIn.lines, currentColumn);
				}
				case IN::I: {
					if (quotesFlag) {
						*newInPointer = symbol;
						newInPointer++;
						if (symbol != IN_CODE_ENDL) newIn.size++;
						break;
					};
					newIn.ignor++;
					break;
				}
				case IN::T: {
					if (commentFlag) {
						newIn.ignor++;
						break;
					}
					if (symbol == IN_CODE_QUOTE) quotesFlag = !quotesFlag;
					*newInPointer = symbol;
					newInPointer++;
					if (symbol != IN_CODE_ENDL) newIn.size++;
					break;
				}
				default: {
					if (commentFlag) {
						newIn.ignor++;
						break;
					}
					*newInPointer = newIn.code[symbol];
					newInPointer++;
					newIn.size++;
					break;
				}
			}
		}
		DeleteSpaces(newIn);
		fileIn.close();
		return newIn;
	}

	void DeleteSpaces(In::IN in) {
		bool quoteFlag = false;
		unsigned char* Pointer = in.text;
		for (int i = 0; in.text[i] != IN_CODE_N; i++)
		{
			if (in.text[i] == IN_CODE_QUOTE)
				quoteFlag = !quoteFlag;
			if (quoteFlag) {
				*Pointer = in.text[i];
				Pointer++;
				continue;
			}
			if (in.text[i] == IN_CODE_ENDL && in.text[i + 1] == IN_CODE_ENDL) {
				in.size--;  continue;
			}
			if (in.text[i] == IN_CODE_SPACE) {
				switch (in.text[i + 1]) {
					case IN_CODE_SPACE: {
						in.size--;  continue;
					}
					/*case IN_CODE_LEFTSHIFT: case IN_CODE_RIGHTSHIFT: */case IN_CODE_COMMA : case IN_CODE_LEFTBRACE: case IN_CODE_RIGHTBRACE: case IN_CODE_OPENBRACKET: case IN_CODE_CLOSEBRACKET: case IN_CODE_EUALITY: case IN_CODE_PLUS: case IN_CODE_MINUS: case IN_CODE_SLASH: case IN_CODE_STAR: {
						in.size--;  continue;
					}
				}
			}
			*Pointer = in.text[i]; Pointer++;
		}
		*Pointer = IN_CODE_N;
		Pointer = in.text;
		quoteFlag = false;
		for (int i = 0; in.text[i] != IN_CODE_N; i++)
		{
			if (in.text[i] == IN_CODE_QUOTE) quoteFlag = !quoteFlag;
			if (quoteFlag) {
				*Pointer = in.text[i]; 
				Pointer++; 
				continue;
			}
			if (in.text[i] == IN_CODE_SPACE) {
				switch (in.text[i - 1]) {
				/*case IN_CODE_LEFTSHIFT: case IN_CODE_RIGHTSHIFT:*/ case IN_CODE_COMMA: case IN_CODE_LEFTBRACE: case IN_CODE_RIGHTBRACE: case IN_CODE_OPENBRACKET:	case IN_CODE_CLOSEBRACKET: case IN_CODE_EUALITY: case IN_CODE_PLUS: case IN_CODE_MINUS: case IN_CODE_SLASH: case IN_CODE_STAR: {
							in.size--;  continue;
					 }
				}
			}
			*Pointer = in.text[i]; Pointer++;
		}
		*Pointer = IN_CODE_N;
	}
}