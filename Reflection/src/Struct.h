#pragma once

#include <vector>
#include "Reflection.h"

namespace Reflection
{
	struct TypeDescriptor_Struct : TypeDescriptor
	{
		struct Member
		{
			const char* m_Name;
			size_t m_Offset;
			TypeDescriptor* m_Type;
		};

		std::vector<Member> m_Members;

		TypeDescriptor_Struct(void(*init)(TypeDescriptor_Struct*)) : TypeDescriptor{ nullptr , 0 }
		{
			init(this);
		}

		TypeDescriptor_Struct(const char* name, const std::initializer_list<Member>& init) : 
			TypeDescriptor{ nullptr , 0}, m_Members{init}
		{}

		void PrintInfo(const void* obj, int indentLevel) const override
		{
			std::cout << m_Name << " {" << "\n";
			for (const auto& member : m_Members)
			{
				std::cout << std::string(4 * (indentLevel + 1), ' ') << member.m_Name << "=";
				member.m_Type->PrintInfo((char*)obj + member.m_Offset, indentLevel + 1);
				std::cout << "\n";
			}
			std::cout << std::string(4 * indentLevel, ' ') << "}";
		}
	};

	#define REFLECT()\
		friend struct Reflection::DefaultSolver;\
		static Reflection::TypeDescriptor_Struct Reflection;\
		static void InitReflection(Reflection::TypeDescriptor_Struct*);

	#define REFLECT_STRUCT_BEGIN(Type)\
		Reflection::TypeDescriptor_Struct Type::Reflection{Type::InitReflection};\
		void Type::InitReflection(Reflection::TypeDescriptor_Struct* typeDesc){\
			using T = Type;\
			typeDesc->m_Name = #Type;\
			typeDesc->m_Size = sizeof(T);\
			typeDesc->m_Members = {

	#define REFLECT_STRUCT_MEMBER(Name)\
			{#Name, offsetof(T, Name), Reflection::TypeResolver<decltype(T::Name)>::Get()},

	#define REFLECT_STRUCT_END()\
		};\
	}

}