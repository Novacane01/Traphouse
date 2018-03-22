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
	int getWindowWidth();
	sf::RenderWindow& getWindow();
	void setWindowLength(int);
	int getWindowLength();
	void Start();
	void Pause();
	void Quit();
	sf::RenderWindow window;
	~GameManager();
private:
	int WINDOW_LENGTH = 0;
	int WINDOW_WIDTH = 0;
};