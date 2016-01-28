#include "KText.h"

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
}

void KText::levelDialog(sf::RenderWindow & window, wstring dialog)
{
	sf::View view;
	view.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	window.setView(view);

	int row = 0;
	int x = 0;

	for (int i = 0; i < dialog.length(); i++)
	{
		bool draw = false;
		wchar_t w = dialog[i];
		sf::Sprite c;
		if (w == '\n') //enter
		{
			row++;
			x = 0;
		}
		if ((32 <= w && w <= 126) || (161 <= w && w <= 255)) //basic latin
		{
			draw = true;
			c = sf::Sprite(basic_latin, sf::IntRect((w % 16) * FONT_SIZE, ((w - (w % 16)) / 16) * FONT_SIZE, FONT_SIZE, FONT_SIZE));
		}
		else if (12288 <= w && w <= 12543) //1st japanese section of unicode stuff
		{
			draw = true;
			c = sf::Sprite(japanese, sf::IntRect((w % 16) * FONT_SIZE, (((w - (w % 16)) / 16)-768) * FONT_SIZE, FONT_SIZE, FONT_SIZE));
		}
		else if (65281 <= w && w <= 65518) //2nd part of japanese stuff in unicode
		{
			draw = true;
			c = sf::Sprite(japanese, sf::IntRect((w % 16) * FONT_SIZE, (((w - (w % 16)) / 16) - 4064) * FONT_SIZE, FONT_SIZE, FONT_SIZE));
		}
		if (draw)
		{
			c.setPosition(sf::Vector2f(20 + x, DIALOG_BOX_LOW + 20 + (row * FONT_SIZE)));
			x += FONT_SIZE; //THIS WILL BE EDITED TO ALLOW FOR CHARACTERS OF DIFFERENT WIDTHS
		}
		window.draw(c);
	}
}