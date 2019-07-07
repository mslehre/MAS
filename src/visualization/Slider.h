#ifndef Slider_H_
#define Slider_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

class Slider{
    private:
        unsigned int x_pos; ///< x coordinate of the slider (upper left corner of axis)
        unsigned int y_pos; ///< y coordinate of the slider (upper left corner of axis)
        unsigned int min;   ///< the minimal value of the slider
        unsigned int max;   ///< the maximal value of the slider
        unsigned int value; ///< the current value of the slider
        unsigned int axis_height;   ///< height of the slider axis
        unsigned int axis_width;    ///< width of the slider axis
        unsigned int slider_width;  ///< width of the slider button
        bool movable;   ///< true, if the movable part of the slider is movable
        sf::Text text;  ///< is needed to display the values of the slider
        sf::Font font;  ///< font of text
        sf::RectangleShape axis;    ///< slider axis
        sf::RectangleShape slider_bar;  ///< movable part of the slider
        std::string name;   ///< name of the slider
    public:

        /** 
         * \param x_pos is the x coordinate of the slider in the window
         * \param y_pos is the y coordinate of the slider in the window
         * \param min is the minimal value of the slider
         * \param max is the maximal value of the slider
         * \param variable is variable that will be changed with the slider
         * \param name this string will draw above the slider in the window
         */

        Slider(unsigned int x_pos, unsigned int y_pos, unsigned int min, unsigned int max, unsigned int& variable, 
               std::string name);

        /** 
         * \param window is the RenderWindow which gets the drawed slider
         * \param number is variable that will be changed with the slider
         */

         void draw(sf::RenderWindow& window, unsigned int& variable);

        /**
         * \param text is the string that will be displayed in the window
         * \param x_pos is the x coordinate of the text in the window
         * \param y_pos is the y coordinate of the text in the window
         * \param size is the size of the text
         * \return a sf::Text 
         */

        sf::Text drawText(std::string text, int x_pos, int y_pos, unsigned int size);
};

#endif //Slider_H_
