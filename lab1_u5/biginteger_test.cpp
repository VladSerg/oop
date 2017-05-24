#include "testslib.hpp"
#include "biginteger.hpp"

#include <sstream>


// ѕерегруженный глобальный оператор вывода << числа в поток.ѕредполагаетс€ вывод в дес€тичной системе счислени€.
std::ostream & operator << (std::ostream & o, BigInteger bi)
{
	o << bi.getBigInteger();
	return o;
}

// ѕерегруженный глобальный оператор ввода >> числа из потока(строка в дес€тичной системе счислени€).
std::istream & operator >> (std::istream & i, BigInteger & bi)
{
	std::string buf;
	std::getline(i,buf);
	BigInteger d (buf); 
	bi = d;
	return i;
}

// ѕерегруженный глобальный оператор, принимающий строку в стиле —, позвол€ющий определить пользовательские литералы типа BigInteger, 
// имеющие вид 1234567890987654321_big(без кавычек, несмотр€ на аргумент - строку).
BigInteger operator "" _big(const char * _string)
{
	std::string temp;
	temp += _string;
	return BigInteger(temp);
}

/*****************************************************************************/

DECLARE_OOP_TEST( biginteger_create )
{
    BigInteger t1( 25 );
	BigInteger t2( "00000034567876543234567654323456763563835" );
	assert(t1.getBigInteger() == "0");
	assert(t2.getBigInteger() == "34567876543234567654323456763563835");

}

/*****************************************************************************/

DECLARE_OOP_TEST( biginteger_create_error_0 )
{
	try
	{
		BigInteger t1("     ");

	}
	catch (const std::exception& _e)
	{
		std::cout << "Exeption: " << _e.what();
	}

}

/*****************************************************************************/

DECLARE_OOP_TEST( biginteger_create_error_1 )
{
	try
	{
		BigInteger t1(0);

	}
	catch (const std::exception& _e)
	{
		std::cout << "Exeption: " << _e.what();
	}
	
}

/*****************************************************************************/

DECLARE_OOP_TEST( biginteger_create_error_2 )
{
	try
	{
		BigInteger t1( "456789f67" );

	}
	catch (const std::exception& _e)
	{
		std::cout << "Exeption: " << _e.what();
	}
}

/*****************************************************************************/

DECLARE_OOP_TEST( biginteger_create_coppy )
{
	BigInteger t1("45678956453443567");
	BigInteger t2( t1 );	

	assert(t1.getBigInteger() == "45678956453443567");
	assert(t2.getBigInteger() == "45678956453443567");
	
}

/*****************************************************************************/

DECLARE_OOP_TEST( biginteger_operator_prisvoenia )
{
	BigInteger t1("45678956453443567");
	BigInteger t2(2);
	BigInteger t3(30);
	t2 = t1;
	t3 = t1;

	assert(t1.getBigInteger() == "45678956453443567");
	assert(t2.getBigInteger() == "45678956453443567");
	assert(t3.getBigInteger() == "45678956453443567");
}

/*****************************************************************************/

DECLARE_OOP_TEST(biginteger_operator_sravneniya1)
{
	BigInteger t1("45678956453443567");
	BigInteger t2("00045678956453443567");

	assert(t1 == t2);
}

/*****************************************************************************/

DECLARE_OOP_TEST(biginteger_operator_sravneniya2)
{
	BigInteger t1("45678956453443567");
	BigInteger t2("000567483");

	assert(t1 != t2);
}

/*****************************************************************************/

DECLARE_OOP_TEST(biginteger_operator_sravneniya3)
{
	BigInteger t1("45678956453443567");
	BigInteger t2("456789564534435671");
	BigInteger t3("45678957453443567");
	BigInteger t4("45678957453443568");
	assert(t1 < t2);
	assert(t1 < t3);
	assert(t3 < t4);
}

/*****************************************************************************/

DECLARE_OOP_TEST(biginteger_operator_sravneniya4)
{
	BigInteger t1("45678956453443567");
	BigInteger t2("456789564534435671");
	BigInteger t3("45678957453443567");
	BigInteger t4("45678957453443568");
	assert(t2 > t1);
	assert(t3 > t1);
	assert(t4 > t3);
}

/*****************************************************************************/

DECLARE_OOP_TEST(biginteger_operator_sravneniya5)
{
	BigInteger t1("45678956453443567");
	BigInteger t2("456789564534435671");
	BigInteger t3("45678957453443567");
	BigInteger t4("45678957453443568");
	BigInteger t5("45678957453443568");
	assert(t2 >= t1);
	assert(t3 >= t1);
	assert(t4 >= t3);
	assert(t4 >= t5);
	assert(t4 <= t5);
}

/*****************************************************************************/

DECLARE_OOP_TEST(biginteger_operator_sravneniya6)
{
	BigInteger t1("45678956453443567");
	BigInteger t2("456789564534435671");
	BigInteger t3("45678957453443567");
	BigInteger t4("45678957453443568");
	BigInteger t5("45678957453443568");
	assert(t1 <= t2);
	assert(t1 <= t3);
	assert(t3 <= t4);
	assert(t5 <= t4);
	assert(t5 >= t4);
}

/*****************************************************************************/

DECLARE_OOP_TEST(biginteger_operator_index1)
{
	BigInteger t1("45678956453443567");
	BigInteger t2("45678956453443560");
	t1[0] = '0';
	assert(t1 == t2);
}

/*****************************************************************************/

DECLARE_OOP_TEST(biginteger_operator_index2)
{
	BigInteger t1("45678956453443567");
	assert(t1[0] == '7');
	assert(t1[16] == '4');
}

/*****************************************************************************/

DECLARE_OOP_TEST(biginteger_operator_index_exeption)
{
	BigInteger t1("45678956453443567");
	char tmp ;

	try
	{
		tmp = t1[135];
	}
	catch (const std::exception& _e)
	{
		std::cout << "Exeption: " << _e.what();
	}
}

/*****************************************************************************/

DECLARE_OOP_TEST(biginteger_operator_index_exeption_2)
{
	BigInteger t1("45678956453443567");
	try
	{
		t1[135] = '3';
	}
	catch (const std::exception& _e)
	{
		std::cout << "Exeption: " << _e.what();
	}
}

/*****************************************************************************/

DECLARE_OOP_TEST(biginteger_getDigit)
{
	BigInteger t1("45678956453443567");
	assert(t1.getDigit(0) == '7');
	assert(t1.getDigit(16) == '4');
}

/*****************************************************************************/

DECLARE_OOP_TEST(biginteger_getDigit_exeption)
{
	BigInteger t1("45678956453443567");
	char tmp;
	try
	{
		tmp = t1.getDigit(135);
	}
	catch (const std::exception& _e)
	{
		std::cout << "Exeption: " << _e.what();
	}
}

/*****************************************************************************/

DECLARE_OOP_TEST(biginteger_setDigit)
{
	BigInteger t1("45678956453443567");
	t1.setDigit(4, '5');
	assert(t1.getDigit(4) == '5');
}

/*****************************************************************************/

DECLARE_OOP_TEST(biginteger_setDigit_exeption)
{
	BigInteger t1("45678956453443567");
	try
	{
		t1.setDigit(123, '3');
	}
	catch (const std::exception& _e)
	{
		std::cout << "Exeption: " << _e.what();
	}
}

/*****************************************************************************/

DECLARE_OOP_TEST(biginteger_print)
{
	BigInteger t1("00045678956453443567");
	std::cout << t1;
}

/*****************************************************************************/

DECLARE_OOP_TEST(biginteger_bool)
{
	BigInteger t1(10);
	BigInteger t2("1234");
	assert(!t1 && t2);
}

/*****************************************************************************/

DECLARE_OOP_TEST(biginteger_pr)
{
	BigInteger t1("9999");
	BigInteger t11("1");
	t1 += t11;
	assert(t1.getBigInteger() == "10000");
	BigInteger t2("8999");
	BigInteger t21("1");
	t2 += t21;
	assert(t2.getBigInteger() == "9000");
	BigInteger t3("9999");
	BigInteger t31("0");
	t3 += t31;
	assert(t3.getBigInteger() == "9999");

	BigInteger t32("9999");
	BigInteger t321(5);
	t32 += t321;
	assert(t32.getBigInteger() == "9999");


	BigInteger t4("9876");
	BigInteger t41("123");
	t4 += t41;
	assert(t4.getBigInteger() == "9999");

	BigInteger t5("9999");
	BigInteger t51("9999");
	t5 += t51;
	assert(t5.getBigInteger() == "19998");

	BigInteger t6("9999");
	BigInteger t61("99999999");
	t6 += t61;
	assert(t6.getBigInteger() == "100009998");
}

/*****************************************************************************/

DECLARE_OOP_TEST(biginteger_pr2)
{
	BigInteger t1("9999");
	t1 += 1;
	assert(t1.getBigInteger() == "10000");
	BigInteger t2("8999");
	t2 += 1;
	assert(t2.getBigInteger() == "9000");
	BigInteger t3("9999");
	t3 += 0;
	assert(t3.getBigInteger() == "9999");

	BigInteger t4("9876");
	t4 += 123;
	assert(t4.getBigInteger() == "9999");

	BigInteger t5("9999");
	t5 += 9999;
	assert(t5.getBigInteger() == "19998");

	BigInteger t6("9999");
	t6 += 99999999;
	assert(t6.getBigInteger() == "100009998");
}

/*****************************************************************************/

DECLARE_OOP_TEST(biginteger_pr3)
{
	BigInteger t1("9999");
	BigInteger t11("1");
	BigInteger summ1(1);
	summ1 = t1 + t11;
	assert(summ1.getBigInteger() == "10000");
	BigInteger t2("8999");
	BigInteger t21("1");
	BigInteger summ2(1);
	summ2 = t2 + t21;
	assert(summ2.getBigInteger() == "9000");
	BigInteger t3("9999");
	BigInteger t31("0");
	BigInteger summ3(1);
	summ3 = t3 + t31;
	assert(summ3.getBigInteger() == "9999");

	BigInteger t32("9999");
	BigInteger t321(5);
	BigInteger summ32(1);
	summ32 = t32 + t321;
	assert(summ32.getBigInteger() == "9999");


	BigInteger t4("9876");
	BigInteger t41("123");
	BigInteger summ4(1);
	summ4 = t4 + t41;
	assert(summ4.getBigInteger() == "9999");

	BigInteger t5("9999");
	BigInteger t51("9999");
	BigInteger summ5(1);
	summ5 = t5 + t51;
	assert(summ5.getBigInteger() == "19998");

	BigInteger t6("9999");
	BigInteger t61("99999999");
	BigInteger summ6(1);
	summ6 = t6 + t61;
	assert(summ6.getBigInteger() == "100009998");
}

/*****************************************************************************/

DECLARE_OOP_TEST(biginteger_pr4)
{
	BigInteger t1("9999");
	BigInteger summ1(1);
	summ1 = t1 + 1;
	assert(summ1.getBigInteger() == "10000");
	BigInteger t2("8999");
	BigInteger summ2(1);
	summ2 = t2 + 1;
	assert(summ2.getBigInteger() == "9000");
	BigInteger t3("9999");
	BigInteger summ3(1);
	summ3 = t3 + 0;
	assert(summ3.getBigInteger() == "9999");

	BigInteger t4("9876");
	BigInteger summ4(1);
	summ4 = t4 + 123;
	assert(summ4.getBigInteger() == "9999");

	BigInteger t5("9999");
	BigInteger summ5(1);
	summ5 = t5 + 9999;
	assert(summ5.getBigInteger() == "19998");

	BigInteger t6("9999");
	BigInteger summ6(1);
	summ6 = t6 + 99999999;
	assert(summ6.getBigInteger() == "100009998");
}

/*****************************************************************************/

DECLARE_OOP_TEST(biginteger_create_big1)
{
	BigInteger t1 = 1234567654323456_big;
	assert(t1.getBigInteger() == "1234567654323456");
}

/*****************************************************************************/

DECLARE_OOP_TEST(biginteger_read)
{
	BigInteger t1(5);

	std::stringstream ss( "1234567890" );
	ss >> t1;
	assert(t1.getBigInteger() == "1234567890");
}
