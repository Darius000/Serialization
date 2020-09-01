#pragma once

#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>

#include "JsonEnumType.h"

#define JSONSTR(str) #str

namespace JSON
{
	
	struct JsonType
	{
		JsonType() = default;
		virtual Type GetType() { return Type::None; };
		virtual std::ostream& Print(std::ostream& os) const { return os; };

		friend std::ostream& operator<<(std::ostream& os, const JsonType& type);
	};

	template<typename U>
	struct JsonNumber : public JsonType
	{
		JsonNumber(U value) : m_Value(value){};
		Type GetType() override { return Type::Number; }
		U GetValue() const { return m_Value; }
		std::ostream& Print(std::ostream& os) const override { return os <<  GetValue(); }
		
		U m_Value;
	};

	struct JsonBoolean : public JsonType
	{
		JsonBoolean(bool v) : m_Value(v){}
		Type GetType() override { return Type::Boolean; }
		const char* GetStringValue() const { return m_Value ? "true": "false" ; }
		bool GetValue() const { return m_Value; }
		std::ostream& Print(std::ostream& os) const override { return os <<  GetStringValue(); }
		bool m_Value;
	};

	struct JsonNull : public JsonType
	{
		Type GetType() override { return Type::Null; }
		const char* GetStringValue() const { return "null"; }
		void* GetValue() const { return nullptr; }
		std::ostream& Print(std::ostream& os) const override { return os << GetStringValue(); }
	};

	struct JsonString : public JsonType
	{
		JsonString(const char* s): m_String(s){};
		Type GetType() override { return Type::String; }
		const char* GetValue() const { return m_String; }
		std::ostream& Print(std::ostream& os) const override { return os << GetValue(); }
		const char* m_String;
	};

	template<typename _Elem>
	struct JsonArray : public JsonType
	{
		JsonArray(std::initializer_list<_Elem> a) : m_Array(a) {};
		Type GetType() override { return Type::Array; }
		std::vector<_Elem> GetValue() const { return m_Array; }
		std::vector<_Elem> m_Array;

		std::ostream& Print(std::ostream& os) const override
		{
			os << "[ ";
			for (size_t i = 0; i < m_Array.size(); i++)
			{
				if (i == m_Array.size() - 1)
				{
					os << " " << m_Array[i];
				}
				else
				{
					os << " " << m_Array[i] << " , ";
				}
			}

			os << " ]";

			return os;
		}
	};

	inline std::ostream& operator<<(std::ostream& os, const JsonType& type)
	{
		return type.Print(os);
	}
}