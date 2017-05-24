#ifndef _POINTER_HPP_
#define _POINTER_HPP_

struct Pointer
{
	int x;
	int y;
	Pointer(int _x, int _y );

	bool operator == (const Pointer _y) const { return (x == _y.x && y == _y.y); };
	bool operator != (const Pointer _y) const { return !(*this == _y); };
};

#endif // _POINTER_HPP_