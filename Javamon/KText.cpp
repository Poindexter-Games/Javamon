﻿#include "KText.h"

//Description is located in the header file

KText::KText()
{
	sf::Image fontImg;
	fontImg.loadFromFile(VIDEO + L"Basic_Latin.png");

	basic_latin = sf::Texture();
	basic_latin.loadFromImage(fontImg);

	latinWidths = new int[256];
	for (int i = 0; i < 256; i++) { latinWidths[i] = FONT_SIZE; }
}

KText::KText(Language lang)
{
	KText::lang = lang;

	sf::Image fontImg;
	fontImg.loadFromFile(VIDEO + L"Basic_Latin.png");

	basic_latin = sf::Texture();
	basic_latin.loadFromImage(fontImg);

	latinWidths = new int[256];
	for (int i = 0; i < 256; i++) { latinWidths[i] = FONT_SIZE; }

	KFile file(VIDEO + L"Latin_Widths.txt");
	bool comment = false;
	wstring w;
	for (bool b = true; b; )
	{
		file.readLine(w);

		if (w.length() == 0) continue;
		if (StringEditor::equals(w, L"endFile;")) {
			break;
		}
		else
		{
			int equals = StringEditor::findCharacter(w, L'=', 1);

			latinWidths[stoi(StringEditor::substring(w, 0, equals))] = stoi(StringEditor::substring(w, equals + 1, w.length()));
		}
	}
	file.close();

	//JAPANESE

	if (lang.getLanguageCode().toWideString().compare(L"ja-JP") == 0)
	{
		sf::Image japaneseImg;
		japaneseImg.loadFromFile(VIDEO + L"Japanese.png");

		japanese = sf::Texture();
		japanese.loadFromImage(japaneseImg);

		for (int i = 0; i < 256; i++) { latinWidths[i] = FONT_SIZE / 2; }
	}
}

void KText::simpleMessage(sf::RenderWindow & window, wstring dialog)
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
		else if (w == 8230) //...
		{
			draw = true;
			//This character isn't actually in the Japanese section of unicode, but I decided to give a spot in the Japanese spritesheet
			//because English users won't ever be typing in a single character form of the ellipses, also putting a character in a blank
			//spot goes againsts the unicode policy, but hey, it keeps me from having to create a hundred new characters
			c = sf::Sprite(japanese, sf::IntRect(0, 16 * FONT_SIZE, FONT_SIZE, FONT_SIZE));
		}
		else if (12288 <= w && w <= 12543) //1st japanese section of unicode stuff
		{
			draw = true;
			c = sf::Sprite(japanese, sf::IntRect((w % 16) * FONT_SIZE, (((w - (w % 16)) / 16) - 768) * FONT_SIZE, FONT_SIZE, FONT_SIZE));
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
			c.setPosition(sf::Vector2f(x,row * FONT_SIZE));
			x += charWidth;
			//Set the x value of the next character to += the width of the last character
		}
		window.draw(c);
	}
}

void KText::coordinates(sf::RenderWindow & window, int px, int py)
{
	sf::View view;
	view.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	window.setView(view);

	int row = 0;
	int x = 0;
	int charWidth = 0;

	sf::String dialog(to_wstring(px)+L"\n"+to_wstring(py));

	for (int i = 0; i < dialog.toWideString().length(); i++)
	{
		bool draw = false;
		wchar_t w = dialog[i];
		sf::Sprite c;
		charWidth = 14;
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
		if (draw)
		{
			c.setPosition(sf::Vector2f(x, row * FONT_SIZE));
			x += charWidth + 4;;
			//Set the x value of the next character to += the width of the last character
		}
		window.draw(c);
	}
}

void KText::drawText(sf::RenderWindow & window, int x, int y, sf::String str, sf::Color colour = sf::Color::Black)
{
	sf::View view;
	view.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	window.setView(view);

	int row = 0;
	int col = 0;
	int charWidth = FONT_SIZE;

	for (int i = 0; i < str.toWideString().length(); i++)
	{
		bool draw = false;
		wchar_t w = str[i];
		sf::Sprite c;
		charWidth = FONT_SIZE;
		if (w != str.toWideString().size() - 1 && w == L'\\' && str[i + 1] == L'n') //If w is the enter key
		{
			//Go down a row and adjust all the way to the left side of the dialog box, also display the enter key with a width of zero
			row++;
			col = 0;
			charWidth = 0;
			i++;
			continue;
		}
		else if (w != str.toWideString().size() - 1 && w == L'\\' && str[i + 1] == L't') //If w is the tab key
		{
			col += charWidth * 2;
			i++;
			continue;
		}
		else if ((32 <= w && w <= 126) || (161 <= w && w <= 255)) //basic latin
		{
			draw = true;
			c = sf::Sprite(basic_latin, sf::IntRect((w % 16) * FONT_SIZE, ((w - (w % 16)) / 16) * FONT_SIZE, latinWidths[w], FONT_SIZE));
			charWidth = latinWidths[w];
			col += 4; //This is for space between each character, Japanese doesn't need this
		}
		else if (w == 8230) //...
		{
			draw = true;
			//This character isn't actually in the Japanese section of unicode, but I decided to give a spot in the Japanese spritesheet
			//because English users won't ever be typing in the single character form of the ellipses, also putting a character in a blank
			//spot goes againsts the unicode policy, but hey, it keeps me from having to create a hundred new characters
			c = sf::Sprite(japanese, sf::IntRect(0, 16 * FONT_SIZE, FONT_SIZE, FONT_SIZE));
		}
		else if (12288 <= w && w <= 12543) //1st japanese section of unicode stuff
		{
			draw = true;
			c = sf::Sprite(japanese, sf::IntRect((w % 16) * FONT_SIZE, (((w - (w % 16)) / 16) - 768) * FONT_SIZE, FONT_SIZE, FONT_SIZE));
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
			charWidth = .5 * FONT_SIZE;\

		}
		else if (65440 <= w && w <= 65519) //2nd part of japanese stuff in unicode, but back to full width characters
		{
			draw = true;
			c = sf::Sprite(japanese, sf::IntRect((w % 16) * FONT_SIZE, (((w - (w % 16)) / 16) - 4064) * FONT_SIZE, FONT_SIZE, FONT_SIZE));
		}
		if (draw)
		{
			c.setPosition(sf::Vector2f(x + col, y + (row * FONT_SIZE)));
			col += charWidth;
			//Set the x value of the next character to += the width of the last character
		}
		c.setColor(colour);
		window.draw(c);
	}
}