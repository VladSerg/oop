#include "biginteger.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>


// Возврат подстроки с удаленными в конце нулями
std::string BigInteger::getStringBigIntegerWithoutZeros()const
{
	std::string temp{ this->data };
	while (temp[temp.size() - 1] == '0')
	{
		temp.pop_back();
		if (temp.size() == 0)
			return "0";
	}
	return temp;
}

// Доступ к хранимой строке
std::string BigInteger::getBigInteger() const 
{
	std::string temp = BigInteger::getStringBigIntegerWithoutZeros();
	std::string _temp;
	for (int i = temp.size()-1; i >= 0; i--)
	{
		_temp.push_back(temp[i]);
	}
	
	return _temp;
}

BigInteger::BigInteger( int _size )
{
	if (_size <= 0)
	{
		throw std::logic_error("Invalid size");
	}
	data.resize( _size, '0' );
}

BigInteger::BigInteger( std::string _number )
{
	data.resize( _number.size() );

	for (int i = _number.size() - 1; i >= 0; i--)
	{
		if ( (_number[_number.size() - i - 1] >= 48) && (_number[_number.size() - i - 1] <= 57) )
			data[i] = _number[_number.size() - i - 1];
		else
		{
			throw std::logic_error("Not a number");
		}
	}
}

bool BigInteger::operator == (const BigInteger & _bi) const
{
	return ( this->getStringBigIntegerWithoutZeros() == _bi.getStringBigIntegerWithoutZeros() );
}

bool BigInteger::operator != (const BigInteger & _bi) const
{
	return !(*this == _bi);
}

bool BigInteger::operator < (const BigInteger & _bi) const
{
	const int size1 = this->getStringBigIntegerWithoutZeros().size();
	const int size2 = _bi.getStringBigIntegerWithoutZeros().size();
	
	if ( size1 < size2 )
		return true;
	else if (size1 == size2)
		for (int i = size1; i >= 0; i--)
		{
			if (this->data[i] < _bi.data[i])
				return true;
			else if (this->data[i] > _bi.data[i])
				return false;
		}
	return false;
}

bool BigInteger::operator > (const BigInteger & _bi) const
{
	return _bi < *this;
}

bool BigInteger::operator <= (const BigInteger & _bi) const
{
	return (*this < _bi) || (*this == _bi);
}

bool BigInteger::operator >= (const BigInteger & _bi) const
{
	return (_bi < *this) || (*this == _bi);
}

bool BigInteger::IsCorrectIndex(int _index) const
{
	return ( _index >= 0 && _index <= data.size() );
}

char BigInteger::operator [] (int _index) const
{
	return getDigit(_index);
}

char & BigInteger::operator [] (int _index)
{
	if (IsCorrectIndex(_index))
		return data[_index];

	throw std::logic_error("Out of range");
}

char BigInteger::getDigit(int _index) const
{
	if (IsCorrectIndex(_index))
		return data[_index];

	throw std::logic_error("Out of range");
}

void BigInteger::setDigit(int _index, char _x)
{
	if (IsCorrectIndex(_index))
	{
		data[_index] = _x;
		return;
	}
	throw std::logic_error("Out of range");
}

BigInteger & BigInteger::operator += (const BigInteger & _v)
{
	int dataSize1 = data.size();
	int dataSize2 = _v.data.size();

	if (dataSize1 >= dataSize2)
	{
		for (int i = 0; i < dataSize2; i++)
			data[i] = data[i] + _v.data[i] - '0';
	}
	else
	{
		for (int i = 0; i < dataSize1; i++)
			data[i] = data[i] + _v.data[i] - '0';
		data += _v.data.substr(dataSize1, dataSize2 - dataSize1);
	}

	dataSize1 = data.size();

	for (int i = 0; i < dataSize1 - 1; i++)
		if (data[i] > '9')
		{
			data[i + 1] ++;
			data[i] -= 10;
		}

	if (data[dataSize1 - 1] > '9')
	{
		data[dataSize1 - 1] -= 10;
		data.push_back('1');
	}
	return *this;
}

BigInteger & BigInteger::operator += (int _v)
{
	const int radix = 10;
	char buffer[10];
	std::string p;
	p = itoa(_v, buffer, radix);

	*this += BigInteger(p);
	return *this;
}

BigInteger BigInteger::operator + (BigInteger _v) const
{
	BigInteger result = *this;
	result += _v;
	return result;
}

BigInteger BigInteger::operator + (int _v) const
{
	BigInteger result = *this;
	result += _v;
	return result;
}
