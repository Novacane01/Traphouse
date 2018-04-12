#include "stdafx.h"
#include "Player.h"
#include "Pickup.h"
#include "Map.h"

//Player Constructor
Player::Player(std::string name, int hp, float walkspeed, float stamina){
	setName(name);
	setHp(hp);
	setStamina(stamina);
	setWalkSpeed(walkspeed);
	player.setOrigin(20,20);
	player.setPosition(WINDOW_WIDTH/2, WINDOW_LENGTH/2);
	setTexture("Sprites\\PlayerAnims\\Walking\\Walking1.png");
	weaponInventory.push_back(pickups.defaultPistol);
	std::cout << "\'Pistol\' added to inventory" << std::endl;
	weaponInventory.push_back(pickups.defaultKnife);
	std::cout << "\'Knife\' added to inventory" << std::endl;
	setUI();
}

//Sets UI
void Player::setUI() {
	font.loadFromFile("Fonts\\light_pixel-7.ttf");
	healthBar.setPosition(20, 55);
	healthBar.setFillColor(sf::Color::Red);
	staminaBar.setFillColor(sf::Color::Green);
	staminaBar.setPosition(20, 65);
	playerName.setString(getName());
	playerName.setCharacterSize(25);
	playerName.setPosition(20, 5);
	playerName.setFont(font);
	hpNum.setPosition(20, 35);
	hpNum.setCharacterSize(15);
	hpNum.setFont(font);
}

//Sets player name
void Player::setName(std::string value) {
	name = value;
}

//Returns player name
const std::string Player::getName() const{
	return name;
}

//Sets player stamina
void Player::setStamina(float value) {
	stamina = value;
}

//Returns player stamina
float Player::getStamina() const {
	return stamina;
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
void Player::setWalkSpeed(float value){
	walkspeed = value;
}

//Returns player walkspeed
float Player::getWalkspeed() const {
	return walkspeed;
}

//Returns player sprite
sf::Sprite& Player::getPlayer(){
	return player;
}

//Sets player texture
void Player::setTexture(std::string texturePath){
	if (texture.loadFromFile(texturePath)) {
		player.setTexture(texture);
	}
}

//Moves player left
void Player::MoveLeft(float dt) {
	if (bIsSprinting&&stamina>0)
		player.move(-(dt*walkspeed*1.5f), 0);
	else
		player.move(-(dt*walkspeed), 0);
}

//Moves player up
void Player::MoveUp(float dt) {
	if (bIsSprinting&&stamina>0)
		player.move(0, -(dt*walkspeed*1.5f));
	else
		player.move(0, -(dt*walkspeed));
}

//Movbes player down
void Player::MoveDown(float dt) {
	if (bIsSprinting&&stamina>0)
		player.move(0, (dt*walkspeed*1.5f));
	else
		player.move(0, (dt*walkspeed));
}

//Moves player right
void Player::MoveRight(float dt) {
	if(bIsSprinting&&stamina>0)
		player.move((dt*walkspeed*1.5f), 0);
	else 
		player.move((dt*walkspeed), 0);
}

//Returns status of player
bool Player::isDead() const{
	return bIsDead;
}

//Displays player info to screen
void Player::displayPlayerInfo(sf::RenderWindow &window) {
	healthBar.setSize(sf::Vector2f(hp*2.5f, 5));
	staminaBar.setSize(sf::Vector2f(stamina / 2, 5));
	hpNum.setString(std::to_string(hp) + "/100");
	window.draw(staminaBar);
	window.draw(healthBar);
	window.draw(playerName);
	window.draw(hpNum);
}

//Updates player position and player rotation
void Player::Update(sf::RenderWindow &window, float dt, Map *map) {
	if (bIsSprinting&&stamina>0) {
		stamina -= 1.f;
	}
	else if (stamina < 500) {
		stamina += .5f;
	}
	if (hp <= 0) {
		bIsDead = true;
	}
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
	//map->collisionTest(this);

	//Rotates player based off of mouse position
	sf::Vector2f playerPosition = player.getPosition();
	sf::Vector2f WorldCoords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	float a = WorldCoords.x - playerPosition.x;
	float b = WorldCoords.y - playerPosition.y;
	float angle = -atan2(a, b) * 180 / 3.14f;
	player.setRotation(angle);
}


//Draws player to screen
void Player::Draw(sf::RenderWindow &window) {
	window.draw(player);
	displayPlayerInfo(window);
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
		for (unsigned i = 0; i < weaponInventory.size();i++) {
			std::cout << i + 1 << ". " << weaponInventory[i].getName() << std::endl;
		}
	}
}

//Player Deconstructor
Player::~Player() {

}