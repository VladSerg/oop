#include "datetime.hpp"
#include "messages.hpp"

Date::Date( int _year, int _month )
	: m_year( _year ), m_month( _month )
{
	if ( !isValid() )
		throw std::logic_error( Messages::InvalidDateTime );
}

int Date::getYear() const
{
	return m_year;
}

int Date::getMonth() const
{
	return m_month;
}

bool Date::operator == ( Date d ) const
{
	return m_year == d.getYear()
		&& m_month == d.getMonth();
}

bool Date::operator != ( Date d ) const
{
	return !( *this == d );
}

bool Date::operator < ( Date d ) const
{
	if ( m_year < d.getYear() )
		return true;

	else if ( m_year == d.getYear() )
	{
		if ( m_month < d.getMonth() )
			return true;

		else if ( m_month == d.getMonth() )
		{
			return true;
		}
	}

	return false;
}

bool Date::operator > ( Date d ) const
{
	return d < *this;
}

bool Date::operator <= ( Date d ) const
{
	return ( *this < d ) || ( *this == d );
}

bool Date::operator >= ( Date d ) const
{
	return ( d < *this ) || ( *this == d );
}

bool Date::isValid() const
{
	if ( m_year == 0 )
		return false;

	if ( m_month < 1 || m_month > 12 )
		return false;

	return true;
}

std::ostream & operator << ( std::ostream & o, const Date & d )
{
	o << d.getYear() << '/' << d.getMonth();
	
	return o;
}