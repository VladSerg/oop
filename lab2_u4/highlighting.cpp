#include "highlighting.hpp"
#include<algorithm>

void Highlighting::sort() 
{
	if (InOneLine())
		if (first.y > second.y)
			std::swap(first, second);

		else if (first.x > second.x)
			std::swap(first, second);
}
