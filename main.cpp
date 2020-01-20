#include <iostream>
#include "JsonLite.h"

using namespace JsonLite;

// Example usage
int main()
{
	JsonLiteSerializer serializer;

	JsonElement* parent = serializer.GetRoot();
	parent = serializer.AddArray(parent, "Results");

	for (int i = 0; i < 10; ++i)
	{
		serializer.AddInteger(parent, "", i);
	}

	parent = serializer.GetRoot();

	parent = serializer.AddObject(parent, "Statistics");
	serializer.AddFloat(parent, "Mean", 3.14f);
	serializer.AddFloat(parent, "StDv", 2.71f);
	serializer.AddString(parent, "Foo", "Bar");
	serializer.AddNull(parent, "null");

	std::string result = serializer.ToString(true);
	result = serializer.ToString(true);

	std::cout << result << std::endl;

	return 0;
}