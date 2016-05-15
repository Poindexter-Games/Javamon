#pragma once
static int rollOverAdd(int n, int a, int b, int i = 1)
{
	if (n + i > b)
	{
		return a + (b - n);
	}
	else if (n + i < a)
	{
		return b - (n - a);
	}
	else
	{
		return n + i;
	}
}
static bool contains(int x, int y, sf::IntRect rect)
{
	return rect.left <= x && x <= rect.left + rect.width && rect.top <= y && y <= rect.top + rect.height;
}