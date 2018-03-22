#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>


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
	~GameManager();

private:
	static sf::RenderWindow window(sf::VideoMode(int,int,std::string);
	int WINDOW_LENGTH = 0;
	int WINDOW_WIDTH = 0;
};