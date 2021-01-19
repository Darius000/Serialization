#pragma once

#include "JsonTypes.h"
#include "JsonParameter.h"

#include <unordered_map>

namespace JSON
{
	struct JsonObject : public JsonType
	{
		JsonObject() = default;

		Type GetType() override { return Type::Object; }
		bool AddParameter(const JsonParameter& parameter)
		{
			if(m_Parameters.find((const char*)parameter.m_Key) == m_Parameters.end())
			{ 
				m_Parameters.emplace(std::pair<const char*, JsonParameter>((const char*)parameter.m_Key, parameter));
				return true;
			}
			
			return false;
		};

		std::ostream& Print(std::ostream& os) const override
		{
			size_t i = 0;

			os << "{ ";
			for ( const auto& param : m_Parameters)
			{
				if (i == m_Parameters.size() - 1)
				{
					os << " " << param.second;
				}
				else
				{
					os << " " << param.second << " , ";
				}
				i++;
			}

			os << " }";

			return os;
		}

		std::unordered_map<const char*, JsonParameter> m_Parameters;
	};
}