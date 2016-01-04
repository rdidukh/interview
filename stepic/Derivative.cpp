#include <iostream>
#include <map>
#include <string>
#include <cassert>
#include <sstream>

std::map<unsigned, int> strToPoly(const std::string & str)
{
	std::map<unsigned, int> poly;
	poly[0] = 0;

	enum State
	{
		Coef,
		Power,
	};

	State state = Coef;
	int coef = 0;
	unsigned power = 0;
	int sign = 1;

	for(auto c: str)
	{
		if(c == '-' || c == '+')
		{
			sign = (c=='+')? 1 : -1;
			poly[power] += sign*coef;
			state = Coef;
			coef = 0;
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
			if(c >= '0' && c <= '9')
			{
				power *= 10;
				power += c - '0';
			}
			else if(c == '^')
			{
				power = 0;
			}
			else
			{
				assert(false);
			}
		}	
	}

	return poly;
}

void powerToStr(std::ostringstream & ss, unsigned power, int coef, bool printPlus = true)
{
	if(printPlus && coef > 0)
	{
		ss << '+';
	}

	if(coef != 1 && coef != -1)
	{
		ss << coef;
		if(power > 0)
			ss << '*';
	}
	else
	{
		if(power > 0 && coef == -1)
			ss << '-';
		else if(power == 0)
			ss << coef;
	}

	if(power == 1)
	{
		ss << 'x';
	}
	else if(power > 1)
	{
		ss << "x^" << power;
	}
}

std::string polyToStr(std::map<unsigned, int> & poly)
{
	if(poly.empty()) return std::string("");
	std::ostringstream ss;
	auto it = poly.rbegin();

	powerToStr(ss, it->first, it->second, false);

	++it;
	while(it != poly.rend())
	{
		powerToStr(ss, it->first, it->second);
		++it;
	}
	return ss.str();
}

std::map<unsigned, int> df(const std::map<unsigned, int> & poly)
{
	std::map<unsigned, int> result;
	result[0] = 0;

	for(const auto & x: poly)
	{
		if(x.first != 0)
		{
			result[x.first-1] = x.first * x.second;
		} 
	}

	return result;
}

void debugPrint(const std::map<unsigned, int> & poly)
{
	for(const auto & x: poly)
	{
		std::cout << x.first << "->" << x.second << "  ";
	}
	std::cout << std::endl;
}

std::string derivative(std::string str)
{
	std::cout << "input: " << str << std::endl;
	auto inPoly = strToPoly(str);
	debugPrint(inPoly);
	auto outPoly = df(inPoly);
	debugPrint(inPoly);
	std::string result = polyToStr(outPoly);
	std::cout << "result: " << result << std::endl;
    return result;
}

#include "test.h"

int main(int argc, char * argv[])
{
	ASSERT_EQ("0", derivative("0"));
	ASSERT_EQ("0", derivative("5"));
	ASSERT_EQ("0", derivative("-5"));
	ASSERT_EQ("0", derivative("+5"));
	ASSERT_EQ("0", derivative("234"));
	ASSERT_EQ("0", derivative("-234"));
	ASSERT_EQ("0", derivative("+234"));	
	ASSERT_EQ("1", derivative("x"));
	ASSERT_EQ("1", derivative("+x"));
	ASSERT_EQ("-1", derivative("-x"));
	ASSERT_EQ("2", derivative("2*x"));
	ASSERT_EQ("543", derivative("543*x"));
	ASSERT_EQ("-543", derivative("-543*x"));
	ASSERT_EQ("256", derivative("256*x^1"));
	ASSERT_EQ("-256", derivative("-256*x^1"));
	ASSERT_EQ("13*x^12", derivative("x^13"));
	ASSERT_EQ("13*x^12", derivative("1*x^13"));
	ASSERT_EQ("-13*x^12", derivative("-x^13"));
	ASSERT_EQ("16*x^3", derivative("4*x^4"));
	ASSERT_EQ("-1300*x^99", derivative("-13*x^100"));
	ASSERT_EQ("2*x+1", derivative("x^2+x"));
	ASSERT_EQ("200*x^99+200*x", derivative("2*x^100+100*x^2"));
	ASSERT_EQ("10000*x^9999+1", derivative("x^10000+x+1"));
	ASSERT_EQ("-3*x^2-2*x", derivative("-x^2-x^3"));
	ASSERT_EQ("10", derivative("x+x+x+x+x+x+x+x+x+x"));
	ASSERT_EQ("-1", derivative("-x+x-x+x-x+x-x+x-x+x-x"));

	std::cout << "OK" << std::endl;
	return 0;
}
