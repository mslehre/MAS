#ifndef button_H_ 
#define button_H_

#include <string>
#include <SFML/Graphics.hpp>

/** 
 * \brief This class generate button for the GUI.
 */

// TODO: 
//       - The call of function()  dont work for any function yet. (only for void)
//       - the button class could have a general "setFunction" method that assignes 
//         a method that is invoked on button click. 
//         (see function object https://de.cppreference.com/w/cpp/utility/functional/function)

class Button {
    private:
        sf::Sprite Button_Sprite;   ///< Sprite of the Button
        sf::Texture Button_Texture; ///< Texture of the Button

    public:
        void (*Button_function) ();
         
         /** 
         * \param texturename is the name of the texture of the button
         * \param x_pos is the x coordinate of the sprite in the window
         * \param y_pos is the y coordinate of the sprite in the window
         * \param function is the function that will executed if the button is pushed
         * \return a Button with texture on a specific position
         */

        Button(std::string texturename, unsigned int x_pos, unsigned int y_pos, void function());
        
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

#endif //button_H_ 