#include "Serializer.hpp"
#include <iostream>

int main()
{
	Data data;
	data.id = 42;
	data.name = "Ali";
	data.value = 3.14;

	std::cout << "Original address: " << &data << std::endl;
	std::cout << "Original values:  " << data.id << ", " << data.name << ", " << data.value << std::endl;

	uintptr_t raw = Serializer::serialize(&data);
	std::cout << "Serialized:       " << raw << std::endl;

	Data* ptr = Serializer::deserialize(raw);
	std::cout << "Restored address: " << ptr << std::endl;
	std::cout << "Restored values:  " << ptr->id << ", " << ptr->name << ", " << ptr->value << std::endl;

	if (ptr == &data)
		std::cout << "Success: pointers match!" << std::endl;
	else
		std::cout << "Error: pointers do not match!" << std::endl;

	return 0;
}
