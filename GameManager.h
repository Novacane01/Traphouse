#pragma once
#include "SFML\Graphics.hpp"
#include "Player.h"
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>


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
	int WINDOW_LENGTH = 0;
	int WINDOW_WIDTH = 0;
};