#ifndef _PORT_HPP_
#define _PORT_HPP_

#include <string>
#include "messages.hpp"

class Port
{
public:
	virtual ~Port() = default;
	Port(const Port &) = delete;
	Port & operator = (const Port &) = delete;
	
	
	virtual bool getValue() const { return false; };
	virtual bool setPort(bool _value) { throw std::logic_error(Messages::CantSetPort); };
	std::string const & getName() const { return m_name; };

	bool IsValidName(std::string const & _name) const;

protected:
	Port(std::string const & _name);

private:
	const std::string m_name;
};


/****************************************************************************/


inline Port::Port(std::string const & _name)
	:m_name(_name)
{
	if (_name.empty() || !IsValidName(_name))
		throw std::logic_error(Messages::InvalidPortName);
};


inline bool Port::IsValidName(std::string const & _name) const //?
{
	for (char curent : _name)
		if (!((curent >= 'A' && curent <= 'Z') || (curent >= 'a' && curent <= 'z') || (curent >= '0' && curent <= '9')))
			return false;
	return true;
}

#endif // _PORT_HPP_