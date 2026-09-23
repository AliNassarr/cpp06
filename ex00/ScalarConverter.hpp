#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>

class ScalarConverter
{
public:
	static void convert(const std::string& literal);

private:
	ScalarConverter();
	ScalarConverter(const ScalarConverter& other);
	ScalarConverter& operator=(const ScalarConverter& rhs);
	~ScalarConverter();

	static void _printChar(double val, bool isSpecial);
	static void _printInt(double val, bool isSpecial);
	static void _printFloat(double val, bool isSpecial);
	static void _printDouble(double val, bool isSpecial);
};

#endif
