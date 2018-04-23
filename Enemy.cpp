#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Collision.h"


std::vector<Enemy *> Enemy::enemies;

//Enemy Constructor
Enemy::Enemy(std::string name, int hp, float attack, float walkspeed, float attackSpeed):name(name) {
	enemy.setOrigin(20, 20);

	setHp(hp);
	setWalkspeed(walkspeed);
	setAttack(attack);
	setAttackSpeed(attackSpeed);
}

void Enemy::setPosition(LinkedMap::room* room){
    std::mt19937 gen(time(0));
    std::uniform_int_distribution<int> dis((int)(room->floor.getPosition().x - room->floor.getSize().x/2), (int)(room->floor.getPosition().x + room->floor.getSize().x/2));
    int enemyPositionX = dis(gen);

    std::uniform_int_distribution<int> dis2((int)(room->floor.getPosition().y - room->floor.getSize().y/2), (int)(room->floor.getPosition().y + room->floor.getSize().y/2));

    int enemyPositionY = dis2(gen);

	enemy.setPosition(enemyPositionX, enemyPositionY);
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
					state  = animationState::DEAD;
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
void Enemy::Spawn(Enemy *enemy, LinkedMap::room *room) {
	enemy->setPosition(room);
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
Skeleton::Skeleton(std::string name, float hp, float attack, float walkspeed, float attackspeed):Enemy(name,hp,attack,walkspeed,attackspeed) {
	WalkRect = sf::IntRect(0,0,64,67);
	AttackRect = sf::IntRect(0, 0, 110, 63);
	DeathRect = sf::IntRect(0, 0, 130, 75);

	deathTexture.loadFromFile("Sprites/EnemyAnims/Skeleton/SkeletonDeath.png");
	walkTexture.loadFromFile("Sprites/EnemyAnims/Skeleton/SkeletonWalk.png");
	attackTexture.loadFromFile("Sprites/EnemyAnims/Skeleton/SkeletonMelee.png");
	bone.texture.loadFromFile("Sprites/EnemyAnims/Skeleton/rib.png");
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
void Skeleton::Animate(Player *player) {
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
				state = animationState::WALKING;
				attackTimer.restart();
			}
			else {
				enemy.setTexture(attackTexture);
				enemy.setTextureRect(AttackRect);
				AttackRect.left += 150;
			}
		}
		else if (state == animationState::WALKING) {
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
		else if (state == animationState::DEAD) {
			enemy.setOrigin(50, 20);
			if (DeathRect.left >= 1200) {
				static sf::Clock deathTimer;
				if (deathTimer.getElapsedTime().asSeconds() > 3.f) {
					bIsDead = true;
				}
			}
			else {
				enemy.setTextureRect(DeathRect);
				enemy.setTexture(deathTexture);
				DeathRect.left += 150;
			}

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
	if (state != animationState::DEAD) {
		for (unsigned i = 0; i < bones.size(); i++) {
			bones[i].bone.move(bones[i].velocity*bones[i].direction.x*dt, bones[i].velocity * bones[i].direction.y*dt);
			bones[i].bone.rotate(180 * dt);
			if (bones[i].bone.getGlobalBounds().intersects(player->getPlayer().getGlobalBounds())) {
				std::cout << player->getName() << " took " << getAttack() << " damage!" << std::endl;
				player->setCurrentHp(player->getCurrentHp() - getAttack());
				bones.erase(bones.begin() + i);
			}
		}
		//Moves enemy in respect to player position
		if (Collision::BoundingBoxTest(enemy, player->getPlayer())) {
			enemy.move(0, 0);
			if (attackTimer.getElapsedTime().asSeconds() > ((player->stopwatch) ? getAttackSpeed() * 2 : getAttackSpeed()) / 2) {
				state = animationState::MELEE;
			}
		}
		else if (attackTimer.getElapsedTime().asSeconds() > ((player->stopwatch) ? getAttackSpeed() * 2 : getAttackSpeed())) {
			state = animationState::RANGED;
		}
		else {
			state = animationState::WALKING;
			sf::Vector2f dir = player->getPlayer().getPosition() - enemy.getPosition();
			setDirection(getUDirection(dir));
			enemy.move(getDirection().x*dt*((player->stopwatch) ? getWalkspeed() / 2 : getWalkspeed()), getDirection().y*dt*((player->stopwatch) ? getWalkspeed() / 2 : getWalkspeed()));
		}
		isHit(player);
		//Rotates enemy based off of player position
		sf::Vector2f playerPosition = player->getPlayer().getPosition();
		float a = enemy.getPosition().x - playerPosition.x;
		float b = enemy.getPosition().y - playerPosition.y;
		float angle = -atan2(a, b) * 180 / 3.14f;
		enemy.setRotation(angle);
	}
	Animate(player);
}

//Draws skeleton to window
void Skeleton::Draw(sf::RenderWindow &window) {
	window.draw(enemy);
	for (unsigned i = 0; i < bones.size() && state != animationState::DEAD;i++) {
		window.draw(bones[i].bone);
		if (bones[i].deleteTimer.getElapsedTime().asSeconds() > 3) {
			std::cout << "Deleting Bone" << std::endl;
			bones.erase(bones.begin() + i);
		}
	}
}

//Spider Class
Spider::Spider(std::string name, float hp, float attack, float walkspeed, float attackspeed):Enemy(name,hp,attack,walkspeed,attackspeed) {
	WalkRect = sf::IntRect(0, 0, 75, 70);
	DeathRect = sf::IntRect(0, 0, 75, 75);
	AttackRect = sf::IntRect(0, 0, 68, 70);
	walkTexture.loadFromFile("Sprites/EnemyAnims/Spider/SpiderWalk.png");
	deathTexture.loadFromFile("Sprites/EnemyAnims/Spider/SpiderDie.png");
	attackTexture.loadFromFile("Sprites/EnemyAnims/Spider/SpiderAttack.png");
	web.texture.loadFromFile("Sprites/EnemyAnims/Spider/webshot.png");
	web.web.setTexture(web.texture);
	web.web.setScale(.5f, .5f);
	enemy.setOrigin(20, 20);
	//enemy.setTextureRect(rectSourceSprite);
}


void Spider::Animate(Player *player) {
	if (animationTimer.getElapsedTime().asSeconds() > 0.05f) {
		if (enemy.getColor() != sf::Color::White) {
			enemy.setColor(sf::Color::White);
		}
		if (state == animationState::WALKING&&mode == behaviour::AGGRESSIVE) {
			if (WalkRect.left > 500) {
				WalkRect.left = 0;
			}
			else {
				WalkRect.left += 77;
				enemy.setTextureRect(WalkRect);
				enemy.setTexture(walkTexture);
			}
		}
		else if (state == animationState::MELEE||state==animationState::RANGED) {
			if (AttackRect.left >= 600) {
				AttackRect.left = 0;
				if (state == animationState::MELEE) {
					Bite(player);
				}
				else if (state == animationState::RANGED) {
					webShot(player);
				}
				attackTimer.restart();
				state = animationState::WALKING;
			}
			else {
				enemy.setTextureRect(AttackRect);
				enemy.setTexture(attackTexture);
				AttackRect.left += 76;
			}
		}
		else if (state == animationState::DEAD) {
			if (DeathRect.left >= 450) {
				static sf::Clock deathTimer;
				if (deathTimer.getElapsedTime().asSeconds() > 3.f) {
					bIsDead = true;
				}
			}
			else {
				enemy.setTextureRect(DeathRect);
				enemy.setTexture(deathTexture);
				DeathRect.left += 76;
			}
		}
		else {
			WalkRect.left = 0;
			enemy.setTextureRect(WalkRect);
			enemy.setTexture(walkTexture);
		}
		animationTimer.restart();
	}


}
//Shoots web at player that slows
void Spider::webShot(Player *player) {
	web.web.setRotation(enemy.getRotation());
	web.direction = player->getPlayer().getPosition() - enemy.getPosition();
	web.direction = getUDirection(web.direction);
	web.web.setPosition(enemy.getPosition()+sf::Vector2f(50*getUDirection(web.direction).x, 50 * getUDirection(web.direction).y));
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
	if (getHp() > 0) {
		
		mode = (player->slowed) ? behaviour::AGGRESSIVE : behaviour::PASSIVE;

		sf::Vector2f newDir = player->getPlayer().getPosition() - enemy.getPosition();
		setDirection(getUDirection(newDir));
		if (mode == behaviour::AGGRESSIVE) {
			if (Collision::PixelPerfectTest(enemy, player->getPlayer())) {
				enemy.move(0, 0);
				state = animationState::MELEE;
			}
			else {
				enemy.move(getDirection().x*dt*((player->stopwatch) ? getWalkspeed() / 2 : getWalkspeed()), getDirection().y*dt*((player->stopwatch) ? getWalkspeed() / 2 : getWalkspeed()));
			}
		}
		else if (mode == behaviour::PASSIVE) {
			if (attackTimer.getElapsedTime().asSeconds() >= getAttackSpeed()) {
				state = animationState::RANGED;
			}
		}
		for (unsigned i = 0; i < webs.size(); i++) {
			webs[i].web.move(webs[i].direction.x*dt*webs[i].velocity, webs[i].direction.y*dt*webs[i].velocity);
			if (webs[i].web.getGlobalBounds().intersects(player->getPlayer().getGlobalBounds())) {
				player->disables.insert(player->disables.begin(), std::pair<std::string, float>("Slow", 3.f));
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
	Animate(player);
}

//Draws spider to window
void Spider::Draw(sf::RenderWindow &window) {
	window.draw(enemy);
	for (unsigned i = 0; i < webs.size()&&state!=animationState::DEAD;i++) {
		window.draw(webs[i].web);
	}
}