//#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Collision.h"

std::vector<Enemy *> Enemy::enemies;

//Enemy Constructor
Enemy::Enemy(std::string name, int hp, float attack, float walkspeed, float attackSpeed):name(name) {
	enemy.setOrigin(20, 20);
	enemy.setPosition(600, 600);
	setHp(hp);
	setWalkspeed(walkspeed);
	setAttack(attack);
	setAttackSpeed(attackSpeed);
}

//Checks for bullet collision
void Enemy::isHit(Player * player) {
	for (unsigned i = 0; i < player->getWeapons().size();i++) {
		for (unsigned j = 0;j < player->getWeapons()[i].bullets.size();j++) {
			if (enemy.getGlobalBounds().intersects(player->getWeapons()[i].bullets[j].bullet.getGlobalBounds())) {
				std::cout << "Hit: " << player->getWeapons()[i].getDamage() << " damage" << std::endl;
				setHp(getHp() - (int)player->getWeapons()[i].getDamage());
				player->getWeapons()[i].bullets.erase(player->getWeapons()[i].bullets.begin() + j);
				if (hp <= 0) {
					bIsDead = true;
				}
			}
		}
	}
}

//Sets Direction of Enemy
void Enemy::setDirection(sf::Vector2f &dVector) {
	sf::Vector2f uVector;
	float mag = sqrt(pow(dVector.x, 2) + pow(dVector.y, 2));
	uVector.x = dVector.x / mag;
	uVector.y = dVector.y / mag;
	direction = uVector;
}

//Returns direction of enemy
sf::Vector2f Enemy::getDirection() const {
	return direction;
}

//Returns all current enemies
std::vector<Enemy *> &Enemy::getEnemies() {
	return enemies;
}

//Spawns an enemy
void Enemy::Spawn(Enemy *enemy) {
	enemies.push_back(enemy);
}

//Destroys an enemy
void Enemy::Destroy(std::vector<Enemy *>::iterator &pos) {
	enemies.erase(pos);
}

//Checks if enemy is dead
bool Enemy::isDead() const {
	return bIsDead;
}

//Sets enemy HP
void Enemy::setHp(int value) {
	hp = value;
}

//Sets enemy walkspeed
void Enemy::setAttackSpeed(float val) {
	attackSpeed = val;
}

//Returns attackspeed
float Enemy::getAttackSpeed() const {
	return attackSpeed;
}

//Sets enemy walkspeed
void Enemy::setWalkspeed(float value) {
	walkspeed = value;
}

//Sets enemy attack
void Enemy::setAttack(float value) {
	attack = value;
}

//Returns enemy attack
float Enemy::getAttack() const {
	return attack;
}

//Sets enemy name
std::string Enemy::getName() const {
	return name;
}

//Returns enemy walkspeed
float Enemy::getWalkspeed() const {
	return walkspeed;
}

//Returns enemy object
sf::Sprite Enemy::getEnemy() const{
	return enemy;
}

//Returns enemy hp
int Enemy::getHp() const {
	return hp;
}

//Sets enemy texture
void Enemy::setTexture(sf::Sprite &sprite,sf::Texture &texture, std::string texturePath) {
	if (texture.loadFromFile(texturePath)) {
		sprite.setTexture(texture);
	}
}

//Enemy Deconstructor
Enemy::~Enemy() {
	std::cout << "Destroyed" << std::endl;
}


//Skeleton Class
Skeleton::Skeleton():Enemy("Skeleton",100,10.f,100.f, 2.f) {
	rectSourceSprite = sf::IntRect(0,0,64,67);
	setTexture(enemy,texture,"Sprites\\EnemyAnims\\Skeleton\\SkeletonWalk.png");
	setTexture(bone.bone, bone.texture, "Sprites\\EnemyAnims\\Skeleton\\rib.png");
	enemy.setTextureRect(rectSourceSprite);
	
	//64x62 pixels
}

void Skeleton::boneWhack(Player *player) {
	player->setHp(player->getHp() - getAttack());
}

//Throws a bone at player
void Skeleton::boneThrow(Player *player) {
	std::cout << "Throwing bone" << std::endl;
	Bone bone = this->bone;
	bone.deleteTimer.restart();
	bone.bone.setPosition(enemy.getPosition());
	bone.bone.setOrigin(20,20);
	float dirX= player->getPlayer().getPosition().x - enemy.getPosition().x;
	float dirY = player->getPlayer().getPosition().y - enemy.getPosition().y;
	bone.direction.x = dirX / sqrt(pow(dirX, 2) + pow(dirY, 2));
	bone.direction.y = dirY / sqrt(pow(dirX, 2) + pow(dirY, 2));
	bones.push_back(bone);
}

//Skeleton walking animation
void Skeleton::walkAnim() {
	if (animationTimer.getElapsedTime().asSeconds() > 0.05f) {
		if (rectSourceSprite.left >= 909) {
			rectSourceSprite.left = 0;
		}
		else {
			enemy.setTextureRect(rectSourceSprite);
			rectSourceSprite.left += 65;
		}
		animationTimer.restart();
		//std::cout << "Animating" << std::endl;
	}
}

//Updates skeleton and bone positions
void Skeleton::Update(Player *player, float dt) {
	for (unsigned i = 0;i < bones.size();i++) {
		bones[i].bone.move(bones[i].velocity*bones[i].direction.x*dt,bones[i].velocity * bones[i].direction.y*dt);
		bones[i].bone.rotate(180*dt);
		if (bones[i].bone.getGlobalBounds().intersects(player->getPlayer().getGlobalBounds())) {
			std::cout << player->getName() << " took " << getAttack() << " damage!" << std::endl;
			player->setHp(player->getHp() - getAttack());
			bones.erase(bones.begin() + i);
		}
	}
	isHit(player);
	//Moves enemy in respect to player position
	if (Collision::PixelPerfectTest(enemy,player->getPlayer())){
		enemy.move(0, 0);
		if (attackTimer.getElapsedTime().asSeconds() > getAttackSpeed()) {
			boneWhack(player);
			attackTimer.restart();
		}
	}
	else if (attackTimer.getElapsedTime().asSeconds()>getAttackSpeed()) {
		boneThrow(player);
		attackTimer.restart();
	}
	else {
		sf::Vector2f dir = player->getPlayer().getPosition() - enemy.getPosition();
		setDirection(dir);
		enemy.move(getDirection().x*dt*getWalkspeed(), getDirection().y*dt*getWalkspeed());
		walkAnim();
	}
	//Rotates enemy based off of player position
	sf::Vector2f playerPosition = player->getPlayer().getPosition();
	float a = enemy.getPosition().x - playerPosition.x;
	float b = enemy.getPosition().y - playerPosition.y;
	float angle = -atan2(a, b) * 180 / 3.14f;
	enemy.setRotation(angle);
}

void Skeleton::Draw(sf::RenderWindow &window) {
	window.draw(enemy);
	for (unsigned i = 0; i < bones.size();i++) {
		window.draw(bones[i].bone);
		if (bones[i].deleteTimer.getElapsedTime().asSeconds() > 3) {
			std::cout << "Deleting Bone" << std::endl;
			bones.erase(bones.begin() + i);
		}
	}
}