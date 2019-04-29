#ifndef button_H_ 
#define button_H_

/** \brief This class generate a Button. 
 *  TODO... 
 *
 */

// TODO: - We need 3 textures for each Button: pushed, released, mouse over button
//       - The call of function()  dont work for any function yet. (only for void)


class Button {
    private:
        sf::Sprite Button_texture;

    public:
        void (*Button_function) ();   
 
         /** 
         * \param all_textures is a vector with all textures
         * \param index is the index of the texture you want to load from all_textures
         * \param x_pos is the x coordinate of the sprite in the window
         * \param y_pos is the y coordinate of the sprite in the window
         * \param function is the function that will executed if the button is pushed
         * \return a Button with texture on a specific position
         */

        Button(std::vector<sf::Texture>& all_textures, int index, int x_pos, int y_pos, void function());

        /** 
         * \param all_textures is a vector with all textures
         * \param index is the index of the texture you want to load from all_textures
         * \param x_pos is the x coordinate of the sprite in the window
         * \param y_pos is the y coordinate of the sprite in the window
         * \return a Sprite with texture on a specific position
         */

        sf::Sprite loadSprite(std::vector<sf::Texture>& all_textures, int index, int x_pos, int y_pos);

        /** 
          * \return Button_texture
          */

        sf::Sprite get_Button_texture();
};

#endif //button_H_ 
