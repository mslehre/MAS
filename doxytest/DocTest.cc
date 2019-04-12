 

/** \brief A short description of test base class
 *         that may go over multiple lines if necessary.
 *
 * A more elaborate description of class DocTestB,
 * also with multiple lines.
 */
class DocTestB {
public:
    /** 
     *
     *
     */
    void do_something(int n, float x);
      
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



int main(void) {
    Rectangle Rect;
 
   Rect.setWidth(5);
   Rect.setHeight(7);

   // Print the area of the object.
   Rect.getArea();

   return 0;
}


//!  A test class. 
/*!
  A more elaborate class description.
*/
class QTstyle_Test
{
  public:
    //! An enum.
    /*! More detailed enum description. */
    enum TEnum { 
                 TVal1, /*!< Enum value TVal1. */  
                 TVal2, /*!< Enum value TVal2. */  
                 TVal3  /*!< Enum value TVal3. */  
               } 
         //! Enum pointer.
         /*! Details. */
         *enumPtr, 
         //! Enum variable.
         /*! Details. */
         enumVar;  
    
    //! A constructor.
    /*!
      A more elaborate description of the constructor.
    */
    QTstyle_Test();
    //! A destructor.
    /*!
      A more elaborate description of the destructor.
    */
   ~QTstyle_Test();
    
    //! A normal member taking two arguments and returning an integer value.
    /*!
      \param a an integer argument.
      \param s a constant character pointer.
      \return The test results
      \sa QTstyle_Test(), ~QTstyle_Test(), testMeToo() and publicVar()
    */
    int testMe(int a,const char *s);
       
    //! A pure virtual member.
    /*!
      \sa testMe()
      \param c1 the first argument.
      \param c2 the second argument.
    */
    virtual void testMeToo(char c1,char c2) = 0;
   
    //! A public variable.
    /*!
      Details.
    */
    int publicVar;
       
    //! A function variable.
    /*!
      Details.
    */
    int (*handler)(int a,int b);
};
