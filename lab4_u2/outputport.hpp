#ifndef _OUTPUT_PORT_HPP_
#define _OUTPUT_PORT_HPP_

#include "port.hpp"
#include "element.hpp" //?


class OutputPort : public Port
{
public:
	OutputPort(const std::string & _name, Element const * _element);
	virtual bool getValue() const;

private:
	Element const * m_element;
};


/****************************************************************************/


inline OutputPort::OutputPort(const std::string & _name, Element const * _element)
	:Port(_name), m_element(_element)
{};

inline bool OutputPort::getValue() const
{
	if (!m_element)
		return false;
	return m_element->evaluate();// ?
};

#endif // _OUTPUT_PORT_HPP_