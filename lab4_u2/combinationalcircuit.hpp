#ifndef _COMBINATION_CIRCUIT_HPP_
#define _COMBINATION_CIRCUIT_HPP_

#include "inputport.hpp"
#include "outputport.hpp"

#include "unaryelement.hpp"
#include "inputportelement.hpp"

#include <unordered_map>
#include <string>
#include <memory>


class CombinationCircuit
{
public:
	CombinationCircuit() = default;
	~CombinationCircuit() = default;
	CombinationCircuit(const CombinationCircuit &) = delete;
	CombinationCircuit & operator = (const CombinationCircuit &) = delete;


	Port const & addInputPort(const std::string & _name, bool _value = false);
	Port const & addOutputPort(const std::string & _name, Element const * _element = nullptr);
	void setPort(const std::string & _name, bool _value);
	bool showPort(const std::string & _name);

	Element const & addInputPortElement(Port const & _port);
	Element const & addUnaryElement(UnaryElement::Action _action, Element const & _element);
	Element const & addBinaryElement();



private:
	std::unordered_map<std::string, std::unique_ptr<Port>> m_ports;
	std::vector<std::unique_ptr<Element>> m_elements;

	Port * findPort(std::string const & _name) const;
};


#endif //_COMBINATION_CIRCUIT_HPP_

/*
����������� �����, �������������� ��� ���������� ��������(Element) :
	�������� ����������� ����������;
	�������� ����� ����������� ����� evaluate, ������������ �������� �� ������ ��������(false ��� true);

����������� �����, �������������� ������������ ��������(UnaryElement) :
	�������� ����� � ��������� - ���������� - ��������� �� ������ Element ��� ��������������� �� �����������;
	�������� ��� �������� - ����� ��� ��������;
	��������� ����� evaluate � ������������ � ����� �������� :
		��� ������ = > ��������� �������� ���������;
		��� ��������� = > ���������� ���������� ��������� �������� ���������;

����������� �����, �������������� ������������ ��������(BinaryElement) :
	�������� 2 ����� � ���������� - ����������� - ��������� �� ������� Element ��� ��������������� �� �����������;
�������� ��� �������� - AND, OR, XOR;
��������� ����� evaluate � ������������ � ����� ��������(�������������� ������ ������������ � ����������� ����� - &&, || , ^);

����������� �����, �������������� ������� ���� �����(InputPortElement) :
	�������� ����� � �������� - ������(������ �� ������ InputPort);
��������� ����� evaluate ����������� �������� ��������, �������������� � �����


���������� �����, �������������� �������������� ����� - CombinationalCircuit:
������� �� ������ ��������� - ��������� �� ������� Element � ���������������� �� �����������;
������� �� ������(�������) ������ - ��������� �� ������� Port � ���������������� �� �����������;


������� �����, �������������� ������� ���� �����(Port) :
	�������� ��� �����;
����� ����������� ����� getValue(), ����������� ��� ������� ��������;

����������� �����, �������������� ����� ������� ���� �����(InputPort) :
	�������� ���������� ���� bool, �������� �������� ����� ��������, �� ��������� false;
����� ����� ��� ��������� �������� ��������;
���������� ������� �������� � ���������� ������ getValue();

����������� �����, �������������� ����� �������� ���� �����(OutputPort) :
	����� ����������� ����� � �������� - ���������, ��� �������� �� ���������� �� ����� �����;
��� ���������� ������ getValue() :
	��� ������� �����, ����������� �������� � ��������������� ��������;
��� ������� �����, ���������� false

�������� ��������� ���� �simulation.txt�, ���������� �������� �� ����� �������� ����������� :

SET_INPUT a true
SET_INPUT b false
SHOW_PORT c

������������ �������� ���������� ���������, ������������ ������������� �������� :
�������� �������, ������� ������� ������� ����� ������������� �������������� ����� �� ��� �����, ��������� �� ����� ������������� �������(��������, ������������� � 4 ������� ������, 2 ������� ���������� � 1 �������);
���������� ������ �� ����� �simulation.txt� � ���������� ���������� ������� :
������� SET_INPUT ������ ������������� ������� �������� ���������� �������� �����(����������� ��� ��������� ����� ������)
������� SHOW_PORT ������ �������� �� ������� ��������� � ������� �������� ���������� �����(����������� ��� ��������� ����� ������);
��������� � ������������ ����������� ����� ��������� � �����������, ��������� �� ������ ����� ������������� �������;
��������� ���������� ��� ������� ������.
*/