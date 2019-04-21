#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "gui.h"

/**
 * \brief This is the main function for the GUI.
 */

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "MAS");

    std::vector<sf::Texture> all_textures;
    all_textures.push_back(loadtexture("startButton.png"));
    all_textures.push_back(loadtexture("settingsButton.png"));
    all_textures.push_back(loadtexture("quitButton.png"));
    sf::Sprite startButton = loadSprite(all_textures, 0, 400, 100);
    sf::Sprite settingsButton = loadSprite(all_textures, 1, 400, 300);
    sf::Sprite quitButton = loadSprite(all_textures, 2, 400, 500);

    bool clicked_startButton = false;
    bool clicked_settingsButton = false;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
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

                    if (!clicked_startButton) {
                        if (startButton.getGlobalBounds().contains(global_mouse_pos)) {
                            clicked_startButton = true;
                            std::cout << "startButton clicked" << std::endl;
                        }
                        if (settingsButton.getGlobalBounds().contains(global_mouse_pos)) {
                            clicked_settingsButton = true;
                            std::cout << "settingsButton clicked" << std::endl;
                        }
                        if (quitButton.getGlobalBounds().contains(global_mouse_pos)) {
                            std::cout << "quitButton clicked" << std::endl;
                            window.close();
                        }
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Right) {
                    std::cout << "the right button was pressed" << std::endl;
                    std::cout << "mouse x: " << mouse_pos.x << std::endl;
                    std::cout << "mouse y: " << mouse_pos.y << std::endl;
                }
                
            }     
        }

        window.clear(sf::Color::White);
        if (!clicked_startButton) {
            window.draw(startButton);
            window.draw(settingsButton);
            window.draw(quitButton);
        }
        window.display();
    }

    return 0;
}
