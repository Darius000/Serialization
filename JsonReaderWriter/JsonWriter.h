#pragma once

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include "JsonObject.h"

namespace JSON
{
	class JsonWriter
	{
	public:
		JsonWriter();
		JsonWriter(std::string&& file, const JsonObject& obj);
		~JsonWriter();

		bool Open(std::string&& file);
		void Write(const JsonObject& obj);
		void Close();

	private:
		std::ofstream* os;
	};
}