#include "stdafx.h"
#include "Player.h"
#include "Pickup.h"

//Player Constructor
Player::Player(std::string name, int hp, double walkspeed){
	setName(name);
	setHp(hp);
	setWalkSpeed(walkspeed);
	player.setOrigin(20,20);
	player.setPosition(400, 400);
	setTexture("Sprites\\PlayerAnims\\Walking\\Walking1.png");
	setSprite();
	weaponInventory.push_back(pickups.defaultPistol);
	std::cout << "\'Pistol\' added to inventory" << std::endl;
	/*weaponInventory.push_back(pickups.defaultKnife);
	std::cout << "\'Knife\' added to inventory" << std::endl;*/
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
	player.setPosition(player.getPosition().x - (dt*walkspeed), player.getPosition().y);
}

//Moves player right
void Player::MoveUp(double dt) {
	player.setPosition(player.getPosition().x, player.getPosition().y- (dt*walkspeed));
}

//Movbes player down
void Player::MoveDown(double dt) {
	player.setPosition(player.getPosition().x, player.getPosition().y+(dt*walkspeed));
}

//Moves player Right
void Player::MoveRight(double dt) {
	player.setPosition(player.getPosition().x + (dt*walkspeed), player.getPosition().y);
}

//Updates player position and rotation
void Player::Update(sf::RenderWindow &window, double dt) {
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

	//Rotates player based off of mouse position
	sf::Vector2f playerPosition = player.getPosition();
	double a = sf::Mouse::getPosition(window).x - playerPosition.x;
	double b = sf::Mouse::getPosition(window).y - playerPosition.y;
	double angle = -atan2(a, b) * 180 / 3.14;
	player.setRotation(angle);
}

//Draws player to screen
void Player::Draw(sf::RenderWindow &window) {
	window.draw(player);
}

//Returns current weapon
Weapon& Player::getCurrentWeapon() {
	return weaponInventory[0];
}

//Returns weapon inventory
std::vector<Weapon>& Player::getWeapons() {
	return weaponInventory;
}

//Sets current weapon
void Player::setWeapon(Weapon &weapon) {
	weaponInventory[0] = weapon;
	std::cout << "Weapon set to \"" << weapon.getName() << "\"" << std::endl;
}

//Swaps weapons
void Player::switchWeapons() {
	if (weaponInventory.size() > 1) {
		std::vector<Weapon> temp = weaponInventory;
		weaponInventory.clear();
		weaponInventory.push_back(temp[1]);
		weaponInventory.push_back(temp[0]);
		std::cout << "Weapons Swapped: " << std::endl;
		for (int i = 0; i < weaponInventory.size();i++) {
			std::cout << i + 1 << ". " << weaponInventory[i].getName() << std::endl;
		}
	}
}

//Player Deconstructor
Player::~Player() {

}