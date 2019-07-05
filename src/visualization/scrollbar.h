
#ifndef scrollbar_H_
#define scrollbar_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <vector>

class scrollbar{
    private:
        sf::View actualView;
        sf::Vector2f xbound;
        sf::Vector2f ybound; 
        sf::Vector2f posOfWin;
        float xQuot;
        float yQuot;
        float xPos;
        float yPos;
        unsigned thickness;
        bool movable1;  
        bool movable2;
        sf::RectangleShape xScrollEl;
        sf::RectangleShape yScrollEl;
        sf::RectangleShape xScrollBar;
        sf::RectangleShape yScrollBar;
    public:

        /** 
         * \param x_pos is the x coordinate of the slider in the window
         * \param y_pos is the y coordinate of the slider in the window
         * \param min is the minimal value of the slider
         * \param max is the maximal value of the slider
         * \param variable is variable that will be changed with the slider
         * \param name this string will draw above the slider in the window
         */

        scrollbar(sf::RenderWindow& window, sf::Vector2f posOfWin, sf::Vector2f xbound, sf::Vector2f ybound, float thickness);

        /** 
         * \param window is the RenderWindow which gets the drawed slider
         * \param number is variable that will be changed with the slider
         */

         void draw(sf::RenderWindow& window, sf::View& myView, std::vector<float>& direction);
};

#endif //scrollbar_H_


