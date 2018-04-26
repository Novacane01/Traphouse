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
    sf::Text getPotionAcquired();
    sf::Text getWeaponAcquired();
    void setUI(Player*,sf::RenderWindow&);
	sf::Sound sound;
	~Chest();


private:
	sf::SoundBuffer openSound;
	std::vector<Weapon *> weaponContents;
	std::vector<Potion *> potionContents;
	sf::Sprite chest;
	sf::Texture closedTexture;
	sf::Texture openTexture;
	sf::Text weaponAcquired;
	sf::Text potionAcquired;
	sf::Font font;
	bool opened = false;

	std::random_device rd;  //Will be used to obtain a seed for the random number engine
};