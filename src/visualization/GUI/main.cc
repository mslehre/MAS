#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "gui.h"

/**
 * \brief This is the main function for the GUI.
 */

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "MAS");

    sf::Texture startButtonTexture;
    if (!startButtonTexture.loadFromFile("startButton.png")) {
        std::cerr << "Error: Can not load startButton.png" << std::endl;
        return -1;
    }
    sf::Sprite startButton;
    startButton.setTexture(startButtonTexture);
    startButton.setPosition(sf::Vector2f(200.f, 300.f));

    //sf::Sprite startButton=loadtexture("startButton.png"); // TODO: solve the white box problem (missing texture)
    //startButton.setPosition(sf::Vector2f(200.f, 300.f));

    bool clicked_startButton = false;
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ///< "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            ///< "mouseButton clicked" events
            if (event.type == sf::Event::MouseButtonPressed) {

                auto mouse_pos = sf::Mouse::getPosition(window); ///< local mouse position in the window
                auto global_mouse_pos = window.mapPixelToCoords(mouse_pos); ///< mouse position in world coordinates

                if (event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << mouse_pos.x << std::endl;
                    std::cout << "mouse y: " << mouse_pos.y << std::endl;
                }
                if (event.mouseButton.button == sf::Mouse::Right) {
                    std::cout << "the right button was pressed" << std::endl;
                    std::cout << "mouse x: " << mouse_pos.x << std::endl;
                    std::cout << "mouse y: " << mouse_pos.y << std::endl;
                }
                if (!clicked_startButton) {
                    if (startButton.getGlobalBounds().contains(global_mouse_pos)) {
                        clicked_startButton = true;
                        std::cout << "startButton clicked" << std::endl;
                    }
                }
            }     
        }

        window.clear(sf::Color::White);
        if (!clicked_startButton) {
            window.draw(startButton);
        }
		window.display();
    }

    return 0;
}
