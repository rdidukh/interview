#include <iostream>

#define RED_COLOR 	"\033[0;31m"
#define GREEN_COLOR	"\033[0;32m"
#define NO_COLOR	"\033[0m"

#define ASSERT_NULL(x) \
	do {	\
		if((x) != NULL) \
		{	\
			std::cerr << RED_COLOR << "FAIL: " #x " != NULL" << NO_COLOR << std::endl;	\
			exit(1);	\
		} else { \
			std::cout << GREEN_COLOR << "OK: " #x " == NULL" << NO_COLOR << std::endl;	\
		} \
	} while(0);

#define ASSERT_NOTNULL(x) \
	do {	\
		if((x) == NULL) \
		{	\
			std::cerr << RED_COLOR << "FAIL: " #x " == NULL" << NO_COLOR << std::endl;	\
			exit(1);	\
		} else { \
			std::cout << GREEN_COLOR << "OK: " #x " != NULL" << NO_COLOR << std::endl;	\
		} \
	} while(0);

template<typename U, typename V> 
void assert_eq(const U & expected, const V & actual, const char * expStr, const char * actStr)
{
	if(actual != expected)
	{
		std::cerr << RED_COLOR << "FAIL: " << actStr << " != " << expStr << NO_COLOR << std::endl; \
		std::cerr << actStr << ": " << std::endl;	\
		std::cerr << "Expected: " << expected << std::endl; \
		std::cerr << "Actual: " << actual << std::endl; \
		exit(1);	\
	} else { \
		std::cout << GREEN_COLOR << "OK: " << actStr << " == " << expStr << NO_COLOR << std::endl; \
	}	\
}

#define ASSERT_EQ(expected, actual) \
	do {	\
		assert_eq(expected, actual, #expected, #actual); \
	} while(0);
