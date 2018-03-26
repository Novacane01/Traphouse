#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Map.h"
#include <iostream>
#include <string>
#include <vector>



class GameManager
{
public:
	GameManager(int, int);
	void setWindowWidth(int);
	void setWindowLength(int);
	void Start();
	Player* createPlayer(sf::RenderWindow &);
	void Pause();
	void Quit();
	~GameManager();
private:
	unsigned WINDOW_LENGTH = 0;
	unsigned WINDOW_WIDTH = 0;
};
