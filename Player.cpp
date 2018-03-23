#include "Player.h"

Player::Player(std::string name, int hp, int attack, double walkspeed){
	setName(name);
	setHp(hp);
	setAttack(attack);
	setWalkSpeed(walkspeed);
    weaponInventory.push_back(Pickup::defaultPistol);
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

void Player::setSprite(){
	player.setTexture(texture);
}

sf::Sprite& Player::getPlayer(){
	return player;
}

bool Player::setTexture(std::string texturePath){
	if (!texture.loadFromFile(texturePath)) {
		return false;
	}
	std::cout << "Loaded" << std::endl;
	return true;
}

void Player::MoveLeft(double dt) {
	player.setPosition(player.getPosition().x - 1, player.getPosition().y);
}

void Player::MoveUp(double dt) {
	player.setPosition(player.getPosition().x, player.getPosition().y-1);
}

void Player::MoveDown(double dt) {
	player.setPosition(player.getPosition().x, player.getPosition().y+1);
}

void Player::MoveRight(double dt) {
	player.setPosition(player.getPosition().x + 1, player.getPosition().y);
}

void Player::Update(double dt) {
	if (isMovingUp) {
		MoveUp(dt);
	}
	if (isMovingDown) {
		MoveDown(dt);
	}
	if (isMovingRight) {
		MoveRight(dt);
	}
	if (isMovingLeft) {
		MoveLeft(dt);
	}
}
