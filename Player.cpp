
#include "Player.h"
#include "Pickup.h"
#include "Map.h"

Player::Player(std::string name, int hp, double walkspeed){
	setName(name);
	setHp(hp);
	setWalkSpeed(walkspeed);
	weaponInventory.push_back(pickups.defaultPistol);
	std::cout << "\'Pistol\' added to inventory" << std::endl;
	weaponInventory.push_back(pickups.defaultKnife);
	std::cout << "\'Knife\' added to inventory" << std::endl;
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
void Player::Update(sf::RenderWindow &window, double dt, int isColliding) {

		if (isMovingUp && isColliding != 1 && isColliding != 5 && isColliding != 6) {
			MoveUp(dt);
		}
		if (isMovingDown && isColliding != 2 && isColliding != 7 && isColliding != 8) {
			MoveDown(dt);
		}
		if (isMovingRight && isColliding != 3 && isColliding != 5 && isColliding != 7) {
			MoveRight(dt);
		}
		if (isMovingLeft && isColliding != 4 && isColliding != 6 && isColliding != 8) {
			MoveLeft(dt);
		}
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
	std::vector<Weapon> temp = weaponInventory;
	weaponInventory.clear();
	weaponInventory.push_back(temp[1]);
	weaponInventory.push_back(temp[0]);
	//weaponInventory.clear();
	/*weaponInventory.push_back(weaponInventory[0]);
	weaponInventory.erase(weaponInventory.begin());*/
	
	std::cout << "Weapons Swapped: " << std::endl;
	for (int i = 0; i < weaponInventory.size();i++) {
		std::cout << i + 1 << ". " << weaponInventory[i].getName() << std::endl;
	}
}

Player::~Player() {

}