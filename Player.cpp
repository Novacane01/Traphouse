#include "Player.h"
#include "Chest.h"


//Player Constructor
Player::Player(std::string name, float hp, float walkspeed, float maxStamina):maxHp(hp),defaultWalkspeed(walkspeed){ //player constructor
	setName(name);
	setCurrentHp(maxHp);
	setMaxStamina(maxStamina);
	setCurrentStamina(this->maxStamina);
	setCurrentWalkSpeed(walkspeed);
	player.setOrigin(20,20);
	player.setPosition(0,0);
	score = 0;
	setTexture("Sprites/PlayerAnims/Walking/Walking1.png");
	weaponInventory.push_back(*Weapon::weaponList["defaultPistol"]);
	std::cout << "\'Pistol\' added to inventory" << std::endl;

	weaponInventory.push_back(*Weapon::weaponList["boltSniper"]);

	//std::cout << "\'Shotgun\' added to inventory" << std::endl;
	//potionInventory.push_back(new TimePotion());
	//potionInventory.push_back(new TimePotion());
	//potionInventory.push_back(new AttackPotion());
	//std::cout << "\'Health Potion' added to inventory" << std::endl;


	//std::cout << "\'Minigun\' added to inventory" << std::endl;
	//weaponInventory.push_back(pickups.defaultKnife);
	//std::cout << "\'Knife\' added to inventory" << std::endl;
	if(potionInventory.size() > 0){
		currentPotion = potionInventory[0];
	}
}

//Sets UI
void Player::setUI() { // UI for name, score, health and stamina
	font.loadFromFile("Fonts/light_pixel-7.ttf");

	healthBar.setFillColor(sf::Color::Red);
	staminaBar.setFillColor(sf::Color::Green);

	playerScore.setFont(font);
	playerScore.setCharacterSize(30);
	playerScore.setString("Score: " + score);

	playerName.setFont(font);
	playerName.setCharacterSize(25);
	playerName.setString(getName());


	hpNum.setCharacterSize(15);
	hpNum.setFont(font);

	sf::RectangleShape tempSlot;
	tempSlot.setSize(sf::Vector2f(35,42));
	sf::Color color(100,100,100);
	tempSlot.setFillColor(color);
	tempSlot.setOrigin(tempSlot.getSize().x/2,tempSlot.getSize().y/2);
	tempSlot.setOutlineThickness(5);
	tempSlot.setOutlineColor(sf::Color::Transparent);
	potionSlots.push_back(tempSlot);
	potionSlots.push_back(tempSlot);
	potionSlots.push_back(tempSlot);
	potionSlots.push_back(tempSlot);
	potionSlots.push_back(tempSlot);
}

//Sets player name
void Player::setName(std::string value) {
	name = value;
}

//Returns player name
const std::string Player::getName() const{ //getter and setters for name

    return name;
}

//Sets player currentStamina
void Player::setCurrentStamina(float value) { //set stamina
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

void Player::setScore(int scoreValue){ //incrementing score
	score += scoreValue;
}

int Player::getScore(){
	return score;
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
	player.move(0, -(dt*currentWalkspeed)); //most of this is self explanatory
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
void Player::displayPlayerInfo(sf::RenderWindow &window) { //displaying all info about player
	if (poisoned) {
		healthBar.setFillColor(sf::Color::Magenta);
	}
	if (!poisoned&&healthBar.getFillColor() == sf::Color::Magenta) {
		healthBar.setFillColor(sf::Color::Red);
	}

	healthBar.setSize(sf::Vector2f(currentHp*2.5f, 5));
    healthBar.setPosition(window.getView().getCenter().x - (window.getView().getSize().x/2) + 20, window.getView().getCenter().y - (window.getView().getSize().y/2) + 90);

    //places stamina bar below health bar
	staminaBar.setSize(sf::Vector2f(currentStamina/2.f, 5));
    staminaBar.setPosition(healthBar.getPosition().x, healthBar.getPosition().y + 20);

    //Places player name above health bar, top left corner
	playerName.setPosition(healthBar.getPosition().x, healthBar.getPosition().y - 70);

    //places current health above health bar, centered
    hpNum.setString(std::to_string((int)currentHp) + "/" + std::to_string((int)maxHp));
    if(hpNum.getGlobalBounds().left  > (window.getView().getCenter().x-window.getView().getSize().x/2 + 40)){
        hpNum.setPosition(healthBar.getPosition().x + healthBar.getSize().x/2 - hpNum.getGlobalBounds().width/2, healthBar.getPosition().y - 30);
    } else{
        hpNum.setPosition((window.getView().getCenter().x-window.getView().getSize().x/2) + 40, healthBar.getPosition().y - 30);
    }
    //gets current player score and sets UI to that
    playerScore.setString("Score: " + std::to_string(score));
    //Places player score in top right corner of view
    playerScore.setPosition(window.getView().getCenter().x + window.getView().getSize().x/2 - 240, window.getView().getCenter().y - window.getView().getSize().y/2 + 20);

    getCurrentWeapon().weaponImage.setPosition(window.getView().getCenter().x + 410, window.getView().getCenter().y + 380);

    potionSlots[0].setPosition(window.getView().getCenter().x - window.getView().getSize().x/2 + 35,window.getView().getCenter().y + window.getView().getSize().y/2 - 40);
    potionSlots[1].setPosition(potionSlots[0].getPosition().x + 55, potionSlots[0].getPosition().y);
    potionSlots[2].setPosition(potionSlots[1].getPosition().x + 55, potionSlots[1].getPosition().y);
    potionSlots[3].setPosition(potionSlots[2].getPosition().x + 55, potionSlots[2].getPosition().y);
    potionSlots[4].setPosition(potionSlots[3].getPosition().x + 55, potionSlots[3].getPosition().y);

    window.draw(potionSlots[0]);
    window.draw(potionSlots[1]);
    window.draw(potionSlots[2]);
    window.draw(potionSlots[3]);
    window.draw(potionSlots[4]);

	for(int i = 0; i< potionInventory.size(); i++){
		if(i == 5){
			break;
		}
		if(potionInventory[i] == currentPotion){
			potionSlots[i].setOutlineColor(sf::Color::Red);
		} else{
			potionSlots[i].setOutlineColor(sf::Color::Transparent);
		}

		potionInventory[i]->potion.setPosition(potionSlots[i].getPosition());
		window.draw(potionInventory[i]->getPotionSprite());
	}

	for(int i = (int)potionInventory.size(); i < 5; i++){
		potionSlots[i].setOutlineColor(sf::Color::Transparent);
	}
    window.draw(getCurrentWeapon().weaponImage);
    window.draw(playerScore);
    window.draw(playerName);
    window.draw(staminaBar);
	window.draw(healthBar);
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
				bCanRegenStamina = false;
				currentWalkspeed = defaultWalkspeed / 2.f;
				disables[i].second -= dTime;
				if (disables[i].second <= 0) {
					disables.erase(disables.begin() + i--);
					currentWalkspeed = defaultWalkspeed;
					slowed = false;
					bCanRegenStamina = true;
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
					buffs.erase(buffs.begin() + i--); //stamina work
					energized = false;
				}
				else {
					i++;
				}
			}
			else if (buffs[i].first == "Attack") {
				empowered = true;
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
	if (currentStamina >= maxStamina) { //can or cannot sprint
		bCanSprint = true;
	}
	else if (currentStamina <= 0) {
		bCanSprint = false;
	}

	if (slowed||stunned) {
		bCanRegenStamina = false;
	}
	else {
		bCanRegenStamina = true;
	}

	if ((bIsSprinting&&bCanSprint&&!slowed||energized)&&!stunned) {
		currentWalkspeed = defaultWalkspeed*1.5f;
		currentStamina -= (energized)?0.f:100.f*dt;
	}
	else if (currentStamina < maxStamina&&bCanRegenStamina) {
		currentWalkspeed = defaultWalkspeed;
		currentStamina += 100.f*dt;
	}
	if (currentHp <= 0) {
		bIsDead = true;
	}
	else{
		bIsDead = false;
	}
	if (!stunned) {
		if (isMovingUp&&canMoveUp) {
			MoveUp(dt);
		}
		if (isMovingDown&&canMoveDown) {
			MoveDown(dt);
		}
		if (isMovingRight&&canMoveRight) { //stun function
			MoveRight(dt);
		}
		if (isMovingLeft&&canMoveLeft) {
			MoveLeft(dt);
		}
	}

	if (bCanShoot&&shootTimer.getElapsedTime().asSeconds() > ((triggerhappy) ? getCurrentWeapon().getAttackSpeed() / 2.f : getCurrentWeapon().getAttackSpeed())&&!stunned) {
		getCurrentWeapon().Shoot(this, window);
		shootTimer.restart();
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

}

//Returns current weapon
Weapon& Player::getCurrentWeapon() {
	return weaponInventory[0];
}

//Returns weapon inventory
std::vector<Weapon>& Player::getWeapons() {
	return weaponInventory;
}

void Player::pickUpWeapon(Weapon &weapon) {
	weaponInventory[0] = weapon;
}

//Returns potion iniventory
std::vector<Potion *>& Player::getPotions() {
	return potionInventory;
}

//Returns current potion
Potion* Player::getCurrentPotion() {
	return currentPotion;
}

void Player::setCurrentPotion(Potion* potion){
    currentPotion = potion;
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
    std::vector<Weapon> temp = weaponInventory;
    weaponInventory.clear();
    weaponInventory.push_back(weapon);
	weaponInventory.push_back(temp[temp.size()-1]);
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

		std::string gunName = getCurrentWeapon().getName();

        if(gunName == "M1911")
        {
            player.setOrigin(20, 20);
            setTexture("Sprites/PlayerAnims/Walking/WalkingM1911.png");

        }
        if(gunName == "Desert Eagle")
        {
            player.setOrigin(27, 20);

            setTexture("Sprites/PlayerAnims/Walking/WalkingDesertEagle.png");

        }
        if(gunName == "L96A1")
        {
            player.setOrigin(32, 20);

            setTexture("Sprites/PlayerAnims/Walking/WalkingL96A1.png");

        }
        if(gunName == "M14")
        {
            player.setOrigin(32, 20);

            setTexture("Sprites/PlayerAnims/Walking/WalkingM14.png");

        }
        if(gunName == "KSG")
        {
            player.setOrigin(32, 20);

            setTexture("Sprites/PlayerAnims/Walking/WalkingKSG.png");

        }
        if(gunName == "AK47")
        {
            player.setOrigin(32, 20);

            setTexture("Sprites/PlayerAnims/Walking/WalkingAK47.png");

        }
        if(gunName == "Minigun")
        {
            player.setOrigin(32, 20);

            setTexture("Sprites/PlayerAnims/Walking/WalkingMinigun.png");

        }
        if(gunName == "Barrett .50 Cal")
        {
            player.setOrigin(32, 20);

            setTexture("Sprites/PlayerAnims/Walking/WalkingBarrett.png");

        }
        if(gunName == "MP40")
        {
            player.setOrigin(32, 20);

            setTexture("Sprites/PlayerAnims/Walking/WalkingMP40.png");

        }
	}
}

//Player Deconstructor
Player::~Player() {

}