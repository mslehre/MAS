#include "../GraphRenderer.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

using namespace std;

int main(int argc, char **argv){
    //Troubleshooting bad arguments
    if (argc != 3) {
        cerr << "\nMissing arguments or too many arguments.\n" << endl;
        printHelp();
        return -1;
    }	
    unsigned int k = atoi(argv[2]);
    if (k <= 0) {
        cerr << "\nThe number must be an positive integer.\n" << endl;
        printHelp();
        return -1;
    }

    // Get Graph by file
    Graph g;
    g.readFastaFiles(argv[1], atoi(argv[2]));
    //get some graph components to compute sth
    vector<Node> nodeList = g.getNodes();
    vector<DrawNode> Nodes;
    //Initialize colomap
    vector<string> Kmers = giveKmers(nodeList);
    colorlist colorExample(Kmers.size());
    vector<sf::Color> colors = colorExample.giveList();
    colormap mapExample(Kmers, colors);
    //initialize DrawNodes
    for (unsigned i = 0; i < nodeList.size(); i++) {
        DrawNode ph;
        Nodes.push_back(ph);
        sf::Vector2f coords(nodeList.at(i).j, nodeList.at(i).i);
        Nodes.at(i).coordinate = coords;
        Nodes.at(i).col = mapExample.Map(nodeList.at(i).kmer);
    }
    //Open the window with white Background and restrict framerate
    sf::RenderWindow window(sf::VideoMode(1600, 900), "MAS");
    window.clear(sf::Color::White);
    window.setFramerateLimit(120);
    window.display();

    //Create Game State
    state gameState(g);
    //Create a GraphRenderer
    GraphRenderer GrRend(window, g, Nodes);
    //create clock to compute a scroll speed
    sf::Clock clock;

    std::string status = "game"; // "status" of the window {menu, game, settings, help, quit} 
    Button menuButton = Button("../../../fig/menuButton.png", 1300, 0, "game", "game");
    menuButton.setFunction([&GrRend] () {GrRend.actualView = GrRend.defaultView; });

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            auto mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            // "close requested" event: we close the window
            if (event.type == sf::Event::EventType::Closed)
                window.close();
            //eventhandler for graphical interaction
            GrRend.eventHandler(event, window, nodeList, Nodes, gameState);
            menuButton.eventHandler(event, status, mouse_position);
        }
        GrRend.updateDrawNode(window, nodeList, Nodes, gameState, menuButton);
        //Render method for update window
        GrRend.render(window, Nodes, nodeList);
        menuButton.setPosition(window.getView().getCenter().x - (window.getSize().x / 2),
                               window.getView().getCenter().y - (window.getSize().y / 2));
        GrRend.display_score(window, gameState);
        window.draw(menuButton.get_Button_Sprite());   
        window.display();
        sf::Time elapsed = clock.restart();
        //scroll speed computation
        GrRend.update(elapsed.asSeconds());
    }
    return 0;
}
