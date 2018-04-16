//#include "stdafx.h"
#include "Player.h"
#include "Pickup.h"
#include "Floor.h"

//Player Constructor
Player::Player(std::string name, float hp, float walkspeed, float maxStamina):maxHp(hp){
	setName(name);
	setCurrentHp(maxHp);
	setMaxStamina(maxStamina);
	setCurrentStamina(this->maxStamina);
	setWalkSpeed(walkspeed);
	player.setOrigin(20,20);
	player.setPosition(WINDOW_WIDTH/2.f, WINDOW_LENGTH/2.f);
	setTexture("Sprites/PlayerAnims/Walking/Walking1.png");
	weaponInventory.push_back(pickups.defaultPistol);
	std::cout << "\'Pistol\' added to inventory" << std::endl;
	weaponInventory.push_back(pickups.shotgun);
	//weaponInventory.push_back(pickups.assaultRifle);
	//weaponInventory.push_back(pickups.boltSniper);
	std::cout << "\'Minigun\' added to inventory" << std::endl;
	weaponInventory.push_back(pickups.defaultKnife);
	std::cout << "\'Knife\' added to inventory" << std::endl;
	setUI();
}

//Sets UI
void Player::setUI() {
	font.loadFromFile("Fonts/light_pixel-7.ttf");
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

//Sets player currentStamina
void Player::setCurrentStamina(float value) {
	currentStamina = value;
}

//Returns player currentStamina
float Player::getCurrentStamina() const {
	return currentStamina;
}

//Sets player maxStamina
void Player::setMaxStamina(float value) {
	maxStamina = value;
}

//Returns player maxStamina
float Player::getMaxStamina() const {
	return maxStamina;
}

//Sets player HP
void Player::setCurrentHp(float value){
	currentHp = value;
}

//Returns player's current HP
float Player::getCurrentHp() const{
	return currentHp;
}

//Returns player's max HP
float Player::getMaxHp() const {
	return maxHp;
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
	if (bIsSprinting&&canSprint)
		player.move(-(dt*walkspeed*1.5f), 0);
	else
		player.move(-(dt*walkspeed), 0);
}

//Moves player up
void Player::MoveUp(float dt) {
	if (bIsSprinting&&canSprint)
		player.move(0, -(dt*walkspeed*1.5f));
	else
		player.move(0, -(dt*walkspeed));
}

//Movbes player down
void Player::MoveDown(float dt) {
	if (bIsSprinting&&canSprint)
		player.move(0, (dt*walkspeed*1.5f));
	else
		player.move(0, (dt*walkspeed));
}

//Moves player right
void Player::MoveRight(float dt) {
	if(bIsSprinting&&canSprint)
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
	healthBar.setSize(sf::Vector2f(currentHp*2.5f, 5));
	staminaBar.setSize(sf::Vector2f(currentStamina/2.f, 5));
	hpNum.setString(std::to_string((int)currentHp) + "/" + std::to_string((int)maxHp));
	window.draw(staminaBar);
	window.draw(healthBar);
	window.draw(playerName);
	window.draw(hpNum);
}

//Updates player position and player rotation
void Player::Update(sf::RenderWindow &window, float dt) {
	if (currentStamina == maxStamina) {
		canSprint = true;
	}
	else if (currentStamina <= 0) {
		canSprint = false;
	}
	if (bIsSprinting&&canSprint) {
		currentStamina -= 1.f;
	}
	else if (currentStamina < 500.f) {
		currentStamina += .5f;
	}
	if (currentHp <= 0) {
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
   //std::cout<<weaponInventory[0].getName()<<std::endl;
	return weaponInventory[0];
}

//Returns weapon inventory
std::vector<Weapon>& Player::getWeapons() {
	return weaponInventory;
}

//Sets current weapon
void Player::setWeapon(Weapon &weapon) {
	weaponInventory[0] = weapon;
	//std::cout << "Weapon set to \"" << weapon.getName() << "\"" << std::endl;
}

//Swaps weapons

void Player::switchWeapons() {
	if (weaponInventory.size() > 1) {
		std::vector<Weapon> temp = weaponInventory;
		weaponInventory.clear();
		weaponInventory.push_back(temp[1]);
		weaponInventory.push_back(temp[0]);
		//std::cout << "Weapons Swapped: " << std::endl;
		//for (unsigned i = 0; i < weaponInventory.size();i++) {
			//std::cout << i + 1 << ". " << weaponInventory[i].getName() << std::endl;
		//}
		getCurrentWeapon().bIsReloading = false;
		getCurrentWeapon().bCanReload = true;
	}
}


//Player Deconstructor
Player::~Player() {

}