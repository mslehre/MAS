#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "../visualization/GraphRenderer.h"
#include "../visualization/Button.h"
#include "Gamemaster.h"
/*
void choose_parameter(unsigned int& k, unsigned int& length_of_sequences, unsigned int& number_of_sequences, double& probability, bool& new_parameter){
    k = 3;
    length_of_sequences = 100;
    number_of_sequences = 3;
    probability = 0.3;
    new_parameter = true;
}
*/
int main() {
    //Open the window with restrict framerate
    sf::RenderWindow window(sf::VideoMode(1600, 900), "MAS");
    window.setFramerateLimit(120);

    //parameter for game
    unsigned int k = 3;
    unsigned int length_of_sequences = 42;
    unsigned int number_of_sequences = 4;
    double probability = 0.3;
    std::string status = "menu"; // "status" of the window {menu, game, settings, help, quit} 
    bool new_parameter = false;

    Gamemaster gamemaster(k, length_of_sequences, number_of_sequences, probability);
    //Initialize variables
    vector<Node> nodeList = gamemaster.GameGraph.getNodes();
    //continue main
    GraphRenderer GrRend(window, gamemaster.GameGraph, gamemaster.GameNodes);
    sf::Clock clock; //clock to compute a scroll speed

    Button startButton = Button("../../fig/startButton.png", 550, 100, "game", "menu");
  // Button settingsButton = Button("../../fig/settingsButton.png", 550, 300, "menu", "menu");
    Button quitButton = Button("../../fig/quitButton.png", 550, 500, "quit", "menu");
    Button menuButton = Button("../../fig/menuButton.png", 1300, 0, "menu", "game");

    startButton.setFunction([&nodeList, &gamemaster, &GrRend, &window, &k, &length_of_sequences, &number_of_sequences, &probability, &new_parameter] () {
        if (new_parameter) {
            Gamemaster gM(k, length_of_sequences, number_of_sequences, probability);
            gamemaster = gM;
            nodeList = gM.GameGraph.getNodes();
            GraphRenderer g(window, gM.GameGraph, gM.GameNodes);
            GrRend = g;
        } 
    });
/*
    settingsButton.setFunction([&k, &length_of_sequences, &number_of_sequences, &probability, &new_parameter] () {
        choose_parameter(k, length_of_sequences, number_of_sequences, probability, new_parameter);
    });
*/
    quitButton.setFunction([&window] () {window.close(); });
    menuButton.setFunction([&GrRend] () {GrRend.actualView = GrRend.defaultView; });

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            auto mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close(); 

            startButton.eventHandler(event, status, mouse_position);
           // settingsButton.eventHandler(event, status, mouse_position);
            quitButton.eventHandler(event, status, mouse_position);
            menuButton.eventHandler(event, status, mouse_position);
            GrRend.eventHandler(event, window, nodeList, gamemaster.GameNodes, gamemaster.GameState);
        }

        if (status == "menu") {
            window.clear(sf::Color::White);
            window.draw(startButton.get_Button_Sprite());
           // window.draw(settingsButton.get_Button_Sprite());
            window.draw(quitButton.get_Button_Sprite());
            clock.restart();
        }
        if (status == "game") {
            window.clear(sf::Color::White);
            GrRend.updateDrawNode(window, nodeList, gamemaster.GameNodes);
            GrRend.render(window, gamemaster.GameNodes, nodeList);  //Render method for update window
            GrRend.display_score(window, gamemaster.GameState);
            menuButton.setPosition(window.getView().getCenter().x - (window.getSize().x / 2),
                                   window.getView().getCenter().y - (window.getSize().y / 2));
            window.draw(menuButton.get_Button_Sprite());                        
            sf::Time elapsed = clock.restart();
            GrRend.update(elapsed.asSeconds()); //scroll speed computation
        }
        window.display();      
    }
    return 0;
}
