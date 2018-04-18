#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "ctime"
#include "cstdlib"
#include <random>


class LinkedMap {
public:
	struct hallway{
		sf::RectangleShape floor;
	};
	struct room {
		std::string name;
		bool bIsVisited;
		bool playerIsInside;
		bool isCleared();
		int neighbors = 0;
		room* neighbor1;
		room* neighbor2;
		room* neighbor3;
		room* previous;
		sf::RectangleShape floor;
		LinkedMap::hallway* hallway;

	};


	const int hallwayWidth = 40;
	LinkedMap(int);
	room* head;
	bool doesIntersect(LinkedMap::room* current);
	void addRooms(int rooms,room* current, sf::RenderWindow &);
	void displayMap(room* current, sf::RenderWindow &window);
	void printRoomNames(room* current);

private:
	std::vector<sf::RectangleShape> positions;


	int roomsToAdd;
	int count = 0;

	bool createRoom(LinkedMap::room* current, std::string, sf::RenderWindow &);
};



