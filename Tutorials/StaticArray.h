#pragma once
//#include "Iterator.h"
#include <Iterator>

template<typename T, size_t Size>
struct StaticArray
{
	StaticArray() = default;

	void Fill(const T& value)
	{
		for (uint64_t i = 0; i < Size; i++)
		{
			data[i] = value;
		}
	}

	constexpr size_t GetSize() const { return Size; };

	T* Data() { return data; }
	const T* Data() const { return data; }

	//operators
	T& operator[](uint64_t index) {return data[index]; }
	const T& operator[](uint64_t index) const { return data[index]; }

private:
	T data[Size];
};