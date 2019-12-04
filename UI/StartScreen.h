#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>

class StartScreen{
    sf::Text title;
	sf::Text playButton;

    public:
        StartScreen(sf::Font&);
        void draw(sf::RenderWindow& window);
};