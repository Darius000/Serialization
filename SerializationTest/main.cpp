
#include <iostream>
#include <Serilializer.h>
#include <Serialize.h>
#include <Archive.h>

class Test //: public Serialization::ISerializable
{
public:

	/*void Serialize(Serialization::Archive& ar, unsigned int version) const override
	{	
		ar & m_var1;
		ar & m_var2;
		ar& sentence;
	}

	void DeSerialize(Serialization::Archive& ar, unsigned int version) override
	{	
		ar & m_var1;
		ar & m_var2;
		ar& sentence;
	}*/

	friend void Serialize(Serialization::Archive& ar, const Test& obj, unsigned int version);

	friend void DeSerialize(Serialization::Archive& ar, Test& obj, unsigned int version);


	int m_var1 = 23;
	bool m_var2 = false;
	std::string sentence = "Default Sentence";
};

void Serialize(Serialization::Archive& ar, const Test& obj, unsigned int version)
{
	ar& obj.m_var1;
	ar& obj.m_var2;
	ar& obj.sentence;
}

void DeSerialize(Serialization::Archive& ar, Test& obj, unsigned int version)
{
	ar& obj.m_var1;
	ar& obj.m_var2;
	ar& obj.sentence;
}

class Test2 : public Test 
{
public:

	/*void Serialize(Serialization::Archive& ar, unsigned int version) const override
	{
		SERIALIZEBASECLASS(Test, ar, version);
		SERIALIZEMEMEBER(ar, m_var3);
	}

	void DeSerialize(Serialization::Archive& ar, unsigned int version) override
	{
		DESERIALIZEBASECLASS(Test, ar, version);
		SERIALIZEMEMEBER(ar, m_var3);
	}*/

	friend void Serialize(Serialization::Archive& ar, const Test2& obj, unsigned int version);

	friend void DeSerialize(Serialization::Archive& ar, Test2& obj, unsigned int version);

	std::string classname = "Test2";
	float m_var3 = 3.14f;
};

inline void Serialize(Serialization::Archive& ar, const Test2& obj, unsigned int version)
{
	ar & obj.classname;
	SERIALIZEBASECLASS(Test, ar, obj, version);
	SERIALIZEMEMEBER(ar, obj.m_var3);
}

inline void DeSerialize(Serialization::Archive& ar, Test2& obj, unsigned int version)
{
	ar& obj.classname;
	DESERIALIZEBASECLASS(Test, ar, obj, version);
	SERIALIZEMEMEBER(ar, obj.m_var3);
}

class Test3 : public Test2
{
	friend void Serialize(Serialization::Archive& ar, const Test3& obj, unsigned int version);

	friend void DeSerialize(Serialization::Archive& ar, Test3& obj, unsigned int version);

	float m_var4 = 5.9f;
	bool m_IsOpen = false;
	std::vector<int> m_List = {0 , 1, 2, 45, -67, 200};
	std::vector<bool> m_List2 = { true, false, true};
	std::vector<std::string> m_List3 = { "me", "myself", " and I" };
	std::vector<std::string> m_EmptyList = {};
};

void Serialize(Serialization::Archive& ar, const Test3& obj, unsigned int version)
{
	SERIALIZEBASECLASS(Test2, ar, obj, version)
	SERIALIZEMEMEBER(ar, obj.m_var4)
	SERIALIZEMEMEBER(ar, obj.m_IsOpen)

	ar& obj.m_List;
	ar& obj.m_List2;
	ar& obj.m_List3;
	ar& obj.m_EmptyList;
}

void DeSerialize(Serialization::Archive& ar, Test3& obj, unsigned int version) 
{
	DESERIALIZEBASECLASS(Test2, ar, obj, version)
	SERIALIZEMEMEBER(ar, obj.m_var4)
	SERIALIZEMEMEBER(ar, obj.m_IsOpen)

	ar& obj.m_List;
	ar& obj.m_List2;
	ar& obj.m_List3;
	ar& obj.m_EmptyList;
}

class MTest 
{
public:
	MTest()
	{
		//test = new Test2();
		//test->m_var1 = 44;
	}

	~MTest()
	{
		delete test;
	}

	void Serialize(Serialization::Archive& ar, unsigned int version) const 
	{
		ar & classname;
		ar & m_var1;
		ar & m_var2;
		ar & sentence;
		SERIALIZEOBJECT(ar, test, version);
	}

	void DeSerialize(Serialization::Archive& ar, unsigned int version) 
	{
		ar & classname;
		ar & m_var1;
		ar & m_var2;
		ar & sentence;
		DESERIALIZEOBJECT(ar, test, version)
	}

	std::string classname = "MTest";
	int m_var1 = 256;
	bool m_var2 = false;
	std::string sentence = "Default Sentence mtest";
	Test2* test = nullptr;
};

int main()
{
	Test test;
	Test2 test2;
	Test3 test3;
	MTest* mtest = new MTest();
	mtest->test = new Test2();

	Serialization::Archive archive("Test3");
	archive.DeSerialize(test3);

	Serialization::Archive archive4("mTest");
	archive4.DeSerialize(*mtest);

	std::cout << test3.sentence << "\n";
	std::cout << test2.m_var3 << "\n";
	std::cout << test3.m_var3 << "\n";

	//Serialization::Serilializer::Load();

	

	std::cout << mtest->test->m_var2 << "\n";
	std::cout << mtest->test->m_var3 << "\n";

	mtest->m_var1  = 992266;
	mtest->test->m_var1 = 56;
	mtest->test->m_var2 = true;
	mtest->test->m_var3 = 4.54333f;


	archive4.Serialize(*mtest);
	archive.Serialize(test3);

	//Serialization::Serilializer::Save();

	delete mtest;

	std::cin.get();
	return 0;
}

