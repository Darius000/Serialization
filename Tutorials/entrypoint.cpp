#pragma once

#include <iostream>

#include "StaticArray.h"

int main()
{
	StaticArray<int, 30> myarray;
	myarray[5] = 40;
	myarray.Fill(256);

	for (size_t i = 0; i < myarray.GetSize(); i += 3)
	{
		myarray[i] = 200;
	}

	for (size_t i = 0; i < myarray.GetSize(); i++)
	{
		std::cout << myarray[i] << std::endl;
	}

	for (int n : myarray)
	{
		n = 2;
		std::cout << n << std::endl;
	}

	std::cin.get();
}