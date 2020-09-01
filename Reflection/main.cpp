// Reflection.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "src/Struct.h"
#include "src/Primitives.h"

struct Node
{
    std::string key;
    int value;
    //std::vector<Node> children;
    bool open;
    float pie;
    double dou;
    std::vector<int> v;
    std::unique_ptr<Node> children;

    REFLECT()
};

class Text
{
public:
    ~Text(){ delete text; }

    std::string line;

    Text* text;

    REFLECT()
};

int main()
{
    std::cout << "Hello World!\n";

    Node node = {"apple" , 3, true, 3.2145f, 2.222456, {2, 3, 32, 33}};

    Text text;
    text.line = "line";
    text.text = new Text();
    text.text->line = "This is a sentence";

    Reflection::TypeDescriptor* typeDescr = Reflection::TypeResolver<Node>::Get();
    typeDescr->PrintInfo(&node);

	Reflection::TypeDescriptor* typeDescr1 = Reflection::TypeResolver<Text>::Get();
	typeDescr1->PrintInfo(&text);

    std::cin.get();

    return 0;
}

REFLECT_STRUCT_BEGIN(Node)
REFLECT_STRUCT_MEMBER(key)
REFLECT_STRUCT_MEMBER(value)
REFLECT_STRUCT_MEMBER(open)
REFLECT_STRUCT_MEMBER(pie)
REFLECT_STRUCT_MEMBER(dou)
REFLECT_STRUCT_MEMBER(v)
REFLECT_STRUCT_MEMBER(children)
REFLECT_STRUCT_END()

REFLECT_STRUCT_BEGIN(Text)
REFLECT_STRUCT_MEMBER(line)
//REFLECT_STRUCT_MEMBER(text)
REFLECT_STRUCT_END()