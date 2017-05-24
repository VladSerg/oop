#ifndef _HIGHLIGHTING_HPP_
#define _HIGHLIGHTING_HPP_

#include "pointer.hpp"

struct Highlighting
{
	Pointer first{ -1,-1 };
	Pointer second{ -1, -1 };
	bool InOneLine() const { return first.x == second.x; };
	void sort();
};


#endif //_HIGHLIGHTING_HPP_