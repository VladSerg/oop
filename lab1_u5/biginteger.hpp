#ifndef _BIGINTEGER_HPP_
#define _BIGINTEGER_HPP_

#include <string>

// ���������� ����� ��� ������ � �������� ������ ������� BigInteger, ������� �� ���������� � ������� ������������� ���� ������, � �������� � ���� ��������. ��� ���� ������� ������� ����������� � ������ �0, ��������� � ������ �1 � �.�. 
//��� ��������� ������, �������, ��� ����� �������� ������������.������������� �������������� ������������ � ��������� ����������� � ���������� � ��������� Internet - �����������.

class BigInteger
{
private:

	std::string data;

	std::string getStringBigIntegerWithoutZeros() const;
	bool IsCorrectIndex(int _index) const;

public:

	// ������ � �������� ������
	std::string getBigInteger() const;

	// �����������, ����������� ������������ ����� ���������� �������� � �����.��� ������� ���������� ����������.� ������ �������� ����� ��������, 
	// �� ����������� �������������, ������������ ���������� std::logic_error � ������� �Invalid size�.
	BigInteger( int _size );

	// �����������, ����������� �������� ����� � ���� ������ � ���������� ������� ���������.����� �������� ������������ �������������. ���� ������ �������� 
	// ������������ ������� - ������ �������������� ���������� std::logic_error  � ������� �Not a number�.
	BigInteger( std::string _number );

	// ����������� �����. 
	// 
	
	// ����������.
	// 

	// �������� ����������.
	// 

	// ����� getNumDigits(), ������������ �����������(�.�., ���������� ���������� ����) � �������� ������.
	int getNumDigits() const { return this->data.size(); };

	// ������������� ��������� ��������� : <. <= , >, >= , == , != .
	bool operator == (const BigInteger & _bi) const;
	bool operator != (const BigInteger & _bi) const;
	bool operator < (const BigInteger & _bi) const;
	bool operator <= (const BigInteger & _bi) const;
	bool operator > (const BigInteger & _bi) const;
	bool operator >= (const BigInteger & _bi) const;

	// ������������� �������� ��������� �������[] � ���� ��������� - � ������ ������ �� ������ � � ������ �� ������, ������� ��������� 
	// ������� / ���������� ���������� ���������� ����� �� �������� ����� �� ����������� ������� �����.� ������ �������� ������������� 
	//������� ������� ������������� ���������� std::logic_error � ������� �Out of range�.
	char operator [] (int _index) const;
	char & operator [] (int _index);

	// ������ char getDigit(int) � setDigit(int, char) ������� � ��������� �������� ������� � ���������� ������� � ������� �����.
	// � ������ �������� ������������� ������ ������� ������� ������������� ���������� std::logic_error � ������� �Out of range�.
	char getDigit(int _index) const;
	void setDigit(int _index, char _x);
	
	// ������������� �������� �������������� � ���� bool, ������������ false, ����� ����� ����� 0 �� �������� �� ��� �������, � true � ��������� ������.
	explicit operator bool()const { return !(getBigInteger() == "0"); };
	
	// ������������� �������� += � ���� ��������� - ����������� ����� ���� int � �������� ��������� � ������ ��������, ������ ������� ����� �� ������ ��������.
	BigInteger & operator += (int _v);
	BigInteger & operator += (const BigInteger & _v);

	// ����������� ���� ������������� ���������� + , ������������ ������ ����� - ����� �� ��������.
	BigInteger operator + (int _v) const;
	BigInteger operator + (BigInteger _v) const;

	// ������������� ���������� �������� ������ << ����� � �����.�������������� ����� � ���������� ������� ���������.
	// � ��������� �������.

	// ������������� ���������� �������� ����� >> ����� �� ������(������ � ���������� ������� ���������).
	// � ���������� �������.

	// ������������� ���������� ��������, ����������� ������ � ����� �, ����������� ���������� ���������������� �������� ���� BigInteger, 
	// ������� ��� 1234567890987654321_big(��� �������, �������� �� �������� - ������).
	// � ���������� �������.
};

#endif //  _BIGINTEGER_HPP_
