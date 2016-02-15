#pragma once
#include <string>
#include <cstdint>
#include <vector>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "MovableEntity.h"

#include "Language.h"

#include "Variables.h"
#include "Controls.h"
#include "Monster.h"

using namespace std;

class Player: public MovableEntity
{
public:
	Player(); //

	Language lang;

	enum Mode{ NORMAL = 0, DIALOG = 1 };
	Mode mode;

	void render(sf::RenderWindow & w);

	wstring getName() { return name; }
	bool isMale() { return sex == 0; }
	bool isFemale() { return sex == 1; }
	void setGender(Gender sex) { Player::sex = sex; }
	Gender getGender() { return sex; };

	void setDirection(Direction direction) { Player::direction = direction; }
	void setZDirection(int zd) { zdirection = zd; }
	void setSteepness(float s) { steepness = s; }

	void place(int, int, Direction);
	void place(int x, int y, Direction d, int zdir, float);

	void allowMovement() { movementAllowed = true; }
	void inhibitMovement() { movementAllowed = false; }
	bool isAllowedToMove() { return movementAllowed; }

	Direction getDirection() { return direction; }
	int getZDirection() { return zdirection; }
	float getSteepness() { return steepness; }

	wstring getDialog() { return dialog; }
	wstring getPostBattleQuote() { return postBattleQuote; }
	wstring getAnteBattleQuote() { return anteBattleQuote; }

	void setDialog(wstring dialog) { Player::dialog = dialog; }

	bool isVisible() { return visible; }
	void setVisible() { visible = true; }
	void setInvisible() { visible = false; }

	int getAnimationFrame() { return animationFrame; }
	void setAnimationFrame(int f) { animationFrame = f; }

	bool getWantsToBattle() { return wantsToBattle; }
	void setWantsToBattle(bool b) { wantsToBattle = b; }
private:
	vector<sf::Texture> textures;

	wstring name;
	Gender sex;
	
	Direction direction;
	int zdirection; //this is for the going up stairs or down stairs animation, 1 is up, -1 is down
	float steepness; //this is for whether the player is traversing steep (.5) or gradual hills (.25)
	bool movementAllowed;

	wstring dialog; //Dialogue
	wstring anteBattleQuote; //Quote before the battle
	wstring postBattleQuote; //Quote after the battle

	bool wantsToBattle;
	Monster* monsters; //Inventory of monsters
	int numMonsters; //Number of monsters in inventory. This must be between 0 and 6 (inclusive).

	bool visible; //If true, shows NPC and gives them a hitbox
	int animationFrame;
};