#include "stdafx.h"
#include "Player.h"
#include "Pickup.h"

Player::Player(std::string name, int hp, double walkspeed){
	setName(name);
	setHp(hp);
	setWalkSpeed(walkspeed);
	weaponInventory.push_back(pickups.defaultKnife);
	std::cout << "\'Knife\' added to inventory" << std::endl;
	weaponInventory.push_back(pickups.defaultPistol);
	std::cout << "\'Pistol\' added to inventory" << std::endl;
}

//Sets player name
void Player::setName(std::string value) {
	name = value;
}

//Sets player HP
void Player::setHp(int value){
	hp = value;
}

//Returns player HP
int Player::getHp() const{
	return hp;
}

//Sets player walkspeed
void Player::setWalkSpeed(double value){
	walkspeed = value;
}

//Returns player walkspeed
double Player::getWalkspeed() const {
	return walkspeed;
}

//Sets player sprite
void Player::setSprite(){
	player.setTexture(texture);
}

//Returns player sprite
sf::Sprite& Player::getPlayer(){
	return player;
}

//Sets player texture
bool Player::setTexture(std::string texturePath){
	if (!texture.loadFromFile(texturePath)) {
		return false;
	}
	std::cout << "Loaded" << std::endl;
	return true;
}

//Moves player left
void Player::MoveLeft(double dt) {
	player.setPosition(player.getPosition().x - 1, player.getPosition().y);
}

//Moves player right
void Player::MoveUp(double dt) {
	player.setPosition(player.getPosition().x, player.getPosition().y-1);
}

//Movbes player down
void Player::MoveDown(double dt) {
	player.setPosition(player.getPosition().x, player.getPosition().y+1);
}

//Moves player Right
void Player::MoveRight(double dt) {
	player.setPosition(player.getPosition().x + 1, player.getPosition().y);
}

//Updates player position
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

//Draws player to screen
void Player::Draw(sf::RenderWindow &window) {
	window.draw(player);
}