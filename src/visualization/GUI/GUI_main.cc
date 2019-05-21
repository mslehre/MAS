#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "../../alignment/Graph.h"
#include "Gamemaster.h"
#include "Button.h"

void test() { // for tests TODO: delete this function later
    std::cout << "test" << std::endl;
} 

void test2(Graph g) { //for tests
    std::cout << g.getNodes().size() << std::endl;
}  

int main() {
    sf::RenderWindow window(sf::VideoMode(1600, 900), "MAS");

    Gamemaster gamemaster(4, 100, 10, 0.8);

    Button startButton = Button("../../../fig/startButton.png", 550, 100, "ingame", "menu");
   // Button settingsButton = Button("../../../fig/settingsButton.png", 550, 300, "settings", "menu");
    Button quitButton = Button("../../../fig/quitButton.png", 550, 500, "quit", "menu");
    startButton.setFunction([&gamemaster] () {test2(gamemaster.get_GameGraph()); });
    quitButton.setFunction([&window] () {window.close();});
   // settingsButton.setFunction([&g] () {test2(g);});

    std::string status = "menu";
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            auto mouse_pos = sf::Mouse::getPosition(window); // local mouse position in the window
            auto global_mouse_pos = window.mapPixelToCoords(mouse_pos); // mouse position in world coordinates

            if (event.type == sf::Event::Closed)
                window.close(); 

            status = startButton.eventHandler(event, status, global_mouse_pos);
           // status = settingsButton.eventHandler(event, status, global_mouse_pos);
            status = quitButton.eventHandler(event, status, global_mouse_pos);
        }

        window.clear(sf::Color::White);
        if (status == "menu") {
            window.draw(startButton.get_Button_Sprite());
          //  window.draw(settingsButton.get_Button_Sprite());
            window.draw(quitButton.get_Button_Sprite());
        }
        window.display();
    }

    return 0;
}
