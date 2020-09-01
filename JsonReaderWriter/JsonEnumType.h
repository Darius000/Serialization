#pragma once

#include <ostream>

namespace JSON
{
	enum class Type : char
	{
		None, String, Number, Boolean, Null, Object, Array
	};
		
	inline std::ostream& operator<<(std::ostream& os, Type type)
	{
		switch (type)
		{
		case Type::String:		return os << "String";
		case Type::Number:		return os << "Number";
		case Type::Object:		return os << "Object";
		case Type::Null:		return os << "Null";
		case Type::Boolean:     return os << "Boolean";
		case Type::Array:		return os << "Array";
		}

		return os << "None";
	}
}