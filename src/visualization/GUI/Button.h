#ifndef Button_H_ 
#define Button_H_

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

};

#endif //Button_H_ 
