#include "Enemy.h"
#include "Player.h"

//Enemy Constructor
Enemy::Enemy(std::string name, int hp, float attack, float walkspeed):name(name) {
	enemy.setOrigin(20, 20);
	enemy.setPosition(600, 600);
	setHp(hp);
	setWalkspeed(walkspeed);
	setAttack(attack);
}

void Enemy::Update(Player *player, float dt) {
	//Checks for bullet collision
	for (unsigned i = 0; i < player->getWeapons().size();i++) {
		for (unsigned j = 0;j < player->getWeapons()[i].bullets.size();j++) {
			if (enemy.getGlobalBounds().intersects(player->getWeapons()[i].bullets[j].getBullet().getGlobalBounds())) {
				std::cout << "Hit: " << player->getWeapons()[i].getDamage() << " damage" << std::endl;
				setHp(getHp() - player->getWeapons()[i].getDamage());
				player->getCurrentWeapon().bullets.erase(player->getCurrentWeapon().bullets.begin() + i);
				if (hp <= 0) {
					dead = true;
				}
			}
		}
	}

	//Moves enemy in respect to player position
	sf::Vector2f dir = player->getPlayer().getPosition() - enemy.getPosition();
	setDirection(dir);
	enemy.move(direction.x*dt*walkspeed,direction.y*dt*walkspeed);

	//Rotates enemy based off of player position
	sf::Vector2f playerPosition = player->getPlayer().getPosition();
	float a = enemy.getPosition().x - playerPosition.x;
	float b = enemy.getPosition().y - playerPosition.y;
	float angle = -atan2(a, b) * 180 / 3.14f;
	enemy.setRotation(angle);
}

void Enemy::setDirection(sf::Vector2f &dVector) {
	sf::Vector2f uVector;
	float mag = sqrt(pow(dVector.x, 2) + pow(dVector.y, 2));
	uVector.x = dVector.x / mag;
	uVector.y = dVector.y / mag;
	direction = uVector;
}

void Enemy::Spawn(Player *player, int windowWidth, int windowLength){
	sf::Vector2f playerPosition = player->getPlayer().getPosition();
	float enemyx;
	float enemyy;
	float i1 = rand()%(int)((windowWidth - (playerPosition.x + 100) + 1)+(playerPosition.x+100));
	float i2 = rand()%(int)(playerPosition.x - 99);
	float j1 = rand()%(int)((windowLength - (playerPosition.y + 100) + 1)+(playerPosition.y+100));
	float j2 = rand()%(int)(playerPosition.y - 99);
	float num = rand()/RAND_MAX;
	float num2 = rand()/RAND_MAX;
	if (num > 0.5){
		enemyx = i1;
	}
	if (num <= 0.5){
		enemyx = i2;
	}
	if (num > 0.5){
		enemyy = j1;
	}
	if (num <= 0.5){
		enemyy = j2;
	}

}

bool Enemy::isDead() {
	return dead;
}

void Enemy::setHp(int value) {
	hp = value;
}

void Enemy::setWalkspeed(float value) {
	walkspeed = value;
}

void Enemy::setAttack(float value) {
	attack = value;
}

float Enemy::getAttack() const {
	return attack;
}

std::string Enemy::getName() const {
	return name;
}

float Enemy::getWalkspeed() const {
	return walkspeed;
}

sf::Sprite Enemy::getEnemy() const {
	return enemy;
}

int Enemy::getHp() const {
	return hp;
}

void Enemy::setTexture(std::string texturePath) {
	if (texture.loadFromFile(texturePath)) {
		enemy.setTexture(texture);
	}
}

Enemy::~Enemy() {
	std::cout << "Destroyed" << std::endl;
}

//Skeleton Class
Skeleton::Skeleton():Enemy("Skeleton",100,10.f,30.f) {
	setTexture("Sprites/EnemyAnims/Skeleton/Idle.png");
}

void Skeleton::boneWhack(Player *player) {
	player->setHp(player->getHp() - getAttack());
}

void Skeleton::boneThrow(Player *player) {
	player->setHp(player->getHp() - getAttack());
}

void Skeleton::walkAnim() {
	
}