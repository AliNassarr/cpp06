#include "Serializer.hpp"
#include <iostream>

int main()
{
	Data originalData;
	originalData.id = 101;
	originalData.name = "Alnassar's Record";
	originalData.value = 99.95;

	std::cout << "=== Original Data Object ===" << std::endl;
	std::cout << "Address: " << &originalData << std::endl;
	std::cout << "ID:      " << originalData.id << std::endl;
	std::cout << "Name:    " << originalData.name << std::endl;
	std::cout << "Value:   " << originalData.value << std::endl;

	std::cout << "\n=== Serialization ===" << std::endl;
	uintptr_t raw = Serializer::serialize(&originalData);
	std::cout << "Serialized integer (uintptr_t): 0x" << std::hex << raw << std::dec << std::endl;

	std::cout << "\n=== Deserialization ===" << std::endl;
	Data* restoredPtr = Serializer::deserialize(raw);
	std::cout << "Restored address: " << restoredPtr << std::endl;
	std::cout << "ID:               " << restoredPtr->id << std::endl;
	std::cout << "Name:             " << restoredPtr->name << std::endl;
	std::cout << "Value:            " << restoredPtr->value << std::endl;

	if (restoredPtr == &originalData)
		std::cout << "\n[SUCCESS] Deserialized pointer matches original address exactly!" << std::endl;
	else
		std::cout << "\n[FAILURE] Pointers do not match!" << std::endl;

	return 0;
}
