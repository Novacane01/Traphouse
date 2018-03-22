#include "Player.h"
#include "SFML/Graphics.hpp"
#include <math.h>
Player::Player(std::string name, int hp, int attack, double walkspeed){
    sf::CircleShape tempshape(25);
    shape = tempshape;
    shape.setPosition(100,100);
    setName(name);
	setHp(hp);
	setAttack(attack);
	setWalkSpeed(walkspeed);
}

void Player::getMovement() {
    int speed = 2;
    double diagonalSpeed = (speed * pow(2,.5))/2;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        shape.move(diagonalSpeed, -diagonalSpeed);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        shape.move(-diagonalSpeed,-diagonalSpeed);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        shape.move(-diagonalSpeed,diagonalSpeed);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        shape.move(diagonalSpeed, diagonalSpeed);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){

        shape.move(-speed, 0);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){

        shape.move(speed, 0);
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){

        shape.move(0,-speed);
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        shape.move(0,speed);

    }

}

void Player::setName(std::string value) {
	name = value;
}

void Player::setHp(int value){
	hp = value;
}

int Player::getHp() const{
	return hp;
}

void Player::setWalkSpeed(double value){
	walkspeed = value;
}

double Player::getWalkspeed() const {
	return walkspeed;
}

void Player::setAttack(int value){
	attack = value;
}

int Player::getAttack() const{
	return attack;
}

void Player::setSprite(sf::Texture &texture){
	player.setTexture(texture);
}

sf::Sprite Player::getPlayer() const{
	return player;
}

bool Player::setTexture(std::string texturePath){
	if (!texture.loadFromFile(texturePath)) {
		return false;
	}
	return true;
}

void Update(double dt) {

}