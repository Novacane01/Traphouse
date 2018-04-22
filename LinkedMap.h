#pragma once
#include "SFML/Graphics.hpp"
#include "ctime"
#include "cstdlib"
#include <random>
#include <iostream>

class Player;
class LinkedMap {
public:
	struct hallway{
		sf::RectangleShape floor;
	};
	struct room {
		std::string name;
		bool bIsVisited;
		bool playerIsInside;
		bool isCleared = false;
		int neighbors = 0;
		room* neighbor1;
		room* neighbor2;
		room* neighbor3;
		room* previous;
		sf::RectangleShape floor;
		LinkedMap::hallway* hallway;


	};


	const int hallwayWidth = 150;
	LinkedMap(int);
	room* head;


	bool doesIntersect(LinkedMap::room* current);
	void addRooms(int rooms,room* current, sf::RenderWindow &);
	void displayMap(room* current, sf::RenderWindow &window);
	void displayCurrentRoom(sf::RenderWindow &window);
	void printRoomNames(room* current);
    LinkedMap::room* getCurrentRoom();
    LinkedMap::room* getHead();
    LinkedMap::room* getLevelUpRoom();
    void findCurrentRoom(LinkedMap::room*, Player* player);

    //Gets room on map that will contain staircase to level up
    void getNextLevel(room* current);
    //Spawns staircase in level up room
    void spawnNextLevel();
    bool displayStairs(sf::RenderWindow &window, Player* player);
    void setLevelUpText();
private:
    //list of all rectangle shapes added to check for intersections as rooms are made
    std::vector<sf::RectangleShape> positions;
    sf::Sprite stairs;
    room* current = nullptr;
    room* levelUpRoom = nullptr;

    int roomsToAdd;
	int count = 0;
    sf::Texture texture;
    sf::Text levelUpText;
    sf::Font font;


	bool createRoom(LinkedMap::room* current, std::string, sf::RenderWindow &);
};



