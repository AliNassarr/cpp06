#include "Identify.hpp"
#include <iostream>
#include <cstdlib>
#include <exception>

Base* generate()
{
	int choice = std::rand() % 3;

	switch (choice)
	{
		case 0:
			std::cout << "[Factory] Instantiated type A" << std::endl;
			return new A();
		case 1:
			std::cout << "[Factory] Instantiated type B" << std::endl;
			return new B();
		default:
			std::cout << "[Factory] Instantiated type C" << std::endl;
			return new C();
	}
}

void identify(Base* p)
{
	if (p == NULL)
	{
		std::cout << "Null pointer passed" << std::endl;
		return;
	}

	if (dynamic_cast<A*>(p) != NULL)
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p) != NULL)
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p) != NULL)
		std::cout << "C" << std::endl;
	else
		std::cout << "Unknown type" << std::endl;
}

void identify(Base& p)
{
	try
	{
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
		return;
	}
	catch (const std::exception&)
	{
	}

	try
	{
		(void)dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
		return;
	}
	catch (const std::exception&)
	{
	}

	try
	{
		(void)dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
		return;
	}
	catch (const std::exception&)
	{
		std::cout << "Unknown type" << std::endl;
	}
}
