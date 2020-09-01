#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cstddef>

namespace Reflection
{

	struct TypeDescriptor
	{
		const char* m_Name;
		size_t m_Size;

		TypeDescriptor(const char* name, size_t size)
			:m_Size(size), m_Name(name){}

		virtual ~TypeDescriptor() = default;

		virtual std::string GetFullName() const {return m_Name; };
		virtual void PrintInfo(const void* obj, int indentLevel = 0) const = 0;
	};

	template<typename T>
	TypeDescriptor* GetPrimitiveDesciptor();

	struct DefaultSolver
	{
		template<typename T>
		static char func(decltype(&T::Reflection));

		template<typename T> 
		static int func(...);

		template<typename T>
		struct IsReflected
		{
			enum { value = (sizeof(func<T>(nullptr)) == sizeof(char)) };
		};

		template<typename T, typename std::enable_if<IsReflected<T>::value, int>::type = 0>
		static TypeDescriptor* Get()
		{
			return &T::Reflection;
		}

		template<typename T, typename std::enable_if<!IsReflected<T>::value, int>::type = 0>
		static TypeDescriptor* Get()
		{
			return GetPrimitiveDesciptor<T>();
		}
	};

	template<typename T>
	struct TypeResolver
	{
		static TypeDescriptor* Get()
		{
			return DefaultSolver::Get<T>();
		}
	};
}