#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

class Slider{
    private:
        int x_pos; ///< x coordinate of the slider
        int y_pos; ///< y coordinate of the slider
        bool movable;   ///< true, if the slider button is movable
        unsigned int min;   ///< the minimal value of the slider
        unsigned int max;   ///< the maximal value of the slider
        unsigned int value; ///< the current value of the slider
        unsigned int axis_height;   ///< height of the slider axis
        unsigned int axis_width;    ///< width of the slider axis
        unsigned int slider_width;  ///< width of the slider button
        sf::Font font;  ///< font of text
	    sf::Text text;  ///< for the
	    sf::RectangleShape axis;    ///<
        sf::RectangleShape slider;  ///<
        std::string name;   ///< name of the slider
    public:

        /**
         *
         */

	Slider(int x_pos, int y_pos, unsigned int min, unsigned int max, unsigned int& number, std::string name);

        /**
         *
         */

	void draw(sf::RenderWindow& window, unsigned int& number);

        /**
         *
         */

	sf::Text drawText(std::string s, int x_pos, int y_pos, unsigned int size);
};
