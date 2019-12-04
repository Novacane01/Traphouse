#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <string>

class CreatePlayerScreen{
    sf::Text nameInput;
	sf::Text namePrompt;
    sf::RectangleShape textBox;
    std::string playerName;

    public:
        CreatePlayerScreen(sf::Font&);
        std::string draw(sf::RenderWindow& window);
};