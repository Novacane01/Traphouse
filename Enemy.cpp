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
				enemy.setColor(sf::Color::Red);
				std::cout << "Hit: " << player->getWeapons()[i].bullets[j].damage << " damage" << std::endl;
				setHp(getHp() - (int)player->getWeapons()[i].bullets[j].damage);
				player->getWeapons()[i].bullets.erase(player->getWeapons()[i].bullets.begin() + j);
				if (hp <= 0) {
					bIsDead = true;
				}
			}
		}
	}
}

//Sets enemy direction
void Enemy::setDirection(sf::Vector2f direction) {
	this->direction = direction;
}

//Returns unit direction vector
sf::Vector2f Enemy::getUDirection(sf::Vector2f &dVector) {
	sf::Vector2f uVector;
	float mag = sqrt(pow(dVector.x, 2) + pow(dVector.y, 2));
	uVector.x = dVector.x / mag;
	uVector.y = dVector.y / mag;
	return uVector;
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
void Enemy::Destroy(std::vector<Enemy *>::iterator pos) {
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
Skeleton::Skeleton(std::string name, int hp, float attack, float walkspeed, float attackspeed):Enemy(name,hp,attack,walkspeed,attackspeed) {
	WalkRect = sf::IntRect(0,0,64,67);
	AttackRect = sf::IntRect(0, 0, 110, 63);
	walkTexture.loadFromFile("Sprites\\EnemyAnims\\Skeleton\\SkeletonWalk.png");
	attackTexture.loadFromFile("Sprites\\EnemyAnims\\Skeleton\\SkeletonMelee.png");
	bone.texture.loadFromFile("Sprites\\EnemyAnims\\Skeleton\\rib.png");
	bone.bone.setTexture(bone.texture);
}

//Whacks player with a Bone
void Skeleton::boneWhack(Player *player) {
	player->setCurrentHp(player->getCurrentHp() - getAttack());
}

//Throws a bone at player
void Skeleton::boneThrow(Player *player) {
	std::cout << "Throwing bone" << std::endl;
	Bone bone = this->bone;
	bone.deleteTimer.restart();
	bone.bone.setPosition(enemy.getPosition());
	bone.bone.setOrigin(20,20);
	bone.direction = player->getPlayer().getPosition() - enemy.getPosition();
	bone.direction = getUDirection(bone.direction);
	bones.push_back(bone);
}

//Skeleton walking animation
void Skeleton::walkAnim(Player *player) {
	//Attacking
	if (animationTimer.getElapsedTime().asSeconds() > 0.07f) {
		if (state == animationState::RANGED || state == animationState::MELEE) {
			if (AttackRect.left >= 1950&&state==animationState::MELEE) {
				AttackRect.left = 0;
				boneWhack(player);
				state = animationState::IDLE;
				attackTimer.restart();
			}
			else if (AttackRect.left>=1700 && state == animationState::RANGED) {
				AttackRect.left = 0;
				boneThrow(player);
				state = animationState::IDLE;
				attackTimer.restart();
			}
			else {
				enemy.setTexture(attackTexture);
				enemy.setTextureRect(AttackRect);
				AttackRect.left += 150;
			}
		}
		else if (state == animationState::IDLE) {
			if (WalkRect.left >= 909) {
				WalkRect.left = 0;
			}
			else {
				enemy.setTexture(walkTexture);
				enemy.setTextureRect(WalkRect);
				WalkRect.left += 65;
			}
			AttackRect.left = 0;
		}
		if (enemy.getColor() != sf::Color::White) {
			enemy.setColor(sf::Color::White);
		}
		animationTimer.restart();
	}
}

//1950

//Updates skeleton and bone positions
void Skeleton::Update(Player *player, float dt) {
	for (unsigned i = 0;i < bones.size();i++) {
		bones[i].bone.move(bones[i].velocity*bones[i].direction.x*dt,bones[i].velocity * bones[i].direction.y*dt);
		bones[i].bone.rotate(180*dt);
		if (bones[i].bone.getGlobalBounds().intersects(player->getPlayer().getGlobalBounds())) {
			std::cout << player->getName() << " took " << getAttack() << " damage!" << std::endl;
			player->setCurrentHp(player->getCurrentHp() - getAttack());
			bones.erase(bones.begin() + i);
		}
	}
	isHit(player);
	//Moves enemy in respect to player position
	if (Collision::BoundingBoxTest(enemy,player->getPlayer())){
		enemy.move(0, 0);
		if (attackTimer.getElapsedTime().asSeconds() > ((player->stopwatch)?getAttackSpeed()*2:getAttackSpeed())/2) {
			state = animationState::MELEE;
		}
	}
	else if (attackTimer.getElapsedTime().asSeconds()>((player->stopwatch) ? getAttackSpeed() * 2 : getAttackSpeed())) {
		state = animationState::RANGED;
	}
	else {
		sf::Vector2f dir = player->getPlayer().getPosition() - enemy.getPosition();
		setDirection(getUDirection(dir));
		enemy.move(getDirection().x*dt*((player->stopwatch)?getWalkspeed()/2:getWalkspeed()), getDirection().y*dt*((player->stopwatch) ? getWalkspeed() / 2 : getWalkspeed()));
	}
	//Rotates enemy based off of player position
	sf::Vector2f playerPosition = player->getPlayer().getPosition();
	float a = enemy.getPosition().x - playerPosition.x;
	float b = enemy.getPosition().y - playerPosition.y;
	float angle = -atan2(a, b) * 180 / 3.14f;
	enemy.setRotation(angle);
	walkAnim(player);
}

//Draws skeleton to window
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

//Spider Class
Spider::Spider(std::string name, int hp, float attack, float walkspeed, float attackspeed):Enemy(name,hp,attack,walkspeed,attackspeed) {
	//rectSourceSprite = sf::IntRect(0, 0, 64, 67);
	setTexture(enemy, walkTexture, "Sprites\\EnemyAnims\\Spider\\BlackWidow3.png");
	setTexture(web.web, web.texture, "Sprites\\EnemyAnims\\Skeleton\\rib.png");
	//enemy.setTextureRect(rectSourceSprite);
}

//Shoots web at player that slows
void Spider::webShot(Player *player) {
	Web w = web;
	web.direction = player->getPlayer().getPosition() - enemy.getPosition();
	web.direction = getUDirection(web.direction);
	web.web.setPosition(enemy.getPosition());
	webs.push_back(web);
}

//Damages and poisons player
void Spider::Bite(Player *player) {
	player->setCurrentHp(player->getCurrentHp() - getAttack());
	player->disables.push_back(std::pair<std::string, float>("Poison", 6.f));
	player->poisonTimer.restart();
}

//Updates spider's position
void Spider::Update(Player *player, float dt) {
	if (enemy.getColor() == sf::Color::Red) {
		enemy.setColor(sf::Color::White);
	}
	mode = (player->slowed)?Spider::behaviour::AGGRESSIVE:Spider::behaviour::PASSIVE;

	sf::Vector2f newDir = player->getPlayer().getPosition() - enemy.getPosition();
	setDirection(getUDirection(newDir));
	if (mode == Spider::behaviour::AGGRESSIVE) {
		if (Collision::PixelPerfectTest(enemy, player->getPlayer())) {
			enemy.move(0, 0);
			if (attackTimer.getElapsedTime().asSeconds() >((player->stopwatch) ? getAttackSpeed() * 2 : getAttackSpeed())) {
				Bite(player);
				attackTimer.restart();
			}
		}
		else {
			enemy.move(getDirection().x*dt*((player->stopwatch) ? getWalkspeed() / 2 : getWalkspeed()), getDirection().y*dt*((player->stopwatch) ? getWalkspeed() / 2 : getWalkspeed()));
		}
	}
	else if (mode == Spider::behaviour::PASSIVE) {
		if (attackTimer.getElapsedTime().asSeconds() >((player->stopwatch) ? getAttackSpeed() * 2 : getAttackSpeed())) {
			webShot(player);
			attackTimer.restart();
		}
	}
	for (unsigned i = 0;i < webs.size();i++) {
		webs[i].web.move(webs[i].direction.x*dt*webs[i].velocity, webs[i].direction.y*dt*webs[i].velocity);
		if (webs[i].web.getGlobalBounds().intersects(player->getPlayer().getGlobalBounds())) {
			//for(unsigned i = 0; i<player->disables.size();)
			player->disables.insert(player->disables.begin(),std::pair<std::string, float>("Slow", 3.f));
			webs.erase(webs.begin() + i);
		}
	}
	isHit(player);
	//Rotates enemy based off of player position
	sf::Vector2f playerPosition = player->getPlayer().getPosition();
	float a = enemy.getPosition().x - playerPosition.x;
	float b = enemy.getPosition().y - playerPosition.y;
	float angle = -atan2(a, b) * 180 / 3.14f;
	enemy.setRotation(angle);
}

//Draws spider to window
void Spider::Draw(sf::RenderWindow &window) {
	window.draw(enemy);
	for (unsigned i = 0; i < webs.size();i++) {
		window.draw(webs[i].web);
	}
}