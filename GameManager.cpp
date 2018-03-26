#include "stdafx.h"
#include "GameManager.h"


//Game Manager Constructor
GameManager::GameManager(int width, int length){
	setWindowLength(length);
	setWindowWidth(width);
}

//Sets window length
void GameManager::setWindowLength(int value) {
	WINDOW_LENGTH = value;
}

//Sets window width
void GameManager::setWindowWidth(int value) {
	WINDOW_WIDTH = value;
}

//Starts The Game
void GameManager::Start() {
	//Creates Window with size WINDOW_WITDTH x WINDOW_LENGTH
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_LENGTH), "Traphouse");

	window.setKeyRepeatEnabled(false); //Disables repeated keypresses
	window.setVerticalSyncEnabled(false); //Limits refresh rate to monitor

	//Initializes clock to record frames per second
	sf::Clock FPSclock;

	//Creates player object
	Player* player = createPlayer(window);
	//Creates bounded Map rectangle object
	Map map;

	//Main loop
	while (window.isOpen()) {
		float deltaTime = FPSclock.restart().asSeconds();

		//Records window events such as mouse movement, mouse clicks, and key strokes
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == event.Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::W) {
					player->isMovingUp = true;
					
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
			else if (event.type == sf::Event::MouseWheelScrolled) {
				player->switchWeapons();
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					std::cout << "Left mouse clicked" << std::endl;
					player->getCurrentWeapon().Shoot(player,window);
				}
			}
		}
		window.clear(); //Clears window
		window.draw(map.map); //Draws map
		player->Update(window, deltaTime, map.collisionTest(player)); //Updates player position
		player->Draw(window); //Draws player to screen
		player->getCurrentWeapon().Update(window,player,deltaTime); //Updates weapon and bullets
		window.display(); //Displays all drawn objects

	}
}

Player* GameManager::createPlayer(sf::RenderWindow &window) {
	window.setKeyRepeatEnabled(true);
	bool created = false;

	//Creates textbox
	sf::RectangleShape textBox(sf::Vector2f(250, 50));
	textBox.setPosition(WINDOW_WIDTH / 2.f - textBox.getSize().x/2.f, WINDOW_LENGTH / 2.f - textBox.getSize().y/2.f);
	textBox.setFillColor(sf::Color::Transparent);
	textBox.setOutlineColor(sf::Color::Red);
	textBox.setOutlineThickness(2);

	sf::Font font; //Creates font object to load to text
	if (!font.loadFromFile("Fonts\\light_pixel-7.ttf")) {
		std::cout << "Could not load file" << std::endl;
	}
	sf::Text text; //Creates text object for name to be drawn to screen
	text.setFont(font);
	text.setPosition(textBox.getPosition().x + textBox.getSize().x / 2.f, textBox.getPosition().y + textBox.getSize().y / 5.f);
	text.setCharacterSize(25);
	text.setFillColor(sf::Color::White);

	sf::Text namePrompt; //Creates text object for user prompt
	namePrompt.setFont(font);
	namePrompt.setString("Enter your name:");
	namePrompt.setPosition(WINDOW_WIDTH/2-namePrompt.getCharacterSize()*5.4f, textBox.getPosition().y - (textBox.getSize().y*1.5f));
	namePrompt.setFillColor(sf::Color::White);

	std::string name; //Player name

	
	//Draw Loop
	while (window.isOpen()&&!created) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::BackSpace&&name.size()>0) {
					name = name.substr(0, name.size() - 1);
					text.setString(name);
					text.setPosition(text.getPosition().x + (textBox.getSize().x / (text.getCharacterSize()*1.15f)), text.getPosition().y);
				}
				if (name.size() > 0 && event.key.code == sf::Keyboard::Return) {
					created = true;
					break;
				}
			}
			if (event.type == sf::Event::TextEntered&&(char)event.text.unicode!='\b'&&name.size()<10) {
				name += (char)event.text.unicode;
				text.setString(name);
				text.setPosition(text.getPosition().x - (textBox.getSize().x/ (text.getCharacterSize()*1.15f)), text.getPosition().y);
			}
		}
		window.clear();
		window.draw(text);
		window.draw(namePrompt);
		window.draw(textBox);
		window.display();
	}

	window.setKeyRepeatEnabled(false);

	//Creating player
	Player *player = new Player(name);
	player->setTexture("Sprites\\PlayerAnims\\Walking\\Walking1.png");
	player->setSprite();
	player->getPlayer().setPosition(400, 400);
	return player;
}

//Game Manager Destructor
GameManager::~GameManager() {

}