#include <iostream>
#include "JsonLite.h"

using namespace JsonLite;

// Example usage
#pragma optimize( "", off )
int main()
{
	JsonLiteSerializer serializer;

	JsonElement* parent = serializer.GetRoot();
	parent = serializer.AddArray(parent, "Results");

	std::vector<int> numbers;

	for (int i = 0; i < 10; ++i)
	{
		serializer.AddInteger(parent, "", i);
	}

	parent = serializer.GetRoot();

	parent = serializer.AddObject(parent, "Statistics");
	serializer.AddFloat(parent, "Mean", 3.14f);
	serializer.AddFloat(parent, "StDv", 2.71f);
	serializer.AddString(parent, "Foo", "Bar");
	parent = serializer.AddObject(parent, "Obj");
	serializer.AddNull(parent, "null");

	std::cout << serializer.ToString() << std::endl;

	return 0;
}
#pragma optimize( "", on )