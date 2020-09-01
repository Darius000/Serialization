#include "JsonWriter.h"

namespace JSON
{
	JsonWriter::JsonWriter()
		:os(nullptr)
	{
		
	}

	JsonWriter::JsonWriter(std::string&& file, const JsonObject& obj)
	{
		if(Open(file.c_str()))
		{ 
			Write(obj);
			Close();
		}
	}

	JsonWriter::~JsonWriter()
	{
		delete os;
	}

	bool JsonWriter::Open(std::string&& file)
	{
		file.append(".json");
		os = new std::ofstream();
		os->open(file.c_str(), std::ios::out);
		return os->good();
	}

	void JsonWriter::Write(const JsonObject& obj)
	{
		if(!os) return;

		std::ofstream& stream = *os;

		stream << obj;
	}

	void JsonWriter::Close()
	{
		os->close();
		
	}
}