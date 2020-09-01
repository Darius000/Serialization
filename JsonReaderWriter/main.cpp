

#include "JsonObject.h"
#include "JsonWriter.h"
#include "JsonReader.h"

int main()
{
	JSON::JsonNumber<int> intValue(999999999);
	JSON::JsonParameter parameter0(JSONKEY("Int_Key"), &intValue);
	//parameter0.Print();

	JSON::JsonBoolean boolValue(false);
	JSON::JsonParameter parameter1(JSONKEY("Bool_Key"), &boolValue);
	//parameter1.Print();

	JSON::JsonNull nullValue;
	JSON::JsonParameter parameter2(JSONKEY("Null_Key"), &nullValue);
	//parameter2.Print();

	JSON::JsonNumber<float> floatValue(22.0f/7.0f);
	JSON::JsonParameter parameter3(JSONKEY("Float_Key"), &floatValue);
	//parameter3.Print();

	JSON::JsonNumber<double> doubleValue(22.0/7.0);
	JSON::JsonParameter parameter4(JSONKEY("Double_Key"), &doubleValue);
	//parameter4.Print();

	JSON::JsonString stringValue(JSONSTR("Rachael"));
	JSON::JsonParameter parameter5(JSONKEY("String_Key"), &stringValue);
	//parameter5.Print();

	JSON::JsonNumber<unsigned int> uintValue(999999);
	JSON::JsonParameter parameter6(JSONKEY("UnInt_Key"), &uintValue);
	//parameter6.Print();

	JSON::JsonArray<const char*> sarrayValue({ JSONSTR("Mike"), JSONSTR("John")});
	JSON::JsonParameter parameter7(JSONKEY("StringArray_Key"), &sarrayValue);
	//parameter7.Print();

	JSON::JsonArray<int> intarrayValue({ 235, 543, 54433,  0, -35 });
	JSON::JsonParameter parameter8(JSONKEY("IntArray_Key"), &intarrayValue);
	//parameter8.Print();

	JSON::JsonObject childobjValue;

	JSON::JsonNumber<int> age(35);
	JSON::JsonParameter parameterAge(JSONKEY("Age"), &age);

	JSON::JsonString name(JSONSTR("Sarah"));
	JSON::JsonParameter parameterName(JSONKEY("Name"), &name);

	childobjValue.AddParameter(parameterName);
	childobjValue.AddParameter(parameterAge);
	JSON::JsonParameter parameter9(JSONKEY("Person"), &childobjValue);

	JSON::JsonObject objValue;
	objValue.AddParameter(parameter0);
	objValue.AddParameter(parameter1);
	objValue.AddParameter(parameter2);
	objValue.AddParameter(parameter3);
	objValue.AddParameter(parameter4);
	objValue.AddParameter(parameter5);
	objValue.AddParameter(parameter6);
	objValue.AddParameter(parameter7);
	objValue.AddParameter(parameter8);
	objValue.AddParameter(parameter9);
	//std::cout << objValue;

	JSON::JsonWriter writer;
	writer.Open("Example 1 Json");
	writer.Write(childobjValue);
	writer.Close();

	JSON::JsonWriter writer2("Example 2 Json", objValue);

	JSON::JsonObject obj;
	JSON::JsonReader reader("Example 2 Json.json", obj);

	std::cin.get();
	return 0;
}