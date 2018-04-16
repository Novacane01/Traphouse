#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Floor.h"
#include "Enemy.h"
#include <iostream>
#include <string>
#include <vector>

extern unsigned WINDOW_LENGTH, WINDOW_WIDTH;

class GameManager
{
public:
	GameManager(int, int);
	void setWindowLength(int);
	void setWindowWidth(int);
	static unsigned getWindowWidth();
	static unsigned getWindowLength();
	void Start();
	Player* createPlayer(sf::RenderWindow &);
	void GameOver();
	void Pause(sf::RenderWindow &);
	void Quit(sf::RenderWindow &);
	~GameManager();
private:
	sf::Font font;
	sf::View view;
};
