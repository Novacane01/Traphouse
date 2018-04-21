#pragma once
#include "SFML/Graphics.hpp"

#include "Enemy.h"
#include "LinkedMap.h"
#include "Player.h"
#include <random>
#include <iostream>
#include <string>
#include <vector>


extern unsigned WINDOW_LENGTH, WINDOW_WIDTH;

class GameManager
{
public:
	GameManager(int, int);
	void setWindowWidth(int);
	void setWindowLength(int);
	void Start();
	void LoadingScreen(sf::RenderWindow &);
	Player* createPlayer(sf::RenderWindow &);
	void spawnEnemies(LinkedMap*);

	void GameOver(sf::RenderWindow &);
	void Pause(sf::RenderWindow &);
	void DisplayMap(sf::RenderWindow &, Player *, LinkedMap*);
    void Quit(sf::RenderWindow &);

private:
	sf::Font font;
	sf::View view;

	Player *player;

	Weapon defaultKnife;
	Weapon defaultPistol;
	Weapon heavyPistol;
	Weapon boltSniper;
	Weapon semiAuto;
	Weapon shotgun;
	Weapon assaultRifle;
	Weapon minigun;
	Weapon semiSniper;
	Weapon submachine;
};
