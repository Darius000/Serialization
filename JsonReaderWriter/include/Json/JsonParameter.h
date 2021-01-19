#pragma once

#include "JsonTypes.h"
#include "JsonKey.h"

namespace JSON
{ 
	struct JsonParameter
	{
		JsonParameter() :m_Key(""), m_Value() {}
		JsonParameter(const char* key, JsonType* value)
			:m_Key(key), m_Value(value) {}

		JsonKey m_Key;
		JsonType* m_Value;

		friend std::ostream& operator<<(std::ostream& os, const JsonParameter& type);
	};

	inline std::ostream& operator<<(std::ostream& os, const JsonParameter& param)
	{
		os <<  param.m_Key << ": ";
		param.m_Value->Print(os);
		return os;
	}
}