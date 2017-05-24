#ifndef _INPUT_PORT_ELEMENT_HPP_
#define _INPUT_PORT_ELEMENT_HPP_

#include "element.hpp"
#include "port.hpp"
class Port;

class InputPortElement : public Element
{
public:
	InputPortElement(Port const & _port);
	virtual bool evaluate() const override;

private:
	Port const & m_port;
};


/****************************************************************************/


inline InputPortElement::InputPortElement(Port const & _port)
	:m_port(_port)
{};

inline bool InputPortElement::evaluate() const
{
	return m_port.getValue();
};


#endif // _INPUT_PORT_ELEMENT_HPP_