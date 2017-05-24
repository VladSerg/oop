#ifndef _DATETIME_HPP_
#define _DATETIME_HPP_

#include <iostream>

class Date
{

public:

	Date( int _year, int _month );
	
	int getYear() const;
	int getMonth() const;
	
	bool operator == ( Date _d ) const;
	bool operator != ( Date _d ) const;
	bool operator < ( Date _d ) const;
	bool operator <= ( Date _d ) const;
	bool operator > ( Date _d ) const;
	bool operator >= ( Date _d ) const;

private:

	bool isValid() const;
	int m_year, m_month;

};

std::ostream & operator << ( std::ostream & o, Date d );

#endif // _DATETIME_HPP_
