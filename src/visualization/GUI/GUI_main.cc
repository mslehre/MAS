#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "button.h"

void test() { // for tests TODO: delete this function later
    std::cout << "test" << std::endl;
} 

/**
 * \brief This is the main function for the GUI.
 */

int main() {
    sf::RenderWindow window(sf::VideoMode(1600, 900), "MAS");

    Button startButton = Button("../../../fig/startButton.png", 550, 100, test);
    Button settingsButton = Button("../../../fig/settingsButton.png", 550, 300, test);
    Button quitButton = Button("../../../fig/quitButton.png", 550, 500, test);

    bool clicked_startButton = false;
    //bool clicked_settingsButton = false;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            auto mouse_pos = sf::Mouse::getPosition(window); ///< local mouse position in the window
            auto global_mouse_pos = window.mapPixelToCoords(mouse_pos); ///< mouse position in world coordinates

            ///< "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            ///< hover with mouse over Button                                            
            if (!clicked_startButton) {
                if (startButton.get_Button_Sprite().getGlobalBounds().contains(global_mouse_pos)) {
                    startButton.load_Texture("../../../fig/startButton_hover.png");
                } else {
                    startButton.load_Texture("../../../fig/startButton.png");
                }
                if (settingsButton.get_Button_Sprite().getGlobalBounds().contains(global_mouse_pos)) {
                    settingsButton.load_Texture("../../../fig/settingsButton_hover.png");
                } else {
                    settingsButton.load_Texture("../../../fig/settingsButton.png");
                }
                if (quitButton.get_Button_Sprite().getGlobalBounds().contains(global_mouse_pos)) {
                    quitButton.load_Texture("../../../fig/quitButton_hover.png");
                } else {
                    quitButton.load_Texture("../../../fig/quitButton.png");
                }
            }

            ///< "mouseButton clicked" events
            if (event.type == sf::Event::MouseButtonPressed) { 
            // left mouseButton               
                if (event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << mouse_pos.x << std::endl;
                    std::cout << "mouse y: " << mouse_pos.y << std::endl;

                    if (!clicked_startButton) {
                        if (startButton.get_Button_Sprite().getGlobalBounds().contains(global_mouse_pos)) {
                            clicked_startButton = true;
                            std::cout << "startButton clicked" << std::endl;
                            //startButton.load_Texture("../../../fig/startButton_clicked.png");
                            startButton.Button_function();
                        }
                        if (settingsButton.get_Button_Sprite().getGlobalBounds().contains(global_mouse_pos)) {
                            //clicked_settingsButton = true;
                            std::cout << "settingsButton clicked" << std::endl;
                            //settingsButton.load_Texture("../../../fig/settingsButton_clicked.png");
                            settingsButton.Button_function();
                        }
                        if (quitButton.get_Button_Sprite().getGlobalBounds().contains(global_mouse_pos)) {
                            std::cout << "quitButton clicked" << std::endl;
                            //quitButton.load_Texture("../../../fig/quitButton_clicked.png");
                            quitButton.Button_function();
                            window.close();
                        }
                    }
                }
            // right mouseButton 
                if (event.mouseButton.button == sf::Mouse::Right) {
                    std::cout << "the right button was pressed" << std::endl;
                    std::cout << "mouse x: " << mouse_pos.x << std::endl;
                    std::cout << "mouse y: " << mouse_pos.y << std::endl;
                }                
            }     
        }

        window.clear(sf::Color::White);
        if (!clicked_startButton) {
            window.draw(startButton.get_Button_Sprite());
            window.draw(settingsButton.get_Button_Sprite());
            window.draw(quitButton.get_Button_Sprite());
        }
        window.display();
    }

    return 0;
}
