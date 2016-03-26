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