#include "Identify.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	for (int i = 0; i < 4; i++)
	{
		std::cout << "--- Test " << i + 1 << " ---" << std::endl;
		Base* ptr = generate();

		std::cout << "Identify pointer:   ";
		identify(ptr);

		std::cout << "Identify reference: ";
		identify(*ptr);

		delete ptr;
		std::cout << std::endl;
	}

	return 0;
}
