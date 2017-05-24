#ifndef _INPUT_PORT_HPP
#define _INPUT_PORT_HPP

#include "port.hpp"
 
class InputPort : public Port
{
public:
	InputPort(const std::string & _name, bool _value);
	bool setPort(bool _value);
	virtual bool getValue() const { return m_value; };

private:
	bool m_value;
};


/****************************************************************************/


inline InputPort::InputPort(const std::string & _name, bool _value)
	:Port(_name), m_value(_value)
{};

inline bool InputPort::setPort(bool _value)
{
	m_value = _value;
	return true;
};

#endif // _INPUT_PORT_HPP