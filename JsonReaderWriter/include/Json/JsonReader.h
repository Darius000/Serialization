#pragma once

#include "JsonObject.h"
#include <string>

namespace JSON
{
	using JsonFileArray = std::vector<std::string>;

	class JsonReader
	{
	public:
		JsonReader();
		JsonReader(const std::string& file, JsonObject& obj);
		~JsonReader();

		bool Open(const std::string& file);
		JsonObject Read();
		void Close();
		bool CheckForDeliminater(char delim);
		JsonFileArray ConvertToStringArray();
		void ParseObjectString(JsonFileArray::iterator& iterator, const JsonFileArray& filearray);
		void ParseArray(JsonFileArray::iterator& iterator, const JsonFileArray& filearray);
		bool IsDigit(const std::string& str);

	private:
		std::ifstream* is;
	};
}