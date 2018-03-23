#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>

class Player
{
public:
	 Player(std::string, int, int, double);
	 void setName(std::string);
	 void setHp(int);
	 void setAttack(int);
	 void setWalkSpeed(double);
	 std::string getName() const;
	 double getWalkspeed() const;
	 int getHp() const;
	 int getAttack() const;
	 void setSprite();
	 bool setTexture(std::string);
	 sf::Sprite& getPlayer();
	 void MoveLeft(double);
	 void MoveUp(double);
	 void MoveDown(double);
	 void MoveRight(double);
	 void Update(double);
	 bool isMovingLeft = false;
	 bool isMovingRight = false;
	 bool isMovingUp = false;
	 bool isMovingDown = false;
	 void Draw(sf::RenderWindow &);
	 sf::Sprite player;
	 sf::Texture texture;
private:
	std::string name;
	int hp = 0;
	int attack = 0;
	double walkspeed = 0;

};