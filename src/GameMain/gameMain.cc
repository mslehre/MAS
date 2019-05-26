#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "../visualization/GraphRenderer.h"
#include "../visualization/Button.h"
#include "Gamemaster.h"

//initialize width and length of the sequences to compute a sizeConstant for the visuals
void calculate_visual_size(Gamemaster& g, float& size){ //TODO:Mayby into Graphrenderer.cc? 
    float length = 0;
    float width = 0;
    for (unsigned int i = 0; i < g.getGameGraph().getNodes().size(); i++) {
        if (length < g.getGameGraph().getNodes().at(i).j)
            length = g.getGameGraph().getNodes().at(i).j;
        if (width < g.getGameGraph().getNodes().at(i).i)
            width = g.getGameGraph().getNodes().at(i).i;
    }
    if (length > 50 && width > 5)
        size = 50 + 80.0 * (1.0 / ((length / 50.0) * (width / 5)));
}

int main() {
    //Open the window with restrict framerate
    sf::RenderWindow window(sf::VideoMode(1600, 900), "MAS");
    window.setFramerateLimit(120);

    //parameter for game
    unsigned int k = 4;
    unsigned int length_of_sequences = 100;
    unsigned int number_of_sequences = 10;
    double probability = 0.2;    
    float size = 130; // for visuals
    std::string status = "menu"; // "status" of the window {menu, game, settings, help, quit} 

    Gamemaster gamemaster(k, length_of_sequences, number_of_sequences, probability);
    calculate_visual_size(gamemaster, size);
    GraphRenderer GrRend(window, gamemaster.getGameGraph().getNodes(), gamemaster.getGameGraph().getEdges(), (int)size);
    sf::Clock clock; //clock to compute a scroll speed

    Button startButton = Button("../../fig/startButton.png", 550, 100, "game", "menu");
    // Button settingsButton = Button("../../fig/settingsButton.png", 550, 300, "settings", "menu");
    Button quitButton = Button("../../fig/quitButton.png", 550, 500, "quit", "menu");
    startButton.setFunction([] () {});
    // settingsButton.setFunction([] () {});
    quitButton.setFunction([&window] () {window.close(); });

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            auto mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close(); 

            startButton.eventHandler(event, status, mouse_position);
           // settingsButton.eventHandler(event, status, global_mouse_pos);
            quitButton.eventHandler(event, status, mouse_position);
            GrRend.eventHandler(event, window, gamemaster.getGameGraph().getNodes());
        }

        if (status == "menu") {
            window.clear(sf::Color::White);
            window.draw(startButton.get_Button_Sprite());
          //  window.draw(settingsButton.get_Button_Sprite());
            window.draw(quitButton.get_Button_Sprite());
            clock.restart();
        }
        if (status == "game") {
            GrRend.render(window);  //Render method for update window
            sf::Time elapsed = clock.restart();
            GrRend.update(elapsed.asSeconds()); //scroll speed computation
        }
        window.display();      
    }
    return 0;
}
