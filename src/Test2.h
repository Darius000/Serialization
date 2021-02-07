#pragma once

//Example class to use Serialization

#include <Serialization/Serialize.h>
//
using namespace Serialization;
//
//class TestSerialable: public ISerializable
//{
//public:
//
//
//	float results = 10.5f;
//
//	float average = 0.0f;
//
//	int age = 2;
//
//	unsigned int time = -1;
//
//	bool isTest = true;
//
//	std::string name = "TestSerializable";
//
//	std::string GetName() override
//	{
//		return name;
//	}
//
//
//	void Serialize(Archive& ar, unsigned int version) const override
//	{
//		ar & results;
//		ar & average;
//		ar & isTest;
//		ar & age;
//		ar & time;
//	}
//
//
//	void DeSerialize(Archive& ar, unsigned int version) override
//	{
//		ar & results;
//		ar & average;
//		ar & isTest;
//		ar & age;
//		ar & time;
//	}
//};
//
class Test2 
{
public:
	
	Test2()
	{
		
	}

	float results = 10.5f;

	float average = 0.0f;

	int age = 2;

	unsigned int time = -1;

	bool isTest = true;

	std::vector<float> floats;

	friend void Serialize(Archive& ar, const Test2& obj, unsigned int version);
	friend void DeSerialize(Archive& ar, Test2& obj, unsigned int version);

};

inline void Serialize(Archive& ar, const Test2& obj, unsigned int version)
{
	ar & obj.results;
	ar & obj.average;
	ar& obj.age;
	ar& obj.time;
	ar & obj.isTest;	
	ar & obj.floats;
};


inline void DeSerialize(Archive& ar, Test2& obj, unsigned int version)
{
	ar & obj.results;
	ar & obj.average;
	ar& obj.age;
	ar& obj.time;
	ar& obj.isTest;
	ar & obj.floats; 
};


///Example code to save and load file
//Serialization::Archive archive = Serialization::Archive("Test2SavedNonBinary", Serialization::EArchiveModes::None);

/*Test2 test;
archive.DeSerialize(test);
archive.Serialize(test);
*/