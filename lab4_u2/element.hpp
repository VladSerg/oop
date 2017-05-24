#ifndef _ELEMENT_HPP_
#define _ELEMENT_HPP_


class Element
{
public:
	virtual ~Element() = default; //?
	virtual bool evaluate() const = 0;

	Element(const Element &) = delete;
	Element & operator = (const Element &) = delete;

protected:
	Element() = default;

private:

};


/****************************************************************************/


#endif // _ELEMENT_HPP_