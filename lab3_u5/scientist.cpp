#include "scientist.hpp"
#include "messages.hpp"

Scientist::Scientist(std::string const & _name, Degree _degree)
	:name(_name), degree(_degree)
{
	if (name.empty())
		throw std::logic_error(Messages::InvalidScientistName);
	if (degree < 0 || degree > 2)
		throw std::logic_error(Messages::InvalidScientistDegree);
};