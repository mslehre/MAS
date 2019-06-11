#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "../visualization/GraphRenderer.h"
#include "../visualization/Button.h"
#include "../visualization/Slider.h"
#include "Gamemaster.h"

int main() {
    //Open the window with restrict framerate
    sf::RenderWindow window(sf::VideoMode(1600, 900), "MAS");
    window.setFramerateLimit(120);

    //default parameter for the game
    unsigned int k = 3;
    unsigned int length_of_sequences = 42;
    unsigned int number_of_sequences = 4;
    unsigned int probability = 25;
    std::string status = "menu"; // "status" of the window {menu, game, settings, quit} 

    sf::Clock clock; //clock to compute a scroll speed
    Gamemaster gamemaster;
    vector<Node> nodeList;
    GraphRenderer GrRend;

    Button startButton = Button("../../fig/startButton.png", 550, 100, "game", "menu");
    Button settingsButton = Button("../../fig/settingsButton.png", 550, 300, "settings", "menu");
    Button quitButton = Button("../../fig/quitButton.png", 550, 500, "quit", "menu");
    Button menuButtonGame = Button("../../fig/menuButton.png", 0, 0, "menu", "game");
    Button menuButtonSettings = Button("../../fig/menuButton.png", 0, 0, "menu", "settings");

    startButton.setFunction([&nodeList, &gamemaster, &GrRend, &window, &k, &length_of_sequences,
                             &number_of_sequences, &probability] () {
            gamemaster.makeGame(k, length_of_sequences, number_of_sequences, probability);
            nodeList = gamemaster.GameGraph.getNodes();
            GraphRenderer gtemp(window, gamemaster.GameGraph, gamemaster.GameNodes);
            GrRend = gtemp;
    });
 
    settingsButton.setFunction([] () {});
    quitButton.setFunction([&window] () {window.close(); });
    menuButtonGame.setFunction([&GrRend, &window] () {window.setView(GrRend.defaultView); });
    menuButtonSettings.setFunction([&GrRend, &window] () {window.setView(GrRend.defaultView); });

    Slider slider_k(450, 100, 1, 6, k, "Length of kmer");
    Slider slider_lengSeq(450, 300, 10, 500, length_of_sequences, "Length of sequences");
    Slider slider_numSeq(450, 500, 2, 50, number_of_sequences, "Number of sequences");
    Slider slider_mutation(450, 700, 0, 100, probability, "Mutationprobability");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            auto mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close(); 

            startButton.eventHandler(event, status, mouse_position);
            settingsButton.eventHandler(event, status, mouse_position);
            quitButton.eventHandler(event, status, mouse_position);
            menuButtonGame.eventHandler(event, status, mouse_position);
            menuButtonSettings.eventHandler(event, status, mouse_position);
            if (status == "game")
                GrRend.eventHandler(event, window, nodeList, gamemaster.GameNodes, gamemaster.GameState,
                                    mouse_position);
        }

        if (status == "menu") {
            window.clear(sf::Color::White);
            window.draw(startButton.get_Button_Sprite());
            window.draw(settingsButton.get_Button_Sprite());
            window.draw(quitButton.get_Button_Sprite());
            clock.restart();
        }
        if (status == "settings") {
            window.clear(sf::Color::White);
            slider_k.draw(window, k);
            slider_lengSeq.draw(window, length_of_sequences);
            slider_numSeq.draw(window, number_of_sequences);
            slider_mutation.draw(window, probability);
            window.draw(menuButtonSettings.get_Button_Sprite());
            clock.restart();
        }
        if (status == "game") {
            GrRend.updateDrawNode(window, nodeList, gamemaster.GameNodes, gamemaster.GameState, menuButtonGame);
            GrRend.render(window, gamemaster.GameNodes, nodeList);  //Render method for update window
            menuButtonGame.setPosition(window.getView().getCenter().x - (window.getSize().x / 2),
                                       window.getView().getCenter().y - (window.getSize().y / 2));
            GrRend.display_score(window, gamemaster.GameState);
            window.draw(menuButtonGame.get_Button_Sprite());
            sf::Time elapsed = clock.restart();
            GrRend.update(elapsed.asSeconds()); //scroll speed computation
        }
        window.display();
    }
    return 0;
}
