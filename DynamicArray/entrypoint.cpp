#include "DynamicArray.h"

#include <iostream>

class Vector3
{
public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	int* memoryblock = nullptr;

	Vector3()
	{	
		memoryblock = new int[5];
	}

	Vector3(float scalar) : x(scalar), y(scalar), z(scalar)
	{
		memoryblock = new int[5];
	}
	Vector3(float x, float y, float z):x(x), y(y), z(z)
	{
		memoryblock = new int[5];
	}

	Vector3(const Vector3& other) = delete;

	Vector3(Vector3&& other) noexcept
		:x(other.x), y(other.y), z(other.z)
	{
		memoryblock = other.memoryblock;
		other.memoryblock = nullptr;
		std::cout << "Move\n";
	}

	~Vector3()
	{
		std::cout << "Destroy\n";
		delete[] memoryblock;
	}

	Vector3& operator=(const Vector3& other) = delete;

	Vector3& operator=(Vector3&& other) noexcept
	{
		std::cout << "Move\n";
		memoryblock = other.memoryblock;
		other.memoryblock = nullptr;
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
};

template<typename T>
void PrintElements(const DynamicArray<T>& dynamicArray)
{
	for (size_t i = 0; i < dynamicArray.Size(); i++)
	{
		std::cout << dynamicArray[i] << std::endl;
	}
}

template<>
void PrintElements(const DynamicArray<Vector3>& dynamicArray)
{
	for (size_t i = 0; i < dynamicArray.Size(); i++)
	{
		std::cout << "{ " << dynamicArray[i].x << " , " << 
			dynamicArray[i].y << " , " << 
			dynamicArray[i].z << " }" << std::endl;
	}
}

int main()
{
	{
		DynamicArray<Vector3> myarray;
		myarray.EmplaceBack(1.0f);
		myarray.EmplaceBack(.5f, 0.0f, 1.0f);
		myarray.EmplaceBack(4.0f, 1.0f, 2.0f);
		myarray.EmplaceBack();
		PrintElements(myarray);
		myarray.PopBack();
		myarray.PopBack();
		myarray.PopBack();
		PrintElements(myarray);

		DynamicArray<int> intArray;
		intArray.EmplaceBack(5);
		intArray.EmplaceBack(5);
		intArray.EmplaceBack(5);
		intArray.EmplaceBack(5);
		intArray.PushBack(5);
		intArray.EmplaceBack(5);
		intArray.EmplaceBack(5);
		PrintElements(intArray);
		myarray.PopBack();
		myarray.PopBack();
		PrintElements(intArray);
		myarray.Clear();
		PrintElements(intArray);

		std::cout << myarray.Size() << std::endl;

		
	}

	std::cin.get();
}