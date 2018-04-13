#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "miniMap.h"
#include "Enemy.h"
#include <iostream>
#include <string>
#include <vector>



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
	void Pause();
	void Quit();
	~GameManager();
private:
	unsigned WINDOW_LENGTH = 0;
	unsigned WINDOW_WIDTH = 0;
};
