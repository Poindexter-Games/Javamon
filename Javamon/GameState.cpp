#include "GameState.h"

/*
For level changes, the level is going to call up to the GameState, which will
pass on the call to main to change the gamestate to loading. Then the main
will change the gamestate back to Level with the new level constructed and
quit rendering the load screen

With Java, I used listeners, I don't know if C++ programmers use those

-Karl
*/

using namespace std;

GameState::GameState(string state)
{
	if(state.compare("level") == 1)
	{
		l = Level();
	}
	else
	{
		//Oops! You loaded an undefined state!
	}
}

void GameState::update()
{

}

void GameState::render(sf::RenderWindow& window)
{
	l.render(window);
}