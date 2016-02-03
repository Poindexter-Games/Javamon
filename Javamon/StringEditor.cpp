#include "StringEditor.h"

//DESCRIPTONS ARE IN THE HEADER FILE

int StringEditor::getBreakPosition(wstring str, int endOfSegmentNumber)
{
	if (endOfSegmentNumber == 0) return -1;
	int s = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == L',' || str[i] == L';')
		{
			s++;
			if (s == endOfSegmentNumber)
			{
				return i;
			}
		}
	}
	//This means that the segment number was invalid
	return -2;
}

int StringEditor::getNumberOfSegments(wstring str)
{
	if (str.length() == 0)
		return 0;


	int num = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == L',')
		{
			num++;
		}
		else if (str[i] == L';')
		{
			num++;
			return num;
		}
	}
	/*
	If the program gets this far into the function, we know the user did not end a line with a semi colon
	It would be the same difficulty to program the game to not use semicolons as it would be to use semi colons,
	but either way, we must be consistent, and I have chosen to use semi colons for now as it justs looks interesting :)
	-Karl Piepho
	*/
	return -1;
}

wstring* StringEditor::breakApart(wstring str)
{
	int s = getNumberOfSegments(str);
	wstring* strs = new wstring[s];
	for (int i = 0; i < s; i++)
	{
		int pos0 = getBreakPosition(str, i);
		int pos1 = getBreakPosition(str, i + 1);
		strs[i] = str.substr(pos0 + 1, (pos1 - 1) - (pos0));
	}
	return strs;
}

void StringEditor::echo(wstring str)
{
	wcout << str << endl;
}
void StringEditor::echo(int i)
{
	wcout << i << endl;
}
void StringEditor::echo(wstring str, int i)
{
	wcout << str << L" " << i << endl;
}
void StringEditor::echo(int i, wstring str)
{
	wcout << i << L" " << str << endl;
}