#pragma once

#include "Reflection.h"

namespace  Reflection
{
	//int type
	struct TypeDescriptor_Int : TypeDescriptor
	{
		TypeDescriptor_Int()
			:TypeDescriptor("int", sizeof(int))
		{}

		void PrintInfo(const void* obj, int indentLevel = 0) const override
		{
			std::cout << "int{"<< *(const int*)obj << "}";
		}
	};

	template<>
	TypeDescriptor* GetPrimitiveDesciptor<int>()
	{
		static TypeDescriptor_Int typeDesc;
		return &typeDesc;
	};

	//string type
	struct TypeDescriptor_StdString : TypeDescriptor
	{
		TypeDescriptor_StdString()
			:TypeDescriptor("std::string", sizeof(std::string))
		{}

		void PrintInfo(const void* obj, int indentLevel = 0) const override
		{
			std::cout << "std::string{" << *(const std::string*)obj << "}";
		}
	};

	template<>
	TypeDescriptor* GetPrimitiveDesciptor<std::string>()
	{
		static TypeDescriptor_StdString typeDesc;
		return &typeDesc;
	};

	//float
	struct TypeDescriptor_Float : TypeDescriptor
	{
		TypeDescriptor_Float()
			:TypeDescriptor("float", sizeof(float))
		{}

		void PrintInfo(const void* obj, int indentLevel = 0) const override
		{
			std::cout << "float{" << *(const float*)obj << "}";
		}
	};

	template<>
	TypeDescriptor* GetPrimitiveDesciptor<float>()
	{
		static TypeDescriptor_Float typeDesc;
		return &typeDesc;
	};

	//bool
	struct TypeDescriptor_Bool : TypeDescriptor
	{
		TypeDescriptor_Bool()
			:TypeDescriptor("bool", sizeof(bool))
		{}

		void PrintInfo(const void* obj, int indentLevel = 0) const override
		{
			std::cout << "bool{" << *(const bool*)obj << "}";
		}
	};

	template<>
	TypeDescriptor* GetPrimitiveDesciptor<bool>()
	{
		static TypeDescriptor_Bool typeDesc;
		return &typeDesc;
	};

	//double
	struct TypeDescriptor_Double : TypeDescriptor
	{
		TypeDescriptor_Double()
			:TypeDescriptor("double", sizeof(double))
		{}

		void PrintInfo(const void* obj, int indentLevel = 0) const override
		{
			std::cout << "double{" << *(const double*)obj << "}";
		}
	};

	template<>
	TypeDescriptor* GetPrimitiveDesciptor<double>()
	{
		static TypeDescriptor_Double typeDesc;
		return &typeDesc;
	};


	struct TypeDescriptor_StdVector : TypeDescriptor
	{
		TypeDescriptor* m_ItemType;
		size_t (*GetSize)(const void*) = nullptr;
		const void* (*GetItem)(const void*, size_t) = nullptr;

		template<typename ItemType>
		TypeDescriptor_StdVector(ItemType*)
			:TypeDescriptor("std::vector<>", sizeof(std::vector<ItemType>)),
			m_ItemType(TypeResolver<ItemType>::Get())
		{

			GetSize = [](const void* vecPtr) ->size_t {
				const auto& vec = *(const std::vector<ItemType>*) vecPtr;
				return vec.size();
			};

			GetItem = [](const void* vecPtr, size_t index) -> const void* {
				const auto& vec = *(const std::vector<ItemType>*) vecPtr;
				return &vec[index];
			};
		
		};

		std::string GetFullName() const override
		{
			return std::string("std::vector<") + m_ItemType->GetFullName() + ">";
		}

		void PrintInfo(const void* obj, int indentLevel = 0) const override
		{
			size_t numItems = GetSize(obj);
			std::cout << GetFullName();
			if(numItems == 0)
				std::cout << "{}";
			else
			{
				std::cout << "{\n";
				for (size_t index = 0; index < numItems; index++)
				{
					std::cout << std::string(4 * (indentLevel + 1), ' ') << "[" << index << "]";
					m_ItemType->PrintInfo(GetItem(obj, index), indentLevel + 1);
					std::cout << "\n";
				}

				std::cout << std::string(4 * indentLevel, ' ') << "}";
			}
		}
	};

	template<typename T>
	class TypeResolver<std::vector<T>>
	{
	public:
	
		static TypeDescriptor* Get()
		{
			static TypeDescriptor_StdVector typeDesc((T*)nullptr);
			return &typeDesc;
		}
	};

	//-------------------------------------------------------------
	//Unique Ptr
	//-------------------------------------------------------------
	struct TypeDescriptor_StdUniquePtr : TypeDescriptor
	{
		TypeDescriptor* m_ItemType;
		const void* (*GetTarget)(const void*) = nullptr;

		template<typename ItemType>
		TypeDescriptor_StdUniquePtr(ItemType*)
			:TypeDescriptor("std::unique_ptr<>", sizeof(std::unique_ptr<ItemType>)),
			m_ItemType(TypeResolver<ItemType>::Get())
		{

			GetTarget = [](const void* uniquePtrPtr) -> const void* {
				const auto& uniquePtr = *(const std::unique_ptr<ItemType>*) uniquePtrPtr;
				return uniquePtr.get();
			};

		};

		std::string GetFullName() const override
		{
			return std::string("std::unique_ptr<") + m_ItemType->GetFullName() + ">";
		}

		void PrintInfo(const void* obj, int indentLevel = 0) const override
		{
			const void* targetObj = GetTarget(obj);
			std::cout << GetFullName() << "{";
			if (targetObj == nullptr)
				std::cout << "nullptr";
			else
			{
				std::cout << "\n";
				std::cout << std::string(4 * (indentLevel + 1), ' ');
				m_ItemType->PrintInfo(targetObj, indentLevel + 1);
				std::cout << "\n";
				std::cout << std::string(4 * indentLevel, ' ');
			}

			std::cout << "}";
		}
	};

	template<typename T>
	class TypeResolver<std::unique_ptr<T>>
	{
	public:

		static TypeDescriptor* Get()
		{
			static TypeDescriptor_StdUniquePtr typeDesc((T*)nullptr);
			return &typeDesc;
		}
	};
}