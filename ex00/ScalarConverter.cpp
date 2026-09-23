#include "ScalarConverter.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <limits>
#include <cmath>

ScalarConverter::ScalarConverter()
{
}

ScalarConverter::ScalarConverter(const ScalarConverter& other)
{
	(void)other;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& rhs)
{
	(void)rhs;
	return *this;
}

ScalarConverter::~ScalarConverter()
{
}

void ScalarConverter::_printChar(double val, bool isSpecial)
{
	std::cout << "char: ";
	if (isSpecial || val != val || val < 0 || val > 127
		|| val == std::numeric_limits<double>::infinity()
		|| val == -std::numeric_limits<double>::infinity())
	{
		std::cout << "impossible" << std::endl;
	}
	else if (!std::isprint(static_cast<int>(val)))
	{
		std::cout << "Non displayable" << std::endl;
	}
	else
	{
		std::cout << "'" << static_cast<char>(val) << "'" << std::endl;
	}
}

void ScalarConverter::_printInt(double val, bool isSpecial)
{
	std::cout << "int: ";
	if (isSpecial || val != val
		|| val < static_cast<double>(std::numeric_limits<int>::min())
		|| val > static_cast<double>(std::numeric_limits<int>::max()))
	{
		std::cout << "impossible" << std::endl;
	}
	else
	{
		std::cout << static_cast<int>(val) << std::endl;
	}
}

void ScalarConverter::_printFloat(double val, bool isSpecial)
{
	std::cout << "float: ";
	if (isSpecial || val != val || val == std::numeric_limits<double>::infinity() || val == -std::numeric_limits<double>::infinity())
	{
		if (val != val)
			std::cout << "nanf" << std::endl;
		else if (val > 0)
			std::cout << "+inff" << std::endl;
		else
			std::cout << "-inff" << std::endl;
	}
	else
	{
		float f = static_cast<float>(val);
		if (f == std::numeric_limits<float>::infinity())
			std::cout << "+inff" << std::endl;
		else if (f == -std::numeric_limits<float>::infinity())
			std::cout << "-inff" << std::endl;
		else if (std::floor(f) == f)
		{
			std::cout << std::fixed << std::setprecision(1) << f << "f" << std::endl;
			std::cout.unsetf(std::ios::fixed);
		}
		else
		{
			std::cout.unsetf(std::ios::fixed);
			std::cout << f << "f" << std::endl;
		}
	}
}

void ScalarConverter::_printDouble(double val, bool isSpecial)
{
	std::cout << "double: ";
	if (isSpecial || val != val || val == std::numeric_limits<double>::infinity() || val == -std::numeric_limits<double>::infinity())
	{
		if (val != val)
			std::cout << "nan" << std::endl;
		else if (val > 0)
			std::cout << "+inf" << std::endl;
		else
			std::cout << "-inf" << std::endl;
	}
	else
	{
		if (val == std::numeric_limits<double>::infinity())
			std::cout << "+inf" << std::endl;
		else if (val == -std::numeric_limits<double>::infinity())
			std::cout << "-inf" << std::endl;
		else if (std::floor(val) == val)
		{
			std::cout << std::fixed << std::setprecision(1) << val << std::endl;
			std::cout.unsetf(std::ios::fixed);
		}
		else
		{
			std::cout.unsetf(std::ios::fixed);
			std::cout << val << std::endl;
		}
	}
}

void ScalarConverter::convert(const std::string& literal)
{
	if (literal.empty())
	{
		std::cout << "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible" << std::endl;
		return;
	}

	// Pseudo-literals
	if (literal == "nan" || literal == "nanf")
	{
		double val = std::numeric_limits<double>::quiet_NaN();
		_printChar(val, true);
		_printInt(val, true);
		_printFloat(val, true);
		_printDouble(val, true);
		return;
	}
	if (literal == "+inf" || literal == "+inff" || literal == "inf" || literal == "inff")
	{
		double val = std::numeric_limits<double>::infinity();
		_printChar(val, true);
		_printInt(val, true);
		_printFloat(val, true);
		_printDouble(val, true);
		return;
	}
	if (literal == "-inf" || literal == "-inff")
	{
		double val = -std::numeric_limits<double>::infinity();
		_printChar(val, true);
		_printInt(val, true);
		_printFloat(val, true);
		_printDouble(val, true);
		return;
	}

	// Quoted char literal (e.g. 'c', 'a', '0', '*')
	if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')
	{
		double val = static_cast<double>(literal[1]);
		_printChar(val, false);
		_printInt(val, false);
		_printFloat(val, false);
		_printDouble(val, false);
		return;
	}

	// Single char literal without quotes (e.g. non-digit character like a, z, *)
	if (literal.length() == 1 && !std::isdigit(static_cast<unsigned char>(literal[0])))
	{
		double val = static_cast<double>(literal[0]);
		_printChar(val, false);
		_printInt(val, false);
		_printFloat(val, false);
		_printDouble(val, false);
		return;
	}

	// Numeric parsing
	char* endPtr = NULL;
	double val = std::strtod(literal.c_str(), &endPtr);

	if (endPtr == literal.c_str())
	{
		std::cout << "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible" << std::endl;
		return;
	}

	// Allow trailing 'f' or 'F' for float literals
	if (*endPtr != '\0' && !((*endPtr == 'f' || *endPtr == 'F') && *(endPtr + 1) == '\0'))
	{
		std::cout << "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible" << std::endl;
		return;
	}

	_printChar(val, false);
	_printInt(val, false);
	_printFloat(val, false);
	_printDouble(val, false);
}
