/**
 * \mainpage What stands here goes to the main doxygen page.
 *
 * \section RL
 * \subsection Learning Algorithm 1
 * Bla Bla
 * \subsection Learning Algorithm 2
 * Bla Bla
 * \section Human Player
 * Bla Bla
 */

/** \brief A short description of test base class
 *         that may go over multiple lines if necessary.
 *
 * A more elaborate description of class DocTestB,
 * also with multiple lines.
 * ![inconcistency](../../../docs/pair-inconsistency.jpg)
 */
class DocTestB {
public:
    /** 
     * \param n the number of something
     * \param x a coordinate of something
     * \return a letter code that means something
     */
    char do_something(int n, float x);
      
    int width;
    int height;
};

/** \brief first derived class
 *        
 * Object of this class bla bla bla.
 */
class DocTestD1: public DocTestB {
public:
    enum Actions {
	top,   ///< brief description of action top
	down,  ///< brief description of action down
	left,  ///< brief description of action left
	right, ///< brief description of action right
	still  ///< brief description of action still
    }
    /**
     * detailed description of data member 'other'
     * If it would not go over multiple lines, a brief 
     * description in one line after the declaration is possible.
     */
    DocTestD1 *other;
    unsigned size; ///< size is the number of ...
};

/** \brief second derived class
 *        
 * state  | #actions
 * -------| -------------
 * start  | 5
 * term   | 1
 */
class DocTestD2: public DocTestB {
public:
    /**
     * The distance is Euklidean:
     * \f$d = \sqrt{\sum_i (x_i-y_i)^2}\f$.
     */
    double d; 
};
