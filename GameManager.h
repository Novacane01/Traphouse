#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Map.h"
#include "Enemy.h"
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
	void GameOver();
	void Pause(sf::RenderWindow &);
	void Quit(sf::RenderWindow &);
	~GameManager();
private:
	unsigned WINDOW_LENGTH = 0;
	unsigned WINDOW_WIDTH = 0;
	sf::Font font;
	sf::View view;
};
