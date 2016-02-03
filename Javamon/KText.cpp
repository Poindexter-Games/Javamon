#include "KText.h"

//Description is located in the header file

KText::KText(Language lang)
{
	KText::lang = lang;

	sf::Image fontImg;
	fontImg.loadFromFile(VIDEO + "Basic_Latin.png");

	basic_latin = sf::Texture();
	basic_latin.loadFromImage(fontImg);

	if (KText::lang == Language::JA_JP)
	{
		sf::Image japaneseImg;
		japaneseImg.loadFromFile(VIDEO + "Japanese.png");

		japanese = sf::Texture();
		japanese.loadFromImage(japaneseImg);
	}
	latinWidths = new int[256];
	for (int i = 0; i < 256; i++) { latinWidths[i] = FONT_SIZE; }
	latinWidths[33] = 18; //!
	latinWidths[34] = 23; //"
	latinWidths[35] = 31; //#
	latinWidths[36] = 24; //$
	latinWidths[37] = 28; //%
	latinWidths[38] = 27; //&
	latinWidths[39] = 16; //'
	latinWidths[40] = 22; //(
	latinWidths[41] = 22; //)
	latinWidths[42] = 26; //*
	latinWidths[43] = 23; //+
	latinWidths[44] = 14; //,
	latinWidths[45] = 24; //-
	latinWidths[46] = 8; //.
	latinWidths[47] = 27; //slash
}

void KText::levelDialog(sf::RenderWindow & window, wstring dialog)
{
	sf::View view;
	view.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	window.setView(view);

	int row = 0;
	int x = 0;
	int charWidth = 0;

	for (int i = 0; i < dialog.length(); i++)
	{
		bool draw = false;
		wchar_t w = dialog[i];
		sf::Sprite c;
		charWidth = FONT_SIZE;
		if (w == '\n') //If w is the enter key
		{
			//Go down a row and adjust all the way to the left side of the dialog box, also display the enter key with a width of zero
			row++;
			x = 0;
			charWidth = 0;
		}
		if ((32 <= w && w <= 126) || (161 <= w && w <= 255)) //basic latin
		{
			draw = true;
			c = sf::Sprite(basic_latin, sf::IntRect((w % 16) * FONT_SIZE, ((w - (w % 16)) / 16) * FONT_SIZE, latinWidths[w], FONT_SIZE));
			charWidth = latinWidths[w];
		}
		else if (12288 <= w && w <= 12543) //1st japanese section of unicode stuff
		{
			draw = true;
			c = sf::Sprite(japanese, sf::IntRect((w % 16) * FONT_SIZE, (((w - (w % 16)) / 16)-768) * FONT_SIZE, FONT_SIZE, FONT_SIZE));
		}
		else if (65281 <= w && w <= 65376) //2nd part of japanese stuff in unicode
		{
			draw = true;
			c = sf::Sprite(japanese, sf::IntRect((w % 16) * FONT_SIZE, (((w - (w % 16)) / 16) - 4064) * FONT_SIZE, FONT_SIZE, FONT_SIZE));
		}
		else if (65377 <= w && w <= 65439) //2nd part of japanese stuff in unicode, but halfwidth stuff
		{
			draw = true;
			c = sf::Sprite(japanese, sf::IntRect((w % 16) * FONT_SIZE, (((w - (w % 16)) / 16) - 4064) * FONT_SIZE, FONT_SIZE * .5, FONT_SIZE));
			charWidth = .5 * FONT_SIZE;
		}
		else if (65440 <= w && w <= 65519) //2nd part of japanese stuff in unicode, but back to full width characters
		{
			draw = true;
			c = sf::Sprite(japanese, sf::IntRect((w % 16) * FONT_SIZE, (((w - (w % 16)) / 16) - 4064) * FONT_SIZE, FONT_SIZE, FONT_SIZE));
		}
		if (draw)
		{
			c.setPosition(sf::Vector2f(20 + x, DIALOG_BOX_LOW + 20 + (row * FONT_SIZE)));
			x += charWidth;
			//Set the x value of the next character to += the width of the last character
		}
		window.draw(c);
	}
}