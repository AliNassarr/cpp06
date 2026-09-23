#include "ScalarConverter.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <limits>
#include <cmath>

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& rhs) { (void)rhs; return *this; }
ScalarConverter::~ScalarConverter() {}

void ScalarConverter::convert(const std::string& literal)
{
	double val = 0.0;
	bool isSpecial = false;

	// 1. Quoted char ('a') or single char (a)
	if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')
		val = static_cast<double>(literal[1]);
	else if (literal.length() == 1 && !std::isdigit(static_cast<unsigned char>(literal[0])))
		val = static_cast<double>(literal[0]);
	// 2. Pseudo-literals
	else if (literal == "nan" || literal == "nanf" || literal == "NAN" || literal == "NANF")
	{
		val = std::numeric_limits<double>::quiet_NaN();
		isSpecial = true;
	}
	else if (literal == "+inf" || literal == "+inff" || literal == "inf" || literal == "inff" || literal == "+INF" || literal == "+INFF" || literal == "INF" || literal == "INFF")
	{
		val = std::numeric_limits<double>::infinity();
		isSpecial = true;
	}
	else if (literal == "-inf" || literal == "-inff" || literal == "-INF" || literal == "-INFF")
	{
		val = -std::numeric_limits<double>::infinity();
		isSpecial = true;
	}
	// 3. Regular numeric parsing
	else
	{
		char* endPtr = NULL;
		val = std::strtod(literal.c_str(), &endPtr);
		if (endPtr == literal.c_str() || (*endPtr != '\0' && !((*endPtr == 'f' || *endPtr == 'F') && *(endPtr + 1) == '\0')))
		{
			std::cout << "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible" << std::endl;
			return;
		}
	}

	// Print char
	std::cout << "char: ";
	if (isSpecial || val != val || val < 0 || val > 127)
		std::cout << "impossible" << std::endl;
	else if (!std::isprint(static_cast<int>(val)))
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "'" << static_cast<char>(val) << "'" << std::endl;

	// Print int
	std::cout << "int: ";
	if (isSpecial || val != val || val < static_cast<double>(std::numeric_limits<int>::min()) || val > static_cast<double>(std::numeric_limits<int>::max()))
		std::cout << "impossible" << std::endl;
	else
		std::cout << static_cast<int>(val) << std::endl;

	// Print float
	std::cout << "float: ";
	if (val != val)
		std::cout << "nanf" << std::endl;
	else if (val == std::numeric_limits<double>::infinity())
		std::cout << "+inff" << std::endl;
	else if (val == -std::numeric_limits<double>::infinity())
		std::cout << "-inff" << std::endl;
	else
	{
		float f = static_cast<float>(val);
		if (std::floor(f) == f)
			std::cout << std::fixed << std::setprecision(1) << f << "f" << std::endl;
		else
			std::cout << f << "f" << std::endl;
		std::cout.unsetf(std::ios::fixed);
	}

	// Print double
	std::cout << "double: ";
	if (val != val)
		std::cout << "nan" << std::endl;
	else if (val == std::numeric_limits<double>::infinity())
		std::cout << "+inf" << std::endl;
	else if (val == -std::numeric_limits<double>::infinity())
		std::cout << "-inf" << std::endl;
	else
	{
		if (std::floor(val) == val)
			std::cout << std::fixed << std::setprecision(1) << val << std::endl;
		else
			std::cout << val << std::endl;
		std::cout.unsetf(std::ios::fixed);
	}
}
