#include <sstream>
#include <iostream>
#include <iomanip>
#include <exception>
#include "JsonLite.h"

using namespace JsonLite;

JsonLiteSerializer::JsonLiteSerializer() : objectList()
{
	this->root = new JsonObject("");
	this->last = root;
	objectList.push_back(this->root);
}

JsonLiteSerializer::~JsonLiteSerializer()
{
	for (JsonElement* elem : objectList)
	{
		delete elem;
	}
}

std::string JsonLiteSerializer::ToString()
{
	return ToString(root, 0);
}

void AddTabs(std::stringstream& stream, int depth)
{
	for (int i = 0; i < depth; ++i)
	{
		stream << "  ";
	}
}

std::string JsonLiteSerializer::ToString(JsonElement* elem, int depth)
{
	std::stringstream ret;
	JsonElement* pElem = elem;
	char openChar = 0;
	char closeChar = 0;

	// Tabs
	AddTabs(ret, depth);

	// Add element name
	if (elem->name != "")
	{
		ret << "\"" << elem->name << "\": ";
	}

	// Add open grouping chars if neccessary
	switch (pElem->type)
	{
	case JsonElement::Type::JsonArray:
		ret << '[' << std::endl;
		break;
	case JsonElement::Type::JsonObject:
		ret << '{' << std::endl;
		break;
	case JsonElement::Type::JsonString:
		ret << "\"" << ((JsonString*)pElem)->value << "\"";
		break;
	case JsonElement::Type::JsonInt:
		ret << ((JsonInteger*)pElem)->value;
		break;
	case JsonElement::Type::JsonFloat:
		ret << ((JsonFloat*)pElem)->value;
		break;
	case JsonElement::Type::JsonBool:
		ret << ((JsonBoolean*)pElem)->value;
		break;
	}

	// recurse on all nested elements
	for (JsonElement* elem : pElem->children)
	{
		ret << ToString(elem, depth + 1);

		if (elem != pElem->children.back())
		{
			ret << ",";
		}

		ret << std::endl;
	}

	// Add closing grouping chars if neccessary
	switch (pElem->type)
	{
	case JsonElement::Type::JsonArray:
		AddTabs(ret, depth);
		ret << ']';
		break;
	case JsonElement::Type::JsonObject:
		AddTabs(ret, depth);
		ret << '}';
		break;
	}

	return ret.str();
}

JsonElement* JsonLiteSerializer::GetRoot()
{
	return this->root;
}

JsonElement* JsonLiteSerializer::GetLast()
{
	return this->last;
}

JsonElement* JsonLiteSerializer::AddArray(JsonElement* parent, const std::string& name)
{
	if (parent == nullptr)
	{
		throw std::runtime_error("Invalid parent JSON element.");
	}

	JsonElement* newElem = new JsonArray(this->SanitizeInput(name));

	parent->children.push_back(newElem);
	this->objectList.push_back(newElem);
	this->last = newElem;

	return newElem;
}

JsonElement* JsonLiteSerializer::AddObject(JsonElement* parent, const std::string& name)
{
	if (parent == nullptr)
	{
		throw std::runtime_error("Invalid parent JSON element.");
	}

	JsonElement* newElem = new JsonObject(this->SanitizeInput(name));

	parent->children.push_back(newElem);
	this->objectList.push_back(newElem);
	this->last = newElem;

	return newElem;
}

JsonElement* JsonLiteSerializer::AddString(JsonElement* parent, const std::string& name, const std::string& value)
{
	if (parent == nullptr)
	{
		throw std::runtime_error("Invalid parent JSON element.");
	}

	JsonElement* newElem = new JsonString(this->SanitizeInput(name), this->SanitizeInput(value));

	parent->children.push_back(newElem);
	this->objectList.push_back(newElem);
	this->last = newElem;

	return newElem;
}

JsonElement* JsonLiteSerializer::AddInteger(JsonElement* parent, const std::string& name, int value)
{
	if (parent == nullptr)
	{
		throw std::runtime_error("Invalid parent JSON element.");
	}

	JsonElement* newElem = new JsonInteger(this->SanitizeInput(name), value);

	parent->children.push_back(newElem);
	this->objectList.push_back(newElem);
	this->last = newElem;

	return newElem;
}

JsonElement* JsonLiteSerializer::AddFloat(JsonElement* parent, const std::string& name, float value)
{
	if (parent == nullptr)
	{
		throw std::runtime_error("Invalid parent JSON element.");
	}

	JsonElement* newElem = new JsonFloat(this->SanitizeInput(name), value);

	parent->children.push_back(newElem);
	this->objectList.push_back(newElem);
	this->last = newElem;

	return newElem;
}

JsonElement* JsonLiteSerializer::AddBoolean(JsonElement* parent, const std::string& name, bool value)
{
	if (parent == nullptr)
	{
		throw std::runtime_error("Invalid parent JSON element.");
	}

	JsonElement* newElem = new JsonBoolean(this->SanitizeInput(name), value);

	parent->children.push_back(newElem);
	this->objectList.push_back(newElem);
	this->last = newElem;

	return newElem;
}

std::string JsonLiteSerializer::SanitizeInput(const std::string& input)
{
	std::ostringstream o;
	for (auto c = input.cbegin(); c != input.cend(); c++) {
		if (*c == '"' || *c == '\\' || ('\x00' <= *c && *c <= '\x1f')) {
			o << "\\u"
				<< std::hex << std::setw(4) << std::setfill('0') << (int)* c;
		}
		else {
			o << *c;
		}
	}
	return o.str();
}

// Example usage
int main()
{
	JsonLiteSerializer serializer;

	JsonElement* parent = serializer.GetRoot();
	parent = serializer.AddArray(parent, "Results");

	std::vector<int> numbers;

	for (int i = 0 ; i < 1000; ++i)
	{
		numbers.push_back(100);
	}

	for (int val : numbers)
	{
		serializer.AddInteger(parent, "", val);
	}

	parent = serializer.GetRoot();

	parent = serializer.AddObject(parent, "Statistics");
	serializer.AddFloat(parent, "Mean", 12.23);
	serializer.AddFloat(parent, "StDv", 0.6);

	std::cout << serializer.ToString();

    return 0;
}

