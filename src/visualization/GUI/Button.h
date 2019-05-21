#ifndef Button_H_ 
#define Button_H_
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>
#include <string>

/** 
 * \brief This class generate a button for the GUI.
 */

class Button {
    private:
        sf::Sprite Button_Sprite;   ///< Sprite of the Button
        sf::Texture Button_Texture; ///< Texture of the Button
        std::string Button_texturename; ///< name of the texture 
        std::string my_status;  ///< in this status the Button is clickable    
        std::string next_status;    ///< the next GUI status after the Button was clicked

    public:
        std::function<void()> Button_function;  ///< function of the Button
        /** 
         * \param texturename is the name of the texture of the button
         * \param x_pos is the x coordinate of the sprite in the window
         * \param y_pos is the y coordinate of the sprite in the window
         * \param nextStatus is the status of the GUI after the Button was clicked
         * \return a Button with a texture on a specific position
         */

        Button(std::string texturename, unsigned int x_pos, unsigned int y_pos, std::string nextStatus, std::string myStatus);
        
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
         * This function handle events
         * \param event a Event which will describe the event that will happen
         * \param status is the status of the current GUI
         * \param global_mouse_pos the current mouse position
         */
    
        std::string eventHandler(sf::Event event, std::string status, sf::Vector2f global_mouse_pos);

};

#endif //Button_H_ 
