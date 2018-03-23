#pragma once
#include "SFML\Graphics.hpp"
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
	void Pause();
	void Quit();
	~GameManager();
private:
	int WINDOW_LENGTH = 0;
	int WINDOW_WIDTH = 0;
};