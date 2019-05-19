#include "Button.h"
#include <iostream>
#include <stdlib.h> 
#include <stdio.h> 
#include <sstream>

Button::Button(std::string texturename, unsigned int x_pos, unsigned int y_pos, std::function<void()> function){ 
    load_Texture(texturename);
    Button_Sprite.setPosition(sf::Vector2f(x_pos, y_pos));    
    Button_function = function;
}

Button::Button(std::string texturename, unsigned int x_pos, unsigned int y_pos){
    load_Texture(texturename);
    Button_Sprite.setPosition(sf::Vector2f(x_pos, y_pos));   
}

void Button::load_Texture(std::string name){
    if (!Button_Texture.loadFromFile(name))
        std::cerr << "Error: Can not load " << name << "." << std::endl;
    Button_Sprite.setTexture(Button_Texture);
}

sf::Sprite Button::get_Button_Sprite(){
    return Button_Sprite;
}

Graph Button::create_level(unsigned int k, unsigned int lenght, unsigned int number_of_sequences, double probability){
    Graph g;

    //std::cout << k << " " << lenght << " " << number_of_sequences << " " << probability << std::endl;

    std::stringstream s;
    s << lenght << " " << number_of_sequences << " " << probability;
    std::string command = "../../SequenceSimulation/./simulation_main " + s.str();    

    printf ("Checking if processor is available...");
    if (system(NULL)) puts ("Ok");
        else exit (EXIT_FAILURE);
    int system_return = system (command.c_str());
    printf ("The value returned was: %d.\n", system_return);

    g.readFastaFiles("../../SequenceSimulation/sequences.fa", k);
    return g;
}
