
#include "LinkedMap.h"
#include "Player.h"

LinkedMap::LinkedMap(int rta) {
	if (!font.loadFromFile("Fonts/light_pixel-7.ttf")) {
		std::cout << "Could not load file" << std::endl;
	}
	srand(time(0));
	roomsToAdd = rta;
	head = new room;
	head->playerIsInside = true;
	head->bIsVisited = true;
    head->isCleared = false;
	count++;
	head->floor.setSize(sf::Vector2f(900, 900));

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

	current = head;
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
	LinkedMap::hallway* tempHallway = new hallway;
	int width = rand() % 350 + 500;
	int height = rand() % 350 + 500;
	//Creates a link between current and new neighbor for hallway
	temp->hallway = tempHallway;

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

		temp->hallway->floor.setSize(sf::Vector2f(hallwayWidth/1.78, 850));
		temp->hallway->floor.setOrigin(temp->hallway->floor.getSize().x / 2, temp->hallway->floor.getSize().y / 2);
		temp->hallway->floor.setFillColor(sf::Color::Yellow);
		temp->hallway->floor.setPosition(current->floor.getPosition().x, (current->floor.getPosition().y - (current->floor.getSize().y/2) - temp->hallway->floor.getSize().y/2));

		temp->floor.setSize(sf::Vector2f(width, height));
		temp->floor.setFillColor(sf::Color::White);
		temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
		temp->floor.setPosition(current->floor.getPosition().x, current->floor.getPosition().y - 850 - ((current->floor.getSize().y + temp->floor.getSize().y)/2));

		//DOWN ROOM
		if (doesIntersect(temp)) {

			temp->hallway->floor.setSize(sf::Vector2f(hallwayWidth/1.78, 850));
			temp->hallway->floor.setOrigin(temp->hallway->floor.getSize().x / 2, temp->hallway->floor.getSize().y / 2);
			temp->hallway->floor.setFillColor(sf::Color::Yellow);
			temp->hallway->floor.setPosition(current->floor.getPosition().x, (current->floor.getPosition().y + (current->floor.getSize().y/2) + temp->hallway->floor.getSize().y/2));

			temp->floor.setSize(sf::Vector2f(width, height));
			temp->floor.setFillColor(sf::Color::Green);
			temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
			temp->floor.setPosition(current->floor.getPosition().x, current->floor.getPosition().y + 850 + ((current->floor.getSize().y + temp->floor.getSize().y)/2));

			//LEFT ROOM
			if (doesIntersect(temp)) {

				temp->hallway->floor.setSize(sf::Vector2f(850, hallwayWidth));
				temp->hallway->floor.setOrigin(temp->hallway->floor.getSize().x / 2, temp->hallway->floor.getSize().y / 2);
				temp->hallway->floor.setFillColor(sf::Color::Yellow);
				temp->hallway->floor.setPosition(current->floor.getPosition().x - (current->floor.getSize().x/2) - (temp->hallway->floor.getSize().x/2),current->floor.getPosition().y);

				temp->floor.setSize(sf::Vector2f(width, height));
				temp->floor.setFillColor(sf::Color::Magenta);
				temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
				temp->floor.setPosition(current->floor.getPosition().x - 850 - ((current->floor.getSize().x + temp->floor.getSize().x)/2), current->floor.getPosition().y);

				//RIGHT ROOM
				if (doesIntersect(temp)) {

					temp->hallway->floor.setSize(sf::Vector2f(850, hallwayWidth));
					temp->hallway->floor.setOrigin(temp->hallway->floor.getSize().x / 2, temp->hallway->floor.getSize().y / 2);
					temp->hallway->floor.setFillColor(sf::Color::Yellow);
					temp->hallway->floor.setPosition((current->floor.getPosition().x + current->floor.getSize().x/2 + temp->hallway->floor.getSize().x/2),current->floor.getPosition().y);

					temp->floor.setSize(sf::Vector2f(width, height));
					temp->floor.setFillColor(sf::Color::Blue);
					temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
					temp->floor.setPosition(current->floor.getPosition().x + 850 + ((current->floor.getSize().x + temp->floor.getSize().x)/2), current->floor.getPosition().y);


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
		temp->hallway->floor.setSize(sf::Vector2f(hallwayWidth/1.78, 850));
		temp->hallway->floor.setOrigin(temp->hallway->floor.getSize().x / 2, temp->hallway->floor.getSize().y / 2);
		temp->hallway->floor.setFillColor(sf::Color::Yellow);
		temp->hallway->floor.setPosition(current->floor.getPosition().x, (current->floor.getPosition().y + (current->floor.getSize().y/2) + temp->hallway->floor.getSize().y/2));

		temp->floor.setSize(sf::Vector2f(width, height));
		temp->floor.setFillColor(sf::Color::Green);
		temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
		temp->floor.setPosition(current->floor.getPosition().x, current->floor.getPosition().y + 850 + ((current->floor.getSize().y + temp->floor.getSize().y)/2));

		//UP ROOM
		if (doesIntersect(temp)) {
			temp->hallway->floor.setSize(sf::Vector2f(hallwayWidth/1.78, 850));
			temp->hallway->floor.setOrigin(temp->hallway->floor.getSize().x / 2, temp->hallway->floor.getSize().y / 2);
			temp->hallway->floor.setFillColor(sf::Color::Yellow);
			temp->hallway->floor.setPosition(current->floor.getPosition().x, (current->floor.getPosition().y - (current->floor.getSize().y/2) - temp->hallway->floor.getSize().y/2));

			temp->floor.setSize(sf::Vector2f(width, height));
			temp->floor.setFillColor(sf::Color::White);
			temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
			temp->floor.setPosition(current->floor.getPosition().x, current->floor.getPosition().y - 850 - ((current->floor.getSize().y + temp->floor.getSize().y)/2));
			//LEFT ROOM
			if (doesIntersect(temp)) {
				temp->hallway->floor.setSize(sf::Vector2f(850, hallwayWidth));
				temp->hallway->floor.setOrigin(temp->hallway->floor.getSize().x / 2, temp->hallway->floor.getSize().y / 2);
				temp->hallway->floor.setFillColor(sf::Color::Yellow);
				temp->hallway->floor.setPosition(current->floor.getPosition().x - (current->floor.getSize().x/2) - (temp->hallway->floor.getSize().x/2),current->floor.getPosition().y);

				temp->floor.setSize(sf::Vector2f(width, height));
				temp->floor.setFillColor(sf::Color::Magenta);
				temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
				temp->floor.setPosition(current->floor.getPosition().x - 850 - ((current->floor.getSize().x + temp->floor.getSize().x)/2), current->floor.getPosition().y);


				//RIGHT ROOM
				if (doesIntersect(temp)) {
					temp->hallway->floor.setSize(sf::Vector2f(850, hallwayWidth));
					temp->hallway->floor.setOrigin(temp->hallway->floor.getSize().x / 2, temp->hallway->floor.getSize().y / 2);
					temp->hallway->floor.setFillColor(sf::Color::Yellow);
					temp->hallway->floor.setPosition((current->floor.getPosition().x + current->floor.getSize().x/2 + temp->hallway->floor.getSize().x/2),current->floor.getPosition().y);

					temp->floor.setSize(sf::Vector2f(width, height));
					temp->floor.setFillColor(sf::Color::Blue);
					temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
					temp->floor.setPosition(current->floor.getPosition().x + 850 + ((current->floor.getSize().x + temp->floor.getSize().x)/2), current->floor.getPosition().y);
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
		temp->hallway->floor.setSize(sf::Vector2f(850, hallwayWidth));
		temp->hallway->floor.setOrigin(temp->hallway->floor.getSize().x / 2, temp->hallway->floor.getSize().y / 2);
		temp->hallway->floor.setFillColor(sf::Color::Yellow);
		temp->hallway->floor.setPosition(current->floor.getPosition().x - (current->floor.getSize().x/2) - (temp->hallway->floor.getSize().x/2),current->floor.getPosition().y);

		temp->floor.setSize(sf::Vector2f(width, height));
		temp->floor.setFillColor(sf::Color::Magenta);
		temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
		temp->floor.setPosition(current->floor.getPosition().x - 850 - ((current->floor.getSize().x + temp->floor.getSize().x)/2), current->floor.getPosition().y);

		//DOWN ROOM
		if (doesIntersect(temp)) {
			temp->hallway->floor.setSize(sf::Vector2f(hallwayWidth/1.78, 850));
			temp->hallway->floor.setOrigin(temp->hallway->floor.getSize().x / 2, temp->hallway->floor.getSize().y / 2);
			temp->hallway->floor.setFillColor(sf::Color::Yellow);
			temp->hallway->floor.setPosition(current->floor.getPosition().x, (current->floor.getPosition().y + (current->floor.getSize().y/2) + temp->hallway->floor.getSize().y/2));

			temp->floor.setSize(sf::Vector2f(width, height));
			temp->floor.setFillColor(sf::Color::Green);
			temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
			temp->floor.setPosition(current->floor.getPosition().x, current->floor.getPosition().y + 850 + ((current->floor.getSize().y + temp->floor.getSize().y)/2));

			//UP ROOM
			if (doesIntersect(temp)) {
				temp->hallway->floor.setSize(sf::Vector2f(hallwayWidth/1.78, 850));
				temp->hallway->floor.setOrigin(temp->hallway->floor.getSize().x / 2, temp->hallway->floor.getSize().y / 2);
				temp->hallway->floor.setFillColor(sf::Color::Yellow);
				temp->hallway->floor.setPosition(current->floor.getPosition().x, (current->floor.getPosition().y - (current->floor.getSize().y/2) - temp->hallway->floor.getSize().y/2));

				temp->floor.setSize(sf::Vector2f(width, height));
				temp->floor.setFillColor(sf::Color::White);
				temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
				temp->floor.setPosition(current->floor.getPosition().x, current->floor.getPosition().y - 850 - ((current->floor.getSize().y + temp->floor.getSize().y)/2));

				//RIGHT ROOM
				if (doesIntersect(temp)) {
					temp->hallway->floor.setSize(sf::Vector2f(850, hallwayWidth));
					temp->hallway->floor.setOrigin(temp->hallway->floor.getSize().x / 2, temp->hallway->floor.getSize().y / 2);
					temp->hallway->floor.setFillColor(sf::Color::Yellow);
					temp->hallway->floor.setPosition((current->floor.getPosition().x + current->floor.getSize().x/2 + temp->hallway->floor.getSize().y/2),current->floor.getPosition().y);

					temp->floor.setSize(sf::Vector2f(width, height));
					temp->floor.setFillColor(sf::Color::Blue);
					temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
					temp->hallway->floor.setPosition((current->floor.getPosition().x + current->floor.getSize().x/2 + temp->hallway->floor.getSize().x/2),current->floor.getPosition().y);
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
		temp->hallway->floor.setSize(sf::Vector2f(850, hallwayWidth));
		temp->hallway->floor.setOrigin(temp->hallway->floor.getSize().x / 2, temp->hallway->floor.getSize().y / 2);
		temp->hallway->floor.setFillColor(sf::Color::Yellow);
		temp->hallway->floor.setPosition((current->floor.getPosition().x + current->floor.getSize().x/2 + temp->hallway->floor.getSize().x/2),current->floor.getPosition().y);

		temp->floor.setSize(sf::Vector2f(width, height));
		temp->floor.setFillColor(sf::Color::Blue);
		temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
		temp->floor.setPosition(current->floor.getPosition().x + 850 + ((current->floor.getSize().x + temp->floor.getSize().x)/2), current->floor.getPosition().y);

		//LEFT ROOM
		if (doesIntersect(temp)) {
			temp->hallway->floor.setSize(sf::Vector2f(850, hallwayWidth));
			temp->hallway->floor.setOrigin(temp->hallway->floor.getSize().x / 2, temp->hallway->floor.getSize().y / 2);
			temp->hallway->floor.setFillColor(sf::Color::Yellow);
			temp->hallway->floor.setPosition(current->floor.getPosition().x - (current->floor.getSize().x/2) - (temp->hallway->floor.getSize().x/2),current->floor.getPosition().y);

			temp->floor.setSize(sf::Vector2f(width, height));
			temp->floor.setFillColor(sf::Color::Magenta);
			temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
			temp->floor.setPosition(current->floor.getPosition().x - 850 - ((current->floor.getSize().x + temp->floor.getSize().x)/2), current->floor.getPosition().y);

			//DOWN ROOM
			if (doesIntersect(temp)) {
				temp->hallway->floor.setSize(sf::Vector2f(hallwayWidth/1.78, 850));
				temp->hallway->floor.setOrigin(temp->hallway->floor.getSize().x / 2, temp->hallway->floor.getSize().y / 2);
				temp->hallway->floor.setFillColor(sf::Color::Yellow);
				temp->hallway->floor.setPosition(current->floor.getPosition().x, (current->floor.getPosition().y + (current->floor.getSize().y/2) + temp->hallway->floor.getSize().y/2));

				temp->floor.setSize(sf::Vector2f(width, height));
				temp->floor.setFillColor(sf::Color::Green);
				temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
				temp->floor.setPosition(current->floor.getPosition().x, current->floor.getPosition().y + 850 + ((current->floor.getSize().y + temp->floor.getSize().y)/2));

				//UP ROOM
				if (doesIntersect(temp)) {
					temp->hallway->floor.setSize(sf::Vector2f(hallwayWidth/1.78, 850));
					temp->hallway->floor.setOrigin(temp->hallway->floor.getSize().x / 2, temp->hallway->floor.getSize().y / 2);
					temp->hallway->floor.setFillColor(sf::Color::Yellow);
					temp->hallway->floor.setPosition(current->floor.getPosition().x, (current->floor.getPosition().y - (current->floor.getSize().y/2) - temp->hallway->floor.getSize().y/2));

					temp->floor.setSize(sf::Vector2f(width, height));
					temp->floor.setFillColor(sf::Color::White);
					temp->floor.setOrigin(temp->floor.getSize().x / 2, temp->floor.getSize().y / 2);
					temp->floor.setPosition(current->floor.getPosition().x, current->floor.getPosition().y - 850 - ((current->floor.getSize().y + temp->floor.getSize().y)/2));

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

	if (rooms <= 0||current == nullptr) {
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
		if(current->neighbor1->bIsVisited) {
			window.draw(current->neighbor1->floor);
			window.draw(current->neighbor1->hallway->floor);

		} else if (current->bIsVisited){
			window.draw(current->neighbor1->hallway->floor);
		}
		if (current->neighbor1->neighbors>0) {
			displayMap(current->neighbor1, window);
		}
	}
	if (current->neighbor2 != nullptr){
		if(current->neighbor2->bIsVisited) {
			window.draw(current->neighbor2->floor);
			window.draw(current->neighbor2->hallway->floor);
		} else if(current->bIsVisited){
			window.draw(current->neighbor2->hallway->floor);
		}

		if (current->neighbor2->neighbors>0) {
			displayMap(current->neighbor2, window);
		}

	}
	if (current->neighbor3 != nullptr) {
		if(current->neighbor1->bIsVisited) {
			window.draw(current->neighbor3->floor);
			window.draw(current->neighbor3->hallway->floor);

		} else if(current->bIsVisited){
			window.draw(current->neighbor3->hallway->floor);
		}

		if (current->neighbor3->neighbors>0) {
			displayMap(current->neighbor3, window);
		}
	}
}

void LinkedMap::displayCurrentRoom(sf::RenderWindow &window) {
	if (current != nullptr) {
		window.draw(current->floor);
		if (current != head) {
			window.draw(current->hallway->floor);
		}
	}
	if (current->previous != nullptr) {
		window.draw(current->previous->floor);
		if (current->previous != head) {
			window.draw(current->previous->hallway->floor);
		}
		if (current->previous->neighbor1 != nullptr) {
			window.draw(current->previous->neighbor1->floor);
			if (current->previous->neighbor1 != head) {
				window.draw(current->previous->neighbor1->hallway->floor);

			}
		}
		if (current->previous->neighbor2 != nullptr) {
			window.draw(current->previous->neighbor2->floor);
			if (current->previous->neighbor2 != head) {
				window.draw(current->previous->neighbor2->hallway->floor);
			}
		}
		if (current->previous->neighbor3 != nullptr) {
			window.draw(current->previous->neighbor3->floor);
			if (current->previous->neighbor3 != head) {
				window.draw(current->previous->neighbor3->hallway->floor);

			}
		}
	}
	if (current->neighbor1 != nullptr) {
		window.draw(current->neighbor1->floor);
		window.draw(current->neighbor1->hallway->floor);
		if (current->neighbor1->neighbor1 != nullptr) {
			window.draw(current->neighbor1->neighbor1->hallway->floor);
			window.draw(current->neighbor1->neighbor1->floor);
		}
		if (current->neighbor1->neighbor2 != nullptr) {
			window.draw(current->neighbor1->neighbor2->hallway->floor);
			window.draw(current->neighbor1->neighbor2->floor);
		}
		if (current->neighbor1->neighbor3 != nullptr) {
			window.draw(current->neighbor1->neighbor3->hallway->floor);
			window.draw(current->neighbor1->neighbor3->floor);
		}
	}
	if (current->neighbor2 != nullptr) {
		window.draw(current->neighbor2->floor);
		window.draw(current->neighbor2->hallway->floor);
		if (current->neighbor2->neighbor1 != nullptr) {
			window.draw(current->neighbor2->neighbor1->hallway->floor);
			window.draw(current->neighbor2->neighbor1->floor);
		}
		if (current->neighbor2->neighbor2 != nullptr) {
			window.draw(current->neighbor2->neighbor2->hallway->floor);
			window.draw(current->neighbor2->neighbor2->floor);
			if (current->neighbor2->neighbor3 != nullptr) {
				window.draw(current->neighbor2->neighbor3->hallway->floor);
				window.draw(current->neighbor2->neighbor3->floor);
			}
		}
	}
	if (current->neighbor3 != nullptr) {
		window.draw(current->neighbor3->floor);
		window.draw(current->neighbor3->hallway->floor);
		if (current->neighbor3->neighbor1 != nullptr) {
			window.draw(current->neighbor3->neighbor1->hallway->floor);
			window.draw(current->neighbor3->neighbor1->floor);
		}
		if (current->neighbor3->neighbor2 != nullptr) {
			window.draw(current->neighbor3->neighbor2->hallway->floor);
			window.draw(current->neighbor3->neighbor2->floor);
		}
		if (current->neighbor3->neighbor3 != nullptr) {
			window.draw(current->neighbor3->neighbor3->hallway->floor);
			window.draw(current->neighbor3->neighbor3->floor);
		}
	}
}

void LinkedMap::getNextLevel(room* current){
    if (current->neighbor2 != nullptr) {
        if(current->neighbor2->neighbors == 0){
            levelUpRoom = current->neighbor2;
        } else{
            getNextLevel(current->neighbor2);
        }
    }
    if (current->neighbor3 != nullptr) {
		if(current->neighbor3->neighbors == 0){

			levelUpRoom = current->neighbor3;

		} else{
			getNextLevel(current->neighbor3);
		}
    }
    if (current->neighbor1 != nullptr) {
    	if(current->neighbor1->neighbors == 0){
			levelUpRoom = current->neighbor1;
		} else{
			getNextLevel(current->neighbor1);
		}
    }
}

void LinkedMap::spawnNextLevel(){

	if (texture.loadFromFile("Sprites/Map/Stairs.png")) {
		stairs.setTexture(texture);
	}
	stairs.setOrigin(stairs.getGlobalBounds().width/2,stairs.getGlobalBounds().height/2);
    stairs.setPosition(levelUpRoom->floor.getPosition());
}

void LinkedMap::setLevelUpText(){
	levelUpText.setFont(font);
	levelUpText.setCharacterSize(24);
	levelUpText.setString("Press 'F' To Level Up");
	levelUpText.setPosition(stairs.getPosition().x + 40,stairs.getPosition().y + 40);
}


bool LinkedMap::displayStairs(sf::RenderWindow &window, Player* player){
    window.draw(stairs);
    if(player->getPlayer().getGlobalBounds().intersects(stairs.getGlobalBounds())){

		window.draw(levelUpText);
		return true;
    }
    return false;
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

//Method determines which rooms have been visited, which room the player is currently in and whether or not a room is cleared
void LinkedMap::findCurrentRoom(room* checkedRoom, Player* player){

    if(checkedRoom == head){

		if (checkedRoom->floor.getGlobalBounds().intersects(player->getPlayer().getGlobalBounds())) {
			if (!checkedRoom->bIsVisited) {
				checkedRoom->bIsVisited = true;
				checkedRoom->isCleared = false;
			}
			checkedRoom->playerIsInside = true;
			current = checkedRoom;
		}
		else {
			checkedRoom->playerIsInside = false;
		}
	}

	if (checkedRoom->neighbor1 != nullptr) {

		if (checkedRoom->neighbor1->floor.getGlobalBounds().intersects(player->getPlayer().getGlobalBounds())) {
			if (!checkedRoom->neighbor1->bIsVisited) {
				checkedRoom->neighbor1->bIsVisited = true;
				checkedRoom->neighbor1->isCleared = false;
			}
			checkedRoom->neighbor1->playerIsInside = true;
			current = checkedRoom->neighbor1;
			return;
		}
		else {
			checkedRoom->neighbor1->playerIsInside = false;
		}
		if (checkedRoom->neighbor1->neighbors>0) {
			findCurrentRoom(checkedRoom->neighbor1, player);
		}
	}

	if (checkedRoom->neighbor2 != nullptr) {
		if (checkedRoom->neighbor2->floor.getGlobalBounds().intersects(player->getPlayer().getGlobalBounds())) {
			if (!checkedRoom->neighbor2->bIsVisited) {
				checkedRoom->neighbor2->bIsVisited = true;
				checkedRoom->neighbor2->isCleared = false;
			}
			checkedRoom->neighbor2->playerIsInside = true;
			current = checkedRoom->neighbor2;
			return;
		}
		else {
			checkedRoom->neighbor2->playerIsInside = false;
		}

        if (checkedRoom->neighbor2->neighbors>0) {
            findCurrentRoom(checkedRoom->neighbor2, player);
        }
    }
    if (checkedRoom->neighbor3 != nullptr) {

		if (checkedRoom->neighbor3->floor.getGlobalBounds().intersects(player->getPlayer().getGlobalBounds())) {
			if (!checkedRoom->neighbor3->bIsVisited) {
				checkedRoom->neighbor3->bIsVisited = true;
				checkedRoom->neighbor3->isCleared = false;
			}
			checkedRoom->neighbor3->playerIsInside = true;
			current = checkedRoom->neighbor3;
			return;
		}
		else {
			checkedRoom->neighbor3->playerIsInside = false;
		}

        if (checkedRoom->neighbor3->neighbors>0) {
            findCurrentRoom(checkedRoom->neighbor3, player);
        }
    }
    if (checkedRoom->neighbor1 != nullptr) {

        if(checkedRoom->neighbor1->floor.getGlobalBounds().intersects(player->getPlayer().getGlobalBounds())){
            current = checkedRoom->neighbor1;
            checkedRoom->neighbor1->bIsVisited = true;
            checkedRoom->neighbor1->playerIsInside = true;
            return;
        } else{
            checkedRoom->neighbor1->playerIsInside = false;
        }
        if (checkedRoom->neighbor1->neighbors>0) {
            findCurrentRoom(checkedRoom->neighbor1, player);
        }
    }
}
//returns current room
LinkedMap::room* LinkedMap::getCurrentRoom(){
    return(current);
}

LinkedMap::room* LinkedMap::getHead(){
    return(head);
}

LinkedMap::room* LinkedMap::getLevelUpRoom(){
    return(levelUpRoom);
}
