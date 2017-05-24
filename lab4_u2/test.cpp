#include "testslib.hpp"
#include "messages.hpp"
#include "combinationalcircuit.hpp"
#include <iostream>
#include "messages.hpp"

DECLARE_OOP_TEST(input_ports_test)
{
	CombinationCircuit circuit;
	circuit.addInputPort("a");
	circuit.addInputPort("b", false);
	circuit.addInputPort("c", true);
	assert(circuit.showPort("a") == false);
	assert(circuit.showPort("b") == false);
	assert(circuit.showPort("c") == true);


	ASSERT_THROWS(
		circuit.addInputPort("a"),
		Messages::PortAlreadyExists);

	ASSERT_THROWS(
		circuit.addInputPort("a", true),
		Messages::PortAlreadyExists);

	ASSERT_THROWS(
		circuit.addInputPort("b"),
		Messages::PortAlreadyExists);

	ASSERT_THROWS(
		circuit.addInputPort("c"),
		Messages::PortAlreadyExists);

	circuit.setPort("a", true);
	assert(circuit.showPort("a") == true);

	ASSERT_THROWS(
		circuit.addInputPort("a 2"),
		Messages::InvalidPortName);
}

DECLARE_OOP_TEST(output_ports_test)
{
	CombinationCircuit circuit;
	circuit.addOutputPort("a");
	
	ASSERT_THROWS(
		circuit.setPort("a", true),
		Messages::CantSetPort);

	assert(circuit.showPort("a") == false);

	ASSERT_THROWS(
		circuit.addOutputPort("-15 dj"),
		Messages::InvalidPortName);
}

DECLARE_OOP_TEST(unaryelement_test)
{
	CombinationCircuit circuit;
	Port const & portA = circuit.addInputPort("a", false);
	Port const & portB = circuit.addInputPort("b", true);

	Element const & element1 = circuit.addInputPortElement(portA);
	Element const & element2 = circuit.addInputPortElement(portB);

	circuit.addOutputPort("c", &element1);
	circuit.addOutputPort("d", &element2);

	assert(circuit.showPort("c") == false);
	assert(circuit.showPort("d") == true);

}