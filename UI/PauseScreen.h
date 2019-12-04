#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <string>

class PauseScreen{
    sf::Text resume;
	sf::Text exit;
  
    public:
        PauseScreen(sf::Font&);
        void draw(sf::RenderWindow& window);
};