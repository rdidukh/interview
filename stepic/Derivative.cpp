#include <iostream>

#include "test.h"

std::map<unsigned, int> strToPoly(const string & str)
{
	std::map<unsigned, int> poly;
	poly[0] = 0;

	enum State
	{
		Coef,
		Power,
	};

	State state = Ready;
	int coef = 0;
	unsigned power = 0;
	int sign = 1;

	for(auto c: str)
	{
		if(c == '-' || c == '+')
		{
			sign = (c=='+')? 1 : -1;
			poly[power] += sign*coef;
			state = Ready;
			coef = 0
			power = 0;
		}
		else if(state == Coef)
		{
			if(c >= '0' && c <= '9')
			{
				coef *= 10;
				coef += c - '0';
			}
			else if(c == 'x')
			{
				coef = 1;
				state = Power;
			}
			else if(c == '*')
			{
				state = Power;
			}
			else
			{
				assert(false);
			}
		}
		else if(state == Power)
		{

		}

		
	}
}

std::string derivative(std::string polynomial)
{
    return (std::string)"";
}

int main(int argc, char * argv[])
{
	ASSERT_EQ("0", derivative("0"));
	ASSERT_EQ("5", derivative("0"));
	ASSERT_EQ("-5", derivative("0"));
	ASSERT_EQ("+5", derivative("0"));
	ASSERT_EQ("234", derivative("0"));
	ASSERT_EQ("-234", derivative("0"));
	ASSERT_EQ("+234", derivative("0"));	
	ASSERT_EQ("x", derivative("1"));
	ASSERT_EQ("+x", derivative("1"));
	ASSERT_EQ("-x", derivative("-1"));
	ASSERT_EQ("2*x", derivative("2"));
	ASSERT_EQ("543*x", derivative("543"));
	ASSERT_EQ("-543*x", derivative("-543"));
	ASSERT_EQ("256*x^1", derivative("256"));
	ASSERT_EQ("-256*x^1", derivative("-256"));
	ASSERT_EQ("x^13", derivative("13*x^12"));
	ASSERT_EQ("1*x^13", derivative("13*x^12"));
	ASSERT_EQ("-x^13", derivative("-13*x^12"));
	ASSERT_EQ("4*x^4", derivative("16*x^3"));
	ASSERT_EQ("-13*x^100", derivative("-1300*x^99"));
	ASSERT_EQ("x^2+x", derivative("2*x+1"));
	ASSERT_EQ("2*x^100+100*x^2", derivative("200*x^99+200*x"));
	ASSERT_EQ("x^10000+x+1", derivative("10000*x^9999+1"));
	ASSERT_EQ("-x^2-x^3", derivative("-3*x^2-2*x"));
	ASSERT_EQ("x+x+x+x+x+x+x+x+x+x", derivative("10"));
	ASSERT_EQ("-x+x-x+x-x+x-x+x-x+x-x", derivative("-1"));

	std::cout << "OK" << std::endl;
	return 0;
}
