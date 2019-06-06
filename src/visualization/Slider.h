#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

class Slider{
    private:
        int x_pos;
        int y_pos;
        bool movable;        
        unsigned int min;
        unsigned int max; 
        unsigned int value;      
        unsigned int height;
        unsigned int axis_width;
        unsigned int slider_width;
        sf::Font font;
	    sf::Text text;
	    sf::RectangleShape axis;
        sf::RectangleShape slider; 
        std::string name;       
    public:
	Slider(int x_pos, int y_pos, unsigned int min, unsigned int max, unsigned int& number, std::string name);
    unsigned int getValue();
	void draw(sf::RenderWindow& window, unsigned int& number);
	sf::Text drawText(std::string s, int x_pos, int y_pos, unsigned int size);
};
