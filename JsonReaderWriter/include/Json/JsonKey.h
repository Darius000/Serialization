#pragma once

#include <ostream>

#define JSONKEY(str) #str
#define XMLKEY(str) #str

namespace JSON
{
	struct JsonKey
	{
		JsonKey() :m_Key(nullptr) {};
		JsonKey(const char* name) : m_Key(name) {};
		const char* GetKey() { return m_Key; }

		const char* m_Key;

		operator const char* () const { return m_Key; }

		friend std::ostream& operator<<(std::ostream& os, const JsonKey& key);
	};

	inline std::ostream& operator<<(std::ostream& os, const JsonKey& key)
	{
		return os << key.m_Key;
	}
}