////#include "stdafx.h"
#include "LinkedMap.h"


LinkedMap::LinkedMap(int rta) {

	srand(time(0));
	roomsToAdd = rta;
	head = new room;
	head->playerIsInside = true;
	head->bIsVisited = true;

	count++;
	head->floor.setSize(sf::Vector2f(500, 500));

	head->floor.setOrigin(head->floor.getSize().x / 2, head->floor.getSize().y / 2);
	head->floor.setPosition(0, 0);

	positions.push_back(head->floor);
	head->floor.setFillColor(sf::Color::Red);
	head->neighbor1 = nullptr;
	head->neighbor2 = nullptr;
	head->neighbor3 = nullptr;
	head->previous = nullptr;
	head->name = "HEAD";
	std::cout << "Adding room 1" << std::endl;

}

bool LinkedMap::doesIntersect(LinkedMap::room* current) {
	for (unsigned i = 0;i < positions.size();i++) {
		if (current->floor.getGlobalBounds().intersects(positions[i].getGlobalBounds())) {
			return true;
		}
	}
	return false;
}

bool LinkedMap::createRoom(LinkedMap::room* current,std::string dir,sf::RenderWindow &window) {
	LinkedMap::room* temp = new room;
	//sets 3 branches to null and previous branch to current
	temp->neighbor1 = nullptr;
	temp->neighbor2 = nullptr;
	temp->neighbor3 = nullptr;
	temp->previous = current;

	//Gives information about size, color and placement of room
	temp->playerIsInside = false;
	temp->bIsVisited = false;
	//Up room
	if (dir == "Up") {
		temp->floor.setSize(sf::Vector2f(150, 150));
		temp->floor.setFillColor(sf::Color::White);
		temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
		temp->floor.setPosition(current->floor.getPosition().x, current->floor.getPosition().y - 600);
		if (doesIntersect(temp)) {
			temp->floor.setSize(sf::Vector2f(225, 225));
			temp->floor.setFillColor(sf::Color::Green);
			temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
			temp->floor.setPosition(current->floor.getPosition().x, current->floor.getPosition().y + 600);
			if (doesIntersect(temp)) {
				temp->floor.setSize(sf::Vector2f(175, 175));
				temp->floor.setFillColor(sf::Color::Magenta);
				temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
				temp->floor.setPosition(current->floor.getPosition().x - 600, current->floor.getPosition().y);
				if (doesIntersect(temp)) {
					temp->floor.setSize(sf::Vector2f(200, 200));
					temp->floor.setFillColor(sf::Color::Blue);
					temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
					temp->floor.setPosition((current->floor.getPosition().x + 600), current->floor.getPosition().y);
					if (doesIntersect(temp)) {
						std::cout << "Overlap" << std::endl;
						addRooms(roomsToAdd - count, current->previous, window);
						return false;
					}
				}
			}
		}
	}
	//Down room
	if (dir == "Down") {
		temp->floor.setSize(sf::Vector2f(225, 225));
		temp->floor.setFillColor(sf::Color::Green);
		temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
		temp->floor.setPosition(current->floor.getPosition().x, current->floor.getPosition().y + 600);
		if (doesIntersect(temp)) {
			temp->floor.setSize(sf::Vector2f(150, 150));
			temp->floor.setFillColor(sf::Color::White);
			temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
			temp->floor.setPosition(current->floor.getPosition().x, current->floor.getPosition().y - 600);
			if (doesIntersect(temp)) {
				temp->floor.setSize(sf::Vector2f(175, 175));
				temp->floor.setFillColor(sf::Color::Magenta);
				temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
				temp->floor.setPosition(current->floor.getPosition().x - 600, current->floor.getPosition().y);
				if (doesIntersect(temp)) {
					temp->floor.setSize(sf::Vector2f(200, 200));
					temp->floor.setFillColor(sf::Color::Blue);
					temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
					temp->floor.setPosition((current->floor.getPosition().x + 600), current->floor.getPosition().y);
					if (doesIntersect(temp)) {
						std::cout << "Overlap" << std::endl;
						addRooms(roomsToAdd - count, current->previous, window);
						return false;
					}
				}
			}
		}
	}
	//Left room
	if (dir == "Left") {
		temp->floor.setSize(sf::Vector2f(175, 175));
		temp->floor.setFillColor(sf::Color::Magenta);
		temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
		temp->floor.setPosition(current->floor.getPosition().x - 600, current->floor.getPosition().y);
		if (doesIntersect(temp)) {
			temp->floor.setSize(sf::Vector2f(225, 225));
			temp->floor.setFillColor(sf::Color::Green);
			temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
			temp->floor.setPosition(current->floor.getPosition().x, current->floor.getPosition().y + 600);
			if (doesIntersect(temp)) {
				temp->floor.setSize(sf::Vector2f(150, 150));
				temp->floor.setFillColor(sf::Color::White);
				temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
				temp->floor.setPosition(current->floor.getPosition().x, current->floor.getPosition().y - 600);
				if (doesIntersect(temp)) {
					temp->floor.setSize(sf::Vector2f(200, 200));
					temp->floor.setFillColor(sf::Color::Blue);
					temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
					temp->floor.setPosition((current->floor.getPosition().x + 600), current->floor.getPosition().y);
					if (doesIntersect(temp)) {
						std::cout << "Overlap" << std::endl;
						addRooms(roomsToAdd - count, current->previous, window);
						return false;
					}
				}
			}
		}
	}
	//Right room
	if (dir == "Right") {
		temp->floor.setSize(sf::Vector2f(200, 200));
		temp->floor.setFillColor(sf::Color::Blue);
		temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
		temp->floor.setPosition((current->floor.getPosition().x + 600), current->floor.getPosition().y);
		if (doesIntersect(temp)) {
			temp->floor.setSize(sf::Vector2f(175, 175));
			temp->floor.setFillColor(sf::Color::Magenta);
			temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
			temp->floor.setPosition(current->floor.getPosition().x - 600, current->floor.getPosition().y);
			if (doesIntersect(temp)) {
				temp->floor.setSize(sf::Vector2f(225, 225));
				temp->floor.setFillColor(sf::Color::Green);
				temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
				temp->floor.setPosition(current->floor.getPosition().x, current->floor.getPosition().y + 600);
				if (doesIntersect(temp)) {
					temp->floor.setSize(sf::Vector2f(150, 150));
					temp->floor.setFillColor(sf::Color::White);
					temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
					temp->floor.setPosition(current->floor.getPosition().x, current->floor.getPosition().y - 600);
					if (doesIntersect(temp)) {
						std::cout << "Overlap" << std::endl;
						addRooms(roomsToAdd - count, current->previous,window);
						return false;
					}
				}
			}
		}
	}
	temp->name = "room " + std::to_string(count++);

	if (current->neighbor1 == nullptr) {
		current->neighbor1 = temp;
	}
	else if (current->neighbor2 == nullptr) {
		current->neighbor2 = temp;
	}
	else if (current->neighbor3 == nullptr) {
		current->neighbor3 = temp;
	}
	std::cout << "Adding room " << count << std::endl;
	positions.push_back(temp->floor);
	window.clear();
	displayMap(head, window);
	window.display();
	return true;
}




void LinkedMap::addRooms(int rooms, room* current, sf::RenderWindow &window) {

	room *temp = new room;
	if (rooms <= 0) {
		return;
	}
	int neighbors = rand() % 3 + 1;
	if (current->neighbors == 0) {
		current->neighbors = neighbors;
		for (int i = 0;i < neighbors&&rooms>0;i++) {
			int r = rand() % 3;
			switch (r) {
			case 0:
				if (!createRoom(current, "Up", window))
					return;
				break;
			case 1:
				if (!createRoom(current, "Left", window))
					return;
				break;
			case 2:
				if (!createRoom(current, "Down", window))
					return;
				break;
			case 3:
				if (!createRoom(current, "Right", window))
					return;
			default:
				break;
			}
			rooms--;
		}
		int r = 0;
		if (neighbors == 1) {
			addRooms(rooms, current->neighbor1, window);
		}
		else if (neighbors == 2) {
			if (rooms == 1) {
				r = 1;
			}
			else if (rooms <= 0) {
				r = 0;
			}
			else {
				r = rand() % (rooms - 1) + 1;
			}
			addRooms(r, current->neighbor1, window);
			addRooms(rooms - r, current->neighbor2, window);
		}
		else if (neighbors == 3) {
			if (rooms == 1) {
				r = 1;
			}
			else if (rooms <= 0) {
				r = 0;
			}
			else {
				r = rand() % (rooms - 1) + 1;
			}
			addRooms(r, current->neighbor1, window);
			rooms -= r;
			if (rooms == 1) {
				r = 1;
			}
			else if (rooms <= 0) {
				r = 0;
			}
			else {
				r = rand() % (rooms - 1) + 1;
			}
			addRooms(r, current->neighbor2, window);
			addRooms(rooms - r, current->neighbor3, window);
		}
	}
	else if(current->neighbors<3) {
		neighbors = 3-current->neighbors;
		for (int i = 0;i < neighbors&&rooms>0;i++) {
			int r = rand() % 3;
			switch (r) {
			case 0:
				if (!createRoom(current, "Up", window))
					return;
				break;
			case 1:
				if (!createRoom(current, "Left", window))
					return;
				break;
			case 2:
				if (!createRoom(current, "Down", window))
					return;
				break;
			case 3:
				if (!createRoom(current, "Right", window))
					return;
			default:
				break;
			}
			rooms--;
		}
		int r = 0;
		if (neighbors == 1) {
			addRooms(rooms, current->neighbor3, window);
		}
		else if (neighbors == 2) {
			if (rooms == 1) {
				r = 1;
			}
			else if (rooms <= 0) {
				r = 0;
			}
			else {
				r = rand() % (rooms - 1) + 1;
			}
			addRooms(r, current->neighbor2, window);
			addRooms(rooms - r, current->neighbor3, window);
		}
		else {
			std::cout << "THIS SHOULDN'T HAPPEN" << std::endl;
		}
	}
	else {
		return;
	}
}

void LinkedMap::displayMap(room* current, sf::RenderWindow &window) {
	if (current == head) {
		window.draw(current->floor);
	}
	if (current->neighbor1 != nullptr) {
		window.draw(current->neighbor1->floor);

		if (current->neighbor1->neighbors>0) {
			displayMap(current->neighbor1, window);
		}
	}
	if (current->neighbor2 != nullptr) {

		window.draw(current->neighbor2->floor);

		if (current->neighbor2->neighbors>0) {
			displayMap(current->neighbor2, window);
		}
	}
	if (current->neighbor3 != nullptr) {

		window.draw(current->neighbor3->floor);

		if (current->neighbor3->neighbors>0) {
			displayMap(current->neighbor3, window);
		}
	}
}

void LinkedMap::printRoomNames(room* current) {

	if (current->neighbor2 != nullptr) {
		std::cout << current->neighbor2->name<<std::endl;

		if (current->neighbor2->neighbors>0) {
			printRoomNames(current->neighbor2);
		}
	}

	if (current->neighbor3 != nullptr) {
		std::cout << current->neighbor3->name << std::endl;
		if (current->neighbor3->neighbors>0) {
			printRoomNames(current->neighbor3);
		}
	}

	if (current->neighbor1 != nullptr) {

		std::cout << current->neighbor1->name << std::endl;

		if (current->neighbor1->neighbors>0) {
			printRoomNames(current->neighbor1);
		}
	}

}
