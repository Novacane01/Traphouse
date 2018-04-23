
#include "GameManager.h"
#include "Player.h"
#include "Weapon.h"
#include <exception>
#include <cmath>

std::map<std::string,Weapon *> Weapon::weaponList;
bool Weapon::gunsLoaded;

//Base Constructor
Weapon::Weapon() {
	if (!gunsLoaded) {
		weaponList["defaultKnife"] = new Weapon("Melee", "Knife", 100000.f, 2, .5f, 0.f);
		weaponList["defaultPistol"]= new Weapon("Pistol", "M1911", 88, 88, 8, 8, 10.f, 0.25f, 1.f, 2.5f, 0.f, "SFX/Guns/shotgun.wav");
		weaponList["heavyPistol"] = new Weapon("Heavy Pistol", "Desert Eagle", 35, 35, 7, 7, 50.f, .5f, 2.f, 2.f, 0.3f, "SFX/Guns/shotgun.wav");
		weaponList["boltSniper"] = new Weapon("Bolt Sniper", "L96A1", 15, 15, 5, 5, 100.f, 2.f, 4.f, 0.f, 0.04f, "SFX/Guns/shotgun.wav");
		weaponList["semiAuto"]= new Weapon("SemiAuto", "M14", 60, 60, 10, 10, 25.f, .4f, 2.f, 1.f, 0.1f, "SFX/Guns/shotgun.wav");
		weaponList["shotgun"] = new Weapon("Shotgun", "KSG", 30, 30, 6, 6, 20.f, 1.f, 0.f, 5.f, 0.1f, "SFX/Guns/shotgun.wav");
		weaponList["assaultRifle"] = new Weapon("Assault Rifle", "AK47", 90, 90, 30, 30, 30.f, .1f, 2.f, 5.f, .01f, "SFX/Guns/shotgun.wav");
		weaponList["minigun"]= new Weapon("Minigun", "Minigun", 180, 180, 180, 180, 20.f, .05f, 5.f, 7.5f, .06f, "SFX/Guns/shotgun.wav");
		weaponList["semiSninper"] = new Weapon("Semi Sniper", "Barrett .50 Cal", 30, 30, 10, 10, 80.f, .5f, 4.f, 0.f, .01f, "SFX/Guns/shotgun.wav");
		weaponList["submachine"] = new Weapon("Submachine Gun", "MP40", 96, 96, 32, 32, 20.f, .4f, 2.f, 2.5f, .2f, "SFX/Guns/shotgun.wav");
		gunsLoaded = true;
	}
}
//Weapon(Melee) Constructor
Weapon::Weapon(std::string type, std::string meleeName, float damage, int range, float attackspeed, float dropChance):name(meleeName),maxAmmo(0),range(range),dropChance(dropChance) {
	setDamage(damage);
	setAttackSpeed(attackspeed);
}

//Weapon(Ranged) Construtor
Weapon::Weapon(std::string weaponType, std::string Name, int MaxAmmo, int currentMax, int currentClip, int maxClip, float Damage,
float attackSpeed, float reloadTime, float Deviation, float DropChance, std::string soundFX):type(weaponType),name(Name),maxAmmo(MaxAmmo),deviation(Deviation),dropChance(DropChance){
    setCurrentClip(currentClip);
    setCurrentMax(currentMax);
    setDamage(Damage);
    setAttackSpeed(attackSpeed);
	setMaxClip(maxClip);
	setReloadTime(reloadTime);
	loadBuffer(FXgunshot, soundFX);
	setUI();
}

//Shoots bullet
void Weapon::Shoot(Player *player,sf::RenderWindow &window) {
	if (player->getCurrentWeapon().getCurrentClip() > 0&&!bIsReloading) {
		if (player->getCurrentWeapon().getType() == "Shotgun") {
			for (int i = 0;i < 12;i++) {
				bullets.push_back(createBullet(player, window));
			}
		}
		else {
			bullets.push_back(createBullet(player, window));
		}
		//Subtracting from current ammo
		player->getCurrentWeapon().setCurrentClip(player->getCurrentWeapon().getCurrentClip() - 1);
		std::thread(&Weapon::playAudio, this,&FXgunshot).detach();
	}
	else if (player->getCurrentWeapon().getCurrentClip()==0) {
		bIsReloading = true;
	}
}

//Plays Audio
void Weapon::playAudio(sf::SoundBuffer *buffer) {
	sf::Sound *s = new sf::Sound(*buffer);
	s->setPlayingOffset(sf::seconds(0.2f));
	s->play();
}

//Creates bullet
Weapon::Bullet Weapon::createBullet(Player* player, sf::RenderWindow &window) {
	//Instantiating bullet
	Bullet b;
	if (type == "Sniper") {
		b.velocity *= 5;
	}
	b.damage = (player->empowered)?damage*1.5f:damage;
	b.bullet.setRadius(2.5f);
	b.bullet.setPosition(player->getPlayer().getPosition());

	//Setting accuracy
	sf::Vector2f WorldCoords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	sf::Vector2f dVector = WorldCoords - player->getPlayer().getPosition();
	float newX1 = dVector.x*cos(deviation * 3.14f / 180) - dVector.y*sin(deviation * 3.14f / 180);
	float newY1 = dVector.x*sin(deviation * 3.14f / 180) + dVector.y*cos(deviation * 3.14f / 180);
	float newX2 = dVector.x*cos(-deviation * 3.14f / 180) - dVector.y*sin(-deviation * 3.14f / 180);
	float newY2 = dVector.x*sin(-deviation * 3.14f / 180) + dVector.y*cos(-deviation * 3.14f / 180);
	float n = ((newX2 - newX1) * ((float)rand() / RAND_MAX)) + newX1;
	float n2 = ((newY2 - newY1) * ((float)rand() / RAND_MAX)) + newY1;
	sf::Vector2f newDir = sf::Vector2f(n, n2);
	float mag = sqrt(pow(newDir.x, 2) + pow(newDir.y, 2));
	b.direction = sf::Vector2f(newDir.x / mag, newDir.y / mag);
	return b;
}
//Reloads current weapon
void Weapon::Reload(Player *player) {
	int amountToReload = player->getCurrentWeapon().getMaxClip() - player->getCurrentWeapon().getCurrentClip();
	if (player->getCurrentWeapon().getCurrentClip() == player->getCurrentWeapon().getMaxClip()) {
		std::cout << "Clip Full" << std::endl;
	}
	else if(player->getCurrentWeapon().getCurrentMax()-player->getCurrentWeapon().getMaxClip()>=0) {

		player->getCurrentWeapon().setCurrentMax(player->getCurrentWeapon().getCurrentMax() - amountToReload);
		player->getCurrentWeapon().setCurrentClip(player->getCurrentWeapon().getMaxClip());
		std::cout << "Reloading" << std::endl;
	}
	else if((player->getCurrentWeapon().getCurrentMax() - player->getCurrentWeapon().getMaxClip()<0)){
		if (player->getCurrentWeapon().getCurrentMax() - amountToReload > 0) {
			player->getCurrentWeapon().setCurrentClip(player->getCurrentWeapon().getMaxClip());
			player->getCurrentWeapon().setCurrentMax(player->getCurrentWeapon().getCurrentMax() - amountToReload);
		}
		else {
			player->getCurrentWeapon().setCurrentClip(player->getCurrentWeapon().getCurrentClip()+player->getCurrentWeapon().getCurrentMax());
			player->getCurrentWeapon().setCurrentMax(0);
		}
	}
	else {
		std::cout << "Out of ammo" << std::endl;
	}
}

//Checks if player is able to reload
void Weapon::canReload(Player *player) {
	if (player->getCurrentWeapon().bIsReloading&&player->getCurrentWeapon().bCanReload) {
		reloadTimer.restart();
		bCanReload = false;
		if (type == "Shotgun") {
			for (int i = 0; i < maxClip - currentClip;i++) {
				reloadTime += .5f;
			}
		}
	}
	if (player->getCurrentWeapon().bIsReloading) {
		if (player->getCurrentWeapon().reloadTimer.getElapsedTime().asSeconds() >= ((player->triggerhappy)?player->getCurrentWeapon().reloadTime/2:player->getCurrentWeapon().reloadTime)) {
			Reload(player);
			bCanReload = true;
			bIsReloading = false;
			if (type == "Shotgun") {
				reloadTime = 0.f;
			}
		}
	}
}

//Sets weapon firing audio
void Weapon::loadBuffer(sf::SoundBuffer &buffer, std::string soundfile) {
	if (!buffer.loadFromFile("SFX/Guns/shotgun.wav")) {
		std::cout << "Could not load sound from file" << std::endl;
	}
}

//Returns weapon max clip
int Weapon::getMaxClip() const {
	return maxClip;
}

//Sets weapon reload time
void Weapon::setReloadTime(float reloadTime) {
	this->reloadTime = reloadTime;
}

//Updates weapon position
void Weapon::Update(sf::RenderWindow &window, Player *player,float dt){
	for (unsigned i = 0;i < bullets.size();i++) {
		bullets[i].bullet.move(bullets[i].direction.x*dt*bullets[i].velocity, bullets[i].direction.y*dt*bullets[i].velocity);
		if (bullets[i].deleteTime.getElapsedTime().asSeconds() > 3) {
			std::cout << "Deleting bullet" << std::endl;
			bullets.erase(bullets.begin() + i);
		}
	}
	//weapon.setPosition(player->getPlayer().getPosition().x, player->getPlayer().getPosition().y);
	canReload(player);
	Draw(window);
}

//Draws weapon to screen
void Weapon::Draw(sf::RenderWindow &window) {
	window.draw(weapon);
	for (unsigned i = 0;i < bullets.size();i++) {
		window.draw(bullets[i].bullet);
	}
}

//Sets current clip of weapon
void Weapon::setCurrentClip(int currentClip) {
    this->currentClip = currentClip;
}

//Sets current max clip of weapon
void Weapon::setCurrentMax(int currentMax) {
    this->currentMax = currentMax;
}

//Sets max clip of weapon
void Weapon::setMaxClip(int maxClip) {
	this->maxClip = maxClip;
}

//Sets weapon damage
void Weapon::setDamage(float damage) {
    this->damage = damage;
}

//Sets weapon attackspeed
void Weapon::setAttackSpeed(float attackSpeed) {
    this->attackSpeed = attackSpeed;
	
}

//Returns weapon type
std::string Weapon::getType() const{
	return type;
}

//Returns weapon name
std::string Weapon::getName() const{
    return name;
}

//Returns weapon's max ammo
int Weapon::getMaxAmmo() const{
    return maxAmmo;
}

//Returns weapon's current ammo
int Weapon::getCurrentMax() const{
    return currentMax;
}

//Returns weapon's current clip
int Weapon::getCurrentClip() const{
    return currentClip;
}

//Returns weapon's damage
float Weapon::getDamage() const{
    return damage;
}

//Returns weapons' attackspeed
float Weapon::getAttackSpeed() const{
    return attackSpeed;
}

//Returns weapon's drop chance
float Weapon::getDropChance() const {
    return dropChance;
}

//Sets ammo UI
void Weapon::setUI() {
	if (!font.loadFromFile("Fonts/light_pixel-7.ttf")) {
		std::cout << "Could not open font" << std::endl;
	}
	ammoCount.setCharacterSize(20);
	ammoCount.setFont(font);

	gunName.setString(name);
	gunName.setFont(font);
	gunName.setCharacterSize(15);
}

//Displays ammo UI
void Weapon::displayWeaponInfo(sf::RenderWindow &window) {
    //Updates current clip numbers
    ammoCount.setString(std::to_string(getCurrentClip()) + "/" + std::to_string(getCurrentMax()));

    //sets x location of ammoCount based on current view
    int infoLocation = (int)window.getView().getCenter().x + (int)window.getView().getSize().x/2 - (int)ammoCount.getGlobalBounds().width - 20;

    //sets location of ammoCount, gunName and ammoBlocks rely on this for location
    ammoCount.setPosition(infoLocation, window.getView().getCenter().y + (window.getView().getSize().y/2) - 50);
    gunName.setPosition(ammoCount.getPosition().x, ammoCount.getPosition().y - 20);

    float offsetX = 0, offsetY = -getMaxClip()/2.f+4, rectSizeX = 5.f, rectSizeY = 15.f, size = 0.f, standardOffset = 40.f, desiredOffset = 200.f;
    for (int i = 8;i < getMaxClip();i += 8) {
        rectSizeX -= 4.f / 23.f;
    }
    for (int i = 32;i < getMaxClip();i+=32) {
        if (i < i + 32) {
            desiredOffset += 100;
        }
    }
    for (int i = 0; i < getMaxClip();i++) {
        sf::RectangleShape temp(sf::Vector2f(rectSizeX, rectSizeY));
        temp.setPosition(ammoCount.getPosition().x-standardOffset-offsetX,ammoCount.getPosition().y+offsetY);
        ammoBlocks.push_back(temp);
        offsetX += 20;
        if (standardOffset + offsetX>desiredOffset) {
            offsetX = 0;
            offsetY += temp.getSize().y+5;
        }
    }
	for (int i = ammoBlocks.size()-1;i >= 0;i--) {
		if ((unsigned)getCurrentClip()<ammoBlocks.size()&&i==ammoBlocks.size()-1) {
			i -= (getMaxClip() - getCurrentClip());
		}
		if ((unsigned)i < ammoBlocks.size()) {
			window.draw(ammoBlocks[i]);
		}
	}
	//clears ammo blocks for next time looped around to get new location.
	ammoBlocks.clear();
    window.draw(ammoCount);
	window.draw(gunName);
}

//Weapon Deconstructor
Weapon::~Weapon() {

}