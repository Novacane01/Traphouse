//#include "stdafx.h"
#include "Player.h"


//Player Constructor
Player::Player(std::string name, float hp, float walkspeed, float maxStamina):maxHp(hp),defaultWalkspeed(walkspeed){
	//Chest *chest = new Chest();
	setName(name);
	setCurrentHp(maxHp);
	setMaxStamina(maxStamina);
	setCurrentStamina(this->maxStamina);
	setCurrentWalkSpeed(walkspeed);
	player.setOrigin(20,20);
	player.setPosition(0,0);
	setTexture("Sprites/PlayerAnims/Walking/Walking1.png");
	weaponInventory.push_back(*Weapon::weaponList["defaultPistol"]);
	std::cout << "\'Pistol\' added to inventory" << std::endl;
	//chest->Open(this);
	weaponInventory.push_back(*Weapon::weaponList["shotgun"]);
	std::cout << "\'Shotgun\' added to inventory" << std::endl;
	//potionInventory.push_back(new TimePotion());
	//potionInventory.push_back(new AttackPotion());
	//std::cout << "\'Health Potion' added to inventory" << std::endl;
	//weaponInventory.push_back(pickups.assaultRifle);
	//weaponInventory.push_back(pickups.boltSniper);
	//std::cout << "\'Minigun\' added to inventory" << std::endl;
	//weaponInventory.push_back(pickups.defaultKnife);
	//std::cout << "\'Knife\' added to inventory" << std::endl;
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
void Player::setCurrentWalkSpeed(float value){
	currentWalkspeed = value;
}

//Returns player's current walkspeed
float Player::getCurrentWalkspeed() const {
	return currentWalkspeed;
}

//Returns player's default walkspeed
float Player::getDefaultWalkspeed() const {
	return defaultWalkspeed;
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
	player.move(-(dt*currentWalkspeed), 0);
}

//Moves player up
void Player::MoveUp(float dt) {
	player.move(0, -(dt*currentWalkspeed));
}

//Movbes player down
void Player::MoveDown(float dt) {
	player.move(0, (dt*currentWalkspeed));
}

//Moves player right
void Player::MoveRight(float dt) {
	player.move((dt*currentWalkspeed), 0);
}

//Returns status of player
bool Player::isDead() const{
	return bIsDead;
}

//Displays player info to screen
void Player::displayPlayerInfo(sf::RenderWindow &window) {
	if (poisoned) {
		healthBar.setFillColor(sf::Color::Magenta);
	}
	if (!poisoned&&healthBar.getFillColor() == sf::Color::Magenta) {
		healthBar.setFillColor(sf::Color::Red);
	}
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
	if (disables.size() == 0) {
		disableTimer.restart();
	}
	else {
		float dTime = disableTimer.restart().asSeconds();
		for (unsigned i = 0;i < disables.size();) {
			if (disables[i].first == "Slow") {
				slowed = true;
				currentWalkspeed = defaultWalkspeed / 2.f;
				disables[i].second -= dTime;
				if (disables[i].second <= 0) {
					disables.erase(disables.begin() + i--);
					currentWalkspeed = defaultWalkspeed;
					slowed = false;
				}
				else {
					i++;
				}
			}
			else if (disables[i].first == "Stun") {
				stunned = true;
				disables[i].second -= dTime;
				if (disables[i].second <= 0) {
					disables.erase(disables.begin() + i--);
					stunned = false;
				}
				else {
					i++;
				}
			}
			else if (disables[i].first == "Poison") {
				poisoned = true;
				disables[i].second -= dTime;
				if (poisonTimer.getElapsedTime().asSeconds() >= 1.5f) {
					currentHp--;
					poisonTimer.restart();
				}
				if (disables[i].second <= 0) {
					disables.erase(disables.begin() + i--);
					poisoned = false;
				}
				else {
					i++;
				}
			}
		}
	}
	if (buffs.size() == 0) {
		buffTimer.restart();
	}
	else {
		float bTime = buffTimer.restart().asSeconds();
		for (unsigned i = 0;i < buffs.size();) {
			if (buffs[i].first == "Stamina") {
				energized = true;
				buffs[i].second -= bTime;
				if (buffs[i].second <= 0) {
					buffs.erase(buffs.begin() + i--);
					energized = false;
				}
				else {
					i++;
				}
			}
			else if (buffs[i].first == "Attack") {
				empowered = true;
				std::cout << buffs[i].second - bTime << " seconds left" << std::endl;
				buffs[i].second -= bTime;
				if (buffs[i].second <= 0) {
					buffs.erase(buffs.begin() + i--);
					empowered = false;
				}
				else {
					i++;
				}
			}
			else if (buffs[i].first == "Speed") {
				triggerhappy = true;
				buffs[i].second -= bTime;
				if (buffs[i].second <= 0) {
					buffs.erase(buffs.begin() + i--);
					triggerhappy = false;
				}
				else {
					i++;
				}
			}
			else if (buffs[i].first == "Time") {
				stopwatch = true;
				buffs[i].second -= bTime;
				if (buffs[i].second <= 0) {
					buffs.erase(buffs.begin() + i--);
					stopwatch = false;
				}
				else {
					i++;
				}
			}
		}
	}

	if (currentStamina == maxStamina) {
		bCanSprint = true;
	}
	else if (currentStamina <= 0) {
		bCanSprint = false;
	}

	if ((bIsSprinting&&bCanSprint&&!slowed||energized)&&!stunned) {
		currentWalkspeed = defaultWalkspeed*1.5f;
		currentStamina -= (energized)?0.f:1.f;
	}
	else if (currentStamina < 500.f&&!slowed) {
		currentWalkspeed = defaultWalkspeed;
		currentStamina += .5f;
	}
	if (currentHp <= 0) {
		bIsDead = true;
	}
	if (!stunned) {
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

//Returns potion iniventory
std::vector<Potion *>& Player::getPotions() {
	return potionInventory;
}

//Returns current potion
Potion* Player::getCurrentPotion() {
	return potionInventory[0];
}

//Swaps potions
void Player::switchPotions() {
	std::vector<Potion *> temp = potionInventory;
	potionInventory.clear();
	potionInventory.push_back(temp[1]);
	potionInventory.push_back(temp[0]);
	std::cout << "Potions swapped" << std::endl;
	for (unsigned i = 1;i <= potionInventory.size();i++) {
		std::cout << i << ". " << potionInventory[i-1]->getName() << std::endl;
	}
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
		getCurrentWeapon().bIsReloading = false;
		getCurrentWeapon().bCanReload = true;
	}
}

//Player Deconstructor
Player::~Player() {

}