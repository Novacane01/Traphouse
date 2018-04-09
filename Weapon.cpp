#include "stdafx.h"
#include "Player.h"
#include "Weapon.h"
#include <cmath>

//Weapon(Melee) Constructor
Weapon::Weapon(std::string meleeName, float damage, int range, float attackspeed, float dropChance):name(meleeName),range(range),dropChance(dropChance) {
	setDamage(damage);
	setAttackSpeed(attackspeed);
}

//Weapon(Ranged) Construtor
Weapon::Weapon(std::string gunName, int MaxAmmo, int currentMax, int currentClip, float damage,
float attackspeed, float DropChance):name(gunName),maxAmmo(MaxAmmo),dropChance(DropChance){
    setCurrentClip(currentClip);
    setCurrentMax(currentMax);
    setDamage(damage);
    setAttackSpeed(attackspeed);
}

//Shoots bullet
void Weapon::Shoot(Player *player,sf::RenderWindow &window) {
	std::cout << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << std::endl;
	std::cout << player->getPlayer().getPosition().x << " " << player->getPlayer().getPosition().y << std::endl;
	Bullet b(player);

	//Setting accuracy
	sf::Vector2f dVector = (sf::Vector2f)sf::Mouse::getPosition(window)-player->getPlayer().getPosition();
	float newX1 = dVector.x*cos(5*3.14f/180) - dVector.y*sin(5 * 3.14f / 180);
	float newY1 = dVector.x*sin(5 * 3.14f / 180) + dVector.y*cos(5 * 3.14f / 180);
	float newX2 = dVector.x*cos(-5 * 3.14f / 180) - dVector.y*sin(-5 * 3.14f / 180);
	float newY2 = dVector.x*sin(-5 * 3.14f / 180) + dVector.y*cos(-5 * 3.14f / 180);
	float n = ((newX2 - newX1) * ((float)rand() / RAND_MAX)) + newX1;
	float n2 = ((newY2 - newY1) * ((float)rand() / RAND_MAX)) + newY1;
	sf::Vector2f newDir = sf::Vector2f(n, n2);
	b.setDirection(newDir);
	bullets.push_back(b);
}

//Returns bullet
sf::CircleShape Bullet::getBullet() const {
	return bullet;
}

//Updates weapon position
void Weapon::Update(sf::RenderWindow &window, Player *player,float dt){
	for (unsigned i = 0;i < bullets.size();i++) {
		bullets[i].Update(window,dt);
		bullets[i].Draw(window);
	}
	//weapon.setPosition(player->getPlayer().getPosition().x, player->getPlayer().getPosition().y);
	Draw(window);
}

//Draws weapon to screen
void Weapon::Draw(sf::RenderWindow &window) {
	window.draw(weapon);
}

//Sets current clip of weapon
void Weapon::setCurrentClip(int currentClip) {
    this->currentClip = currentClip;
}

//Sets max clip of weapon
void Weapon::setCurrentMax(int currentMax) {
    this->currentMax = currentMax;
}

//Sets weapon damage
void Weapon::setDamage(float damage) {
    this->damage = damage;
}

//Sets weapon attackspeed
void Weapon::setAttackSpeed(float attackSpeed) {
    this->attackSpeed = attackSpeed;
	
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

//Weapon Deconstructor
Weapon::~Weapon() {

}



//Bullet Constructor
Bullet::Bullet(Player *player) {
	bullet.setRadius(2.5);
	bullet.setFillColor(sf::Color::White);
	bullet.setPosition(player->getPlayer().getPosition().x, player->getPlayer().getPosition().y);
	damage = player->getCurrentWeapon().getDamage();
}

//Sets direction of bullet
void Bullet::setDirection(sf::Vector2f &dVector) {
	sf::Vector2f uVector;
	float mag = sqrt(pow(dVector.x, 2) + pow(dVector.y, 2));
	uVector.x = dVector.x / mag;
	uVector.y = dVector.y / mag;
	direction = uVector;
}

//Updates bullet's position
void Bullet::Update(sf::RenderWindow &window, float dt) {
	bullet.move(velocity*dt*direction.x, velocity*dt*direction.y);
}

//Draws bullet to screen
void Bullet::Draw(sf::RenderWindow &window) {
	window.draw(bullet);
}


