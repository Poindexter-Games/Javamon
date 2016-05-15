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

#include "InGameMenu.h"

using namespace std;

class Player: public MovableEntity
{
public:
	Player();

	enum RequestMode {NONE, NEW_LEVEL, QUIT, LEVEL, BATTLE};
	enum Mode{ NORMAL = 0, DIALOG = 1, MENU = 2 };

	/*
	METHODS TO BE ACCESSED
	*/

	void render(sf::RenderWindow & w);

	void updateMenu(Controls & c);
	void renderMenu(sf::RenderWindow & w, KText&);

	/*
	GETTER METHODS
	*/

	InGameMenu getMenu() const {return menu;}
	sf::String getLanguageCode() { return lang.getLanguageCode(); }
	Mode getMode() const { return mode; }
	wstring getLevelName() const { return levelName; }

	//Movement Stuff

	Direction getDirection() const { return direction; }
	int getZDirection() const { return zdirection; }
	float getSteepness() const { return steepness; }

	bool isAllowedToMove() const { return movementAllowed; }
	bool isVisible() const { return visible; }

	int getAnimationFrame() const { return animationFrame; }

	//RPG Stuff

	sf::String getName() const { return name; }
	bool isMale()  const { return sex == 0; }
	bool isFemale() const { return sex == 1; }
	Sex getSex() const { return sex; };
	int getCash() const { return cash; }
	bool hasEnoughCash(int cash) const { return Player::cash >= cash; }

	//Dialogue Stuff

	sf::String getDialog() const { return dialog; }
	sf::String getPostBattleQuote() const { return postBattleQuote; }
	sf::String getAnteBattleQuote() const { return anteBattleQuote; }
	int getNPCDialogNumber() const { return npcDialogNumber; }

	//Battle Stuff

	bool getWantsToBattle() const { return wantsToBattle; }
	BattleType getBattleType() const { return preferredBattleType; }
	SwitchType getSwitchType() const { return preferredSwitchType; }
	
	/*
	SETTER METHODS
	*/

	void setLanguage(Language l) { lang = l; menu.setLanguage(l); }
	void setMode(Mode m) { mode = m; }
	void setLevelName(wstring s) { levelName = s; }

	//Movement Stuff

	void place(int, int, Direction);
	void place(int x, int y, Direction d, int zdir, float);

	void setDirection(Direction direction) { Player::direction = direction; }
	void setZDirection(int zd) { zdirection = zd; }
	void setSteepness(float s) { steepness = s; }

	void allowMovement() { movementAllowed = true; }
	void inhibitMovement() { movementAllowed = false; }

	void setVisible() { visible = true; }
	void setInvisible() { visible = false; }

	void setAnimationFrame(int f) { animationFrame = f; }

	//RPG Stuff

	void setSex(Sex sex) { Player::sex = sex; }
	void setCash(int cash) { Player::cash = cash; }
	void addCash(int cash) { Player::cash += cash; }
	void removeCash(int cash) { Player::cash -= cash; }

	//Dialogue Stuff
	
	void setNPCDialogNumber(int n) { npcDialogNumber = n; }
	void setDialiog(sf::String dialog) { Player::dialog = dialog; }

	//Battle Stuff

	void setWantsToBattle(bool b) { wantsToBattle = b; }
private:
	RequestMode m;
	wstring levelName;

	vector<sf::Texture> textures;	//Number of textures (should be 16)
	vector<Monster> party;			//Party (your monsters)

	sf::String name;		//Do I need to explain?
	Sex sex;				//Okay, you need some help
	int cash;

	Mode mode;				//Player mode

	Language lang;
	InGameMenu menu;

	BattleType preferredBattleType;
	SwitchType preferredSwitchType;
	
	Direction direction;
	int zdirection;			//this is for the going up stairs or down stairs animation, 1 is up, -1 is down
	float steepness;		//this is for whether the player is traversing steep (.5) or gradual hills (.25)
	bool movementAllowed;

	sf::String dialog;			//Dialogue
	sf::String anteBattleQuote;	//Quote before the battle	This will probably be for user vs user battles
	sf::String postBattleQuote;	//Quote after the battle	This will probably be for user vs user battles
	int npcDialogNumber;		//Stores the value for which npc the player is talking to, this may be more appropriately saved in the Level class, but it's fine for now

	bool wantsToBattle;			//Bool for online which states if the player wants to participate in battles

	bool visible;				//If true, shows the player and gives them a hitbox
	int animationFrame;			//Frame number of the player
};