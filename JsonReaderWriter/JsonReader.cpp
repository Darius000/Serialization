#include "JsonReader.h"

namespace JSON
{

	JsonReader::JsonReader()
		:is(nullptr)
	{

	}

	JsonReader::JsonReader(const std::string& file, JsonObject& obj)
	{
		if (Open(file))
		{
			obj = Read();
			Close();
		}
	}

	JsonReader::~JsonReader()
	{
		delete is;
	}

	bool JsonReader::Open(const std::string& file)
	{
		is = new std::ifstream();
		is->open(file.c_str(), std::ios::in);
		return is->good();
	}

	JsonObject JsonReader::Read()
	{
		JsonFileArray strarray = ConvertToStringArray();

		bool isObject = false;
		bool isArray = false;
		bool isKey = true;
	
		std::string currentKey = "";

		JsonObject parentObject = JsonObject();

		for (auto& str : strarray)
		{
			JsonObject childObject;

			if (str == "{")
			{
				std::cout << str << " begin object \n";
			}
			else if (str == "}")
			{
				std::cout << str << " end object \n";
			}
			else if (isKey && str == ":")
			{
				isKey = false;

				std::cout << "Value = ";
			}
			else if (!isKey && str == "," && !isArray)
			{
				isKey = true;
			}
			else if (str == "{" && str != strarray[0])
			{
				isObject = true;

				std::cout << str << " begin object \n";

				childObject = JsonObject();

				isKey = false;
			}
			else if (str == "}" && str != *(strarray.end() - 1))
			{
				isObject = false;

				std::cout << str << " end object \n";

				JsonParameter param(currentKey.c_str(), &childObject);
				parentObject.AddParameter(param);
			}
			else if (IsDigit(str))
			{
				std::cout << str << "\n";
			}
			else if (str == "null")
			{
				std::cout << str << "\n";
			}
			else if (str == "[")
			{
				isArray = true;

				std::cout << str << " begin array \n";
			}
			else if(str == "]")
			{
				isArray = false;

				std::cout << str << " end array\n";
			}
			else if (str == "true" || str == "false")
			{
				std::cout << str << "\n";
			}
			else if (str == ":" || str == ",")
			{

			}
			else
			{
				if (isKey)
				{
					currentKey = str;

					std::cout << "Key = ";
				}
				
				std::cout << str << "\n";
			}
		}

		return parentObject;
	}

	void JsonReader::Close()
	{
		is->close();
	}

	bool JsonReader::CheckForDeliminater(char delim)
	{
		switch (delim)
		{
		case '[':
			return true;
		case ']':
			return true;
		case '{':
			return true;
		case '}':
			return true;
		case ':':
			return true;
		case ',':
			return true;
		default:
			return false;
		}

		return false;
	}

	JsonFileArray JsonReader::ConvertToStringArray()
	{
		char character;

		std::string capture;
		std::string conversion;

		JsonFileArray capture_list;

		std::string line;
		while (*is >> character)
		{
			if (CheckForDeliminater(character))
			{
				conversion = character;
				if (!capture.empty())
				{
					capture_list.push_back(capture);
					capture_list.push_back(conversion);
					capture.clear();
				}
				else
				{
					capture_list.push_back(conversion);
				}
			}
			else
			{
				capture += character;
			}
		}

		return capture_list;
	}

	bool JsonReader::IsDigit(const std::string& str)
	{
		char c = str[0];

		size_t i = 0;

		while (i != str.size())
		{
			if (c == '.' || c == '-')
			{
				
			}
			else if (!isdigit(c))
			{
				return false;
			}

			i++;
			c = str[i];
		}

		return true;
	}
}
