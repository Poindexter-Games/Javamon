#include "Tile.h"

using namespace std;

Tile::Tile() :Entity(0, 0)
{
	Tile::imgnum = 0;
	Tile::z = 0;
	Tile::type = 0;
}
Tile::Tile(int imgnum, int z, int type): Entity(0, 0)
{
	Tile::imgnum = imgnum;
	Tile::z = z;
	Tile::type = type;
}
Tile::Tile(wstring w) : Entity(0, 0)
{
	int openParenthesis = StringEditor::findCharacter(w, L'(', 1);
	int comma_1 = StringEditor::findCharacter(w, L',', 1);
	int comma_2 = StringEditor::findCharacter(w, L',', 2);
	int closeParenthesis = StringEditor::findCharacter(w, L')', 1);

	try
	{
		wstring sZ = StringEditor::substring(w, openParenthesis + 1, comma_1);
		wstring sN = StringEditor::substring(w, comma_1 + 1, comma_2);
		wstring sT = StringEditor::substring(w, comma_2 + 1, closeParenthesis);

		Tile::imgnum = stoi(sN);
		Tile::z = stoi(sZ);
		Tile::type = stoi(sT);
	}
	catch (exception e)
	{
		StringEditor::echo(sf::String(e.what()));
	}
}