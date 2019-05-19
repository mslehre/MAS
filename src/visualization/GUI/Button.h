#ifndef Button_H_ 
#define Button_H_

#include "../../alignment/Graph.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <functional>

/** 
 * \brief This class generate button for the GUI.
 */

class Button {
    private:
        sf::Sprite Button_Sprite;   ///< Sprite of the Button
        sf::Texture Button_Texture; ///< Texture of the Button

    public:
        std::function<void()> Button_function; ///< function of the Button
 
        /** 
         * \param texturename is the name of the texture of the button
         * \param x_pos is the x coordinate of the sprite in the window
         * \param y_pos is the y coordinate of the sprite in the window
         * \param function is the function that will executed if the button is pushed
         * \return a Button with a texture on a specific position
         */

        Button(std::string texturename, unsigned int x_pos, unsigned int y_pos, std::function<void()> function);

        /** 
         * \param texturename is the name of the texture of the button
         * \param x_pos is the x coordinate of the sprite in the window
         * \param y_pos is the y coordinate of the sprite in the window
         * \return a Button with a texture on a specific position
         */

        Button(std::string texturename, unsigned int x_pos, unsigned int y_pos);
        
        /**
         * This function load a new texture for the Button. 
         * \param name is the name of the new texture
         */

        void load_Texture(std::string name);

        /** 
         * \return Button_Sprite
         */

        sf::Sprite get_Button_Sprite();

        /** 
         * \param lenght is the length of the created sequences
         * \param number_of_sequences is the number of sequences that will created   
         * \param probability is the probability for mutations in the sequencens  
         * \return create a Graph
         */
            
        Graph create_level(unsigned int k, unsigned int lenght, unsigned int number_of_sequences,
                           unsigned int probability);

};

#endif //Button_H_ 
