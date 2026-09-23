#include "Serializer.hpp"
#include <iostream>

int main()
{
	std::cout << "========================================" << std::endl;
	std::cout << "  TEST 1: Stack Allocated Data Object   " << std::endl;
	std::cout << "========================================" << std::endl;
	Data originalData;
	originalData.id = 101;
	originalData.name = "Alnassar's Record";
	originalData.value = 99.95;

	std::cout << "Original address: " << &originalData << std::endl;
	std::cout << "Original ID:      " << originalData.id << std::endl;
	std::cout << "Original Name:    " << originalData.name << std::endl;
	std::cout << "Original Value:   " << originalData.value << std::endl;

	uintptr_t raw = Serializer::serialize(&originalData);
	std::cout << "Serialized (uintptr_t): 0x" << std::hex << raw << std::dec << std::endl;

	Data* restoredPtr = Serializer::deserialize(raw);
	std::cout << "Restored address: " << restoredPtr << std::endl;
	std::cout << "Restored ID:      " << restoredPtr->id << std::endl;
	std::cout << "Restored Name:    " << restoredPtr->name << std::endl;
	std::cout << "Restored Value:   " << restoredPtr->value << std::endl;

	if (restoredPtr == &originalData)
		std::cout << "[PASS] Pointer matches original address exactly!" << std::endl;
	else
		std::cout << "[FAIL] Pointers do not match!" << std::endl;

	// Modify through restored pointer to prove it's the exact same memory
	restoredPtr->id = 202;
	if (originalData.id == 202)
		std::cout << "[PASS] Modifying through restored pointer modifies original data!" << std::endl;
	else
		std::cout << "[FAIL] Data memory is not shared!" << std::endl;

	std::cout << "\n========================================" << std::endl;
	std::cout << "  TEST 2: Heap Allocated Data Object    " << std::endl;
	std::cout << "========================================" << std::endl;
	Data* heapData = new Data;
	heapData->id = 777;
	heapData->name = "Heap Data";
	heapData->value = 123.456;

	uintptr_t rawHeap = Serializer::serialize(heapData);
	Data* restoredHeap = Serializer::deserialize(rawHeap);

	if (restoredHeap == heapData && restoredHeap->id == 777 && restoredHeap->name == "Heap Data")
		std::cout << "[PASS] Heap serialization roundtrip succeeded!" << std::endl;
	else
		std::cout << "[FAIL] Heap serialization failed!" << std::endl;

	delete heapData;

	std::cout << "\n========================================" << std::endl;
	std::cout << "  TEST 3: NULL Pointer Serialization    " << std::endl;
	std::cout << "========================================" << std::endl;
	uintptr_t rawNull = Serializer::serialize(NULL);
	Data* restoredNull = Serializer::deserialize(rawNull);

	if (restoredNull == NULL && rawNull == 0)
		std::cout << "[PASS] NULL pointer serialized to 0 and deserialized to NULL!" << std::endl;
	else
		std::cout << "[FAIL] NULL pointer serialization failed!" << std::endl;

	return 0;
}
