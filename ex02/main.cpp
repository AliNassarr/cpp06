#include "Identify.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

class Unknown : public Base {};

int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	std::cout << "========================================" << std::endl;
	std::cout << "  TEST 1: 5 Random Type Identifications " << std::endl;
	std::cout << "========================================" << std::endl;
	for (int i = 0; i < 5; ++i)
	{
		std::cout << "\n--- Iteration " << (i + 1) << " ---" << std::endl;
		Base* instance = generate();

		std::cout << "Identify via pointer:   ";
		identify(instance);

		std::cout << "Identify via reference: ";
		identify(*instance);

		delete instance;
	}

	std::cout << "\n========================================" << std::endl;
	std::cout << "  TEST 2: NULL Pointer Identification   " << std::endl;
	std::cout << "========================================" << std::endl;
	std::cout << "Identify NULL pointer:  ";
	identify(static_cast<Base*>(NULL));

	std::cout << "\n========================================" << std::endl;
	std::cout << "  TEST 3: Unknown Derived Type Test     " << std::endl;
	std::cout << "========================================" << std::endl;
	Unknown unknown;
	std::cout << "Identify unknown via pointer:   ";
	identify(&unknown);
	std::cout << "Identify unknown via reference: ";
	identify(unknown);

	return 0;
}
