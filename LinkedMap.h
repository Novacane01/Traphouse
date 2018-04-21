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
	void printRoomNames(room* current);
    LinkedMap::room* getCurrentRoom();
    void findCurrentRoom(LinkedMap::room*, Player* player);
    void setCurrentRoom();
private:
	std::vector<sf::RectangleShape> positions;

    room* current = nullptr;
	int roomsToAdd;
	int count = 0;


	bool createRoom(LinkedMap::room* current, std::string, sf::RenderWindow &);
};



