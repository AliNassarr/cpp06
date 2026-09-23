#include "Identify.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	std::cout << "=== Generating and Identifying Random Types ===" << std::endl;
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

	return 0;
}
