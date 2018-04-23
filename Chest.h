#pragma once
#include <random>
#include "Player.h"
class Chest
{
public:
	Chest();
	void Open(Player *);
	void fillChestWeapons();
	void fillChestPotions();
	std::vector<Weapon *>& getWeaponContents();
	std::vector<Potion *>& getPotionContents();
    sf::Sprite getChestSprite();
    void setData(float,float);
    bool getIsOpen();

	~Chest();


private:
	std::vector<Weapon *> weaponContents;
	std::vector<Potion *> potionContents;
	sf::Sprite chest;
	sf::Texture closedTexture;
	sf::Texture openTexture;

	bool opened = false;

	std::random_device rd;  //Will be used to obtain a seed for the random number engine
};