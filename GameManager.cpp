#include "stdafx.h"
#include "GameManager.h"

GameManager::GameManager(int width, int length):WINDOW_LENGTH(length),WINDOW_WIDTH(width),
window(sf::VideoMode(WINDOW_WIDTH,WINDOW_LENGTH),"TrapHouse"){
	window.setSize(sf::Vector2u(WINDOW_WIDTH,WINDOW_LENGTH));
}



int GameManager::getWindowLength() {
	return WINDOW_LENGTH;
}

int GameManager::getWindowWidth() {
	return WINDOW_WIDTH;
}

void GameManager::Start() {
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == event.Closed) {
				window.close();
			}
		}
		window.clear();
		window.display();
	}
}

sf::RenderWindow& GameManager::getWindow() {
	return window;
}

GameManager::~GameManager() {

}