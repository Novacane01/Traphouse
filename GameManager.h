#pragma once
#include "SFML/Graphics.hpp"

#include "Enemy.h"
#include "LinkedMap.h"
#include "Player.h"
#include "UI/StartScreen.h"
#include "UI/CreatePlayerScreen.h"
#include "UI/PauseScreen.h"
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
	bool Start();
	void spawnEnemies(LinkedMap*);
	void restrictMovement();
	bool GameOver(float);
	void DisplayMap(Player *, LinkedMap*);
	void levelUp(LinkedMap* lmap);
	void changeView(LinkedMap*, float);

	
private:
	sf::Font font;
	sf::View view;
	sf::RenderWindow window;
	bool paused;
	bool inFunction;

	StartScreen startScreen;
	CreatePlayerScreen playerCreationScreen;
	PauseScreen pauseScreen;

	Player *player = nullptr;
	int level;
	sf::View roomView;
	sf::Clock displayChestTime;
	bool chestIsLookedAt = false;
	bool chestIsLookedAt2 = false;
	bool isDemonSpawned = false;
};

