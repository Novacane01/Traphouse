#include "stdafx.h"
#include "GameManager.h"
#include "Player.h"

GameManager::GameManager(int width, int length){
	setWindowLength(length);
	setWindowWidth(width);
}

void GameManager::setWindowLength(int value) {
	WINDOW_LENGTH = value;
}


void GameManager::setWindowWidth(int value) {
	WINDOW_WIDTH = value;
}


void GameManager::Start() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_LENGTH), "Traphouse");
	sf::Clock FPSclock;
	Player *player = new Player("John Doe",100,10,50);
	player->setTexture("C:\\Users\\Novacane\\Pictures\\2.jpg");
	player->setSprite();
	player->player.setPosition(400, 400);
	while (window.isOpen()) {
		double deltaTime = FPSclock.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == event.Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::W) {
					player->isMovingUp = true;
					std::cout << "Up" << std::endl;
				}
				if (event.key.code == sf::Keyboard::A) {
					player->isMovingLeft = true;
				}
				if (event.key.code == sf::Keyboard::S) {
					player->isMovingDown = true;
				}
				if (event.key.code == sf::Keyboard::D) {
					player->isMovingRight = true;
				}
			}
			else if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::W) {
					player->isMovingUp = false;
				}
				if (event.key.code == sf::Keyboard::A) {
					player->isMovingLeft = false;
				}
				if (event.key.code == sf::Keyboard::S) {
					player->isMovingDown = false;
				}
				if (event.key.code == sf::Keyboard::D) {
					player->isMovingRight = false;
				}
			}
		}
		window.clear();
		player->Update(deltaTime);
		window.draw(player->player);
		window.display();
	}
}

GameManager::~GameManager() {

}