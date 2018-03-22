#include "GameManager.h"

GameManager::GameManager(int width, int length) {
	setWindowWidth(width);
	setWindowLength(length);
}


void GameManager::setWindowLength(int value) {
	WINDOW_LENGTH = value;
}

void GameManager::setWindowWidth(int value) {
	WINDOW_WIDTH = value;
}

int GameManager::getWindowLength() {
	return WINDOW_LENGTH;
}

int GameManager::getWindowWidth() {
	return WINDOW_WIDTH;
}

void GameManager::Start() {

}

sf::RenderWindow& GameManager::getWindow() {
	/*return window;*/
}