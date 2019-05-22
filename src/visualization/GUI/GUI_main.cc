#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "../GraphRenderer.h"
#include "Gamemaster.h"
#include "Button.h"

void test(Graph g) { //for tests TODO: delete this function later
    std::cout << g.getNodes().size() << std::endl;
}  

int main() {
    //Open the window with restrict framerate
    sf::RenderWindow window(sf::VideoMode(1600, 900), "MAS");
    window.setFramerateLimit(120);

    Gamemaster gamemaster(4, 100, 10, 0.2);

    //initialize Buttons
    Button startButton = Button("../../../fig/startButton.png", 550, 100, "game", "menu");
    // Button settingsButton = Button("../../../fig/settingsButton.png", 550, 300, "settings", "menu");
    Button quitButton = Button("../../../fig/quitButton.png", 550, 500, "quit", "menu");
    startButton.setFunction([&gamemaster] () {test(gamemaster.getGameGraph()); });
    quitButton.setFunction([&window] () {window.close();});
    // settingsButton.setFunction([&g] () {test(g);});

    //initialize width and length of the sequences to compute a sizeConstant for the visuals
    float length = 0;
    float width = 0;
    float size;
    for (uint i = 0; i < gamemaster.getGameGraph().getNodes().size(); i++) {
        if (length < gamemaster.getGameGraph().getNodes().at(i).j)
            length = gamemaster.getGameGraph().getNodes().at(i).j;
        if (width < gamemaster.getGameGraph().getNodes().at(i).i)
            width = gamemaster.getGameGraph().getNodes().at(i).i;
    }
    if (length > 50 && width > 5) {
        size = 50 + 80.0 * (1.0 / ((length / 50.0) * (width / 5)));
    } else {
        size = 130;
    }

    std::string status = "menu";

    //Create a GraphRenderer
    GraphRenderer GrRend(window, gamemaster.getGameGraph().getNodes(), gamemaster.getGameGraph().getEdges(), (int)size);
    //create clock to compute a scroll speed
    sf::Clock clock;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            auto global_mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window)); // mouse position

            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close(); 
            
            GrRend.eventHandler(event, window, gamemaster.getGameGraph().getNodes());
            status = startButton.eventHandler(event, status, global_mouse_pos);
           // status = settingsButton.eventHandler(event, status, global_mouse_pos);
            status = quitButton.eventHandler(event, status, global_mouse_pos);
        }

        if (status == "menu") {
            window.clear(sf::Color::White);
            window.draw(startButton.get_Button_Sprite());
          //  window.draw(settingsButton.get_Button_Sprite());
            window.draw(quitButton.get_Button_Sprite());
        }
        if (status == "game") {
            //Render method for update window
            GrRend.render(window);
            sf::Time elapsed = clock.restart();
            //scroll speed computation
            GrRend.update(elapsed.asSeconds());
        }
        window.display();      
    }
    return 0;
}
