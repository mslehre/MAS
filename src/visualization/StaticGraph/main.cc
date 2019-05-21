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
    for (uint i = 0; i < nodeList.size(); i++) {
        DrawNode ph;
        Nodes.push_back(ph);
        sf::Vector2f coords(nodeList.at(i).j, nodeList.at(i).i);
        Nodes.at(i).coordinate = coords;
        Nodes.at(i).col = mapExample.Map(nodeList.at(i).kmer);
    }
    //initialize width and length of the sequences to compute a sizeConstant for the visuals
    float length = 0;
    float width = 0;
    float size;
    for (uint i = 0; i < nodeList.size(); i++) {
        if (length < nodeList.at(i).j)
            length = nodeList.at(i).j;
        if (width < nodeList.at(i).i)
            width = nodeList.at(i).i;
    }
    if (length > 50 && width > 5) {
        size = 50 + 80.0 * (1.0 / ((length / 50.0) * (width / 5)));
    } else {
        size = 130;
    }
    //Open the window with white Background and restrict framerate
    sf::RenderWindow window(sf::VideoMode(1600, 900), "MAS");
    window.clear(sf::Color::White);
    window.setFramerateLimit(120);
    window.display();

    //Create a GraphRenderer
    GraphRenderer GrRend(window, g, Nodes, (int)size);
    //create clock to compute a scroll speed
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::EventType::Closed)
                window.close();
            //eventhandler for graphical interaction
            GrRend.eventHandler(event, window, nodeList);
        }
        //Render method for update window
        GrRend.render(window);
        window.display();
        sf::Time elapsed = clock.restart();
        //scroll speed computation
        GrRend.update(elapsed.asSeconds());
    }
    return 0;
}
