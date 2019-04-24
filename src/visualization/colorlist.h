
#ifndef colorlist_H_
#define colorlist_H_

#include <SFML/Graphics.hpp>
#include <vector>

/** \brief This Class stores a List of well-distinguishable Colors. (Color Values)
 *
 * the Class stores 1 variable: list, which is a vector with different Color Values.
 * you can initialize a "colorlist" with an integer k. (See constructors)
 * Also there are update methods, to initialize variables after the constructor call.
 */
class colorlist {
    private:
        std::vector<sf::Color> list; ///< vector of well-distinguishable Colors
    public:
        /** 
         * \param numbOfKmers an integer which set the size of list
         */
        colorlist(int numbOfKmers);   ///< complete constructor
        colorlist();                 ///< standard constructor

        /** 
         * \param numbOfKmer an integer which set the size of list
         */
        void updateList(int numbOfKmers); ///< update function for list
        /**
         * \return a vector of different Color values
         */
        std::vector<sf::Color> giveList(); ///< return method for the class variable
};

#endif //colorlist_H_
