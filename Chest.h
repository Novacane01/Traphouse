#pragma once
#include "GameManager.h"

class Chest
{
public:
	Chest();
	void Open(Player *);
	void fillChestWeapons();
	void fillChestPotions();
	std::vector<Weapon *>& getWeaponContents();
	std::vector<Potion *>& getPotionContents();
	~Chest();
	
private:
	std::vector<Weapon *> weaponContents;
	std::vector<Potion *> potionContents;
	sf::Sprite chest;
	sf::Texture texture;

	std::random_device rd;  //Will be used to obtain a seed for the random number engine
};