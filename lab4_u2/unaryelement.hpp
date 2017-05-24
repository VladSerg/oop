#ifndef _UNARY_ELEMENT_HPP_
#define _UNARY_ELEMENT_HPP_

#include "element.hpp"
#include "messages.hpp"

class UnaryElement : public Element
{
public:
	enum Action { AC_Buffer, AC_Invertor };
	UnaryElement(Action _action, Element const & _element);
	
	virtual bool evaluate() const override;

private:
	Element const & m_element;
	Action m_action;
};


/****************************************************************************/


inline bool UnaryElement::evaluate() const
{
	if (m_action == AC_Buffer)
		return m_element.evaluate();
	return !m_element.evaluate();
};

inline UnaryElement::UnaryElement(Action _action, Element const & _element)
	:m_action(_action), m_element(_element)
{
	//if (m_element)
	//	throw std::logic_error(Messages::InvalidPointer);
};


#endif // _UNARY_ELEMENT_HPP_