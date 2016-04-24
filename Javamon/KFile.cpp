#include "KFile.h"

KFile::KFile(sf::String filepath)
{
	std::locale locale("");											//This will read the user's locale, so the program can determine string encoding since wifstream uses a regular string to load a file
	std::string path = sf::String(filepath).toAnsiString(locale);	//This translates sf::String to std::string so that std::wfstream can be opened
	
	StringEditor::echo(sf::String(path).toWideString());

	file.open(path);

	//This is to load the file as a UTF-8 format
	file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>()));
}

void KFile::readLine(wstring & w)
{
	std::getline(file, w);
}

void KFile::close()
{
	file.close();
}