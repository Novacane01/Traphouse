#include "stdafx.h"
#include "Player.h"

Player::Player(std::string name, int hp, int attack, double walkspeed){
	setName(name);
	setHp(hp);
	setAttack(attack);
	setWalkSpeed(walkspeed);
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