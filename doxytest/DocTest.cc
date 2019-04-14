/**
 * \brief Example DocTest file
 *
 * This file is there so we can test, how IDEs make use
 * of doxygen-style comments.
 */
#include "DocTest.hh"

int main(){
	DocTestB B;
	DocTestD1 D1;
	DocTestD2 D2;

	B.do_something(1, 2.0, 'a', false);
	D1.width = 22;
	D2.d = 2.2;
	return 0;
}



