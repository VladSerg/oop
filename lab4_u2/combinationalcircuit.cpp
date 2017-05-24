#include "combinationalcircuit.hpp"

Port const & CombinationCircuit::addInputPort(const std::string & _name, bool _value)
{
	if (findPort(_name))
		throw std::logic_error(Messages::PortAlreadyExists);

	InputPort * result = new InputPort(_name, _value);
	m_ports[_name] = std::unique_ptr<InputPort>(result);
	return *result;
}

Port const & CombinationCircuit::addOutputPort(const std::string & _name, Element const * _element)
{
	if (findPort(_name))
		throw std::logic_error(Messages::PortAlreadyExists);

	OutputPort * result = new OutputPort(_name, _element);
	m_ports[_name] = std::unique_ptr<OutputPort>(result);
	return *result;
}

void CombinationCircuit::setPort(const std::string & _name, bool _value)
{
	if (!m_ports[_name]->setPort(_value))
		throw std::logic_error(Messages::PortIsntExists);
}

bool CombinationCircuit::showPort(const std::string & _name)
{
	if (!findPort(_name))
		throw std::logic_error(Messages::PortIsntExists);

	return m_ports[_name]->getValue();
}

Element const & CombinationCircuit::addInputPortElement(Port const & _port)
{
	InputPortElement * result = new InputPortElement(_port);
	m_elements.push_back(std::unique_ptr<InputPortElement>(result));
	return *result;
}

Element const & CombinationCircuit::addUnaryElement(UnaryElement::Action _action, Element const & _element)
{
	UnaryElement * result = new UnaryElement(_action, _element);
	m_elements.push_back(std::unique_ptr<UnaryElement>(result));
	return *result;
}




Port * CombinationCircuit::findPort(std::string const & _name) const
{
	auto it = m_ports.find(_name);
	return (it == m_ports.end()) ? nullptr : it->second.get();
}