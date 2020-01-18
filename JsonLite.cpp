#include <sstream>
#include <iostream>
#include <iomanip>
#include <exception>
#include "JsonLite.h"

using namespace JsonLite;

JsonLiteSerializer::JsonLiteSerializer() : objectList()
{
	this->root = new JsonElement("", JsonElement::Type::JsonObject);
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

std::string JsonLiteSerializer::ToString(bool prettyPrint)
{
	return ToString(root, 0, prettyPrint);
}

void AddTabs(std::stringstream& stream, int depth)
{
	for (int i = 0; i < depth; ++i)
	{
		stream << "  ";
	}
}

std::string JsonLiteSerializer::ToString(JsonElement* elem, int depth, bool prettyPrint)
{
	std::stringstream ret;
	JsonElement* pElem = elem;
	char openChar = 0;
	char closeChar = 0;

	// Tabs
	if (prettyPrint)
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
		ret << '[';
		if (prettyPrint) ret << std::endl;
		break;
	case JsonElement::Type::JsonObject:
		ret << '{';
		if (prettyPrint) ret << std::endl;
		break;
	case JsonElement::Type::JsonString:
		ret << "\"" << ((JsonValue<std::string>*)pElem)->value << "\"";
		break;
	case JsonElement::Type::JsonInt:
		ret << ((JsonValue<int>*)pElem)->value;
		break;
	case JsonElement::Type::JsonFloat:
		ret << ((JsonValue<float>*)pElem)->value;
		break;
	case JsonElement::Type::JsonBool:
		ret << ((JsonValue<bool>*)pElem)->value;
		break;
	case JsonElement::Type::JsonNull:
		ret << "null";
		break;
	default:
		throw std::runtime_error("Type not implemented.");
	}

	// recurse on all nested elements
	for (JsonElement* elem : pElem->children)
	{
		ret << ToString(elem, depth + 1, prettyPrint);

		if (elem != pElem->children.back())
		{
			ret << ",";
		}

		if (prettyPrint)
			ret << std::endl;
	}

	// Add closing grouping chars if neccessary
	switch (pElem->type)
	{
	case JsonElement::Type::JsonArray:
		if (prettyPrint) AddTabs(ret, depth);
		ret << ']';
		break;
	case JsonElement::Type::JsonObject:
		if (prettyPrint) AddTabs(ret, depth);
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

JsonElement* JsonLiteSerializer::AddElement(JsonElement * parent, const std::string & name, JsonElement::Type type)
{
	if (parent == nullptr)
	{
		throw std::runtime_error("Invalid parent JSON element.");
	}

	JsonElement* newElem = new JsonElement(this->SanitizeInput(name), type);

	parent->children.push_back(newElem);
	this->objectList.push_back(newElem);
	this->last = newElem;

	return newElem;
}

template<class T, typename V>
JsonElement* JsonLiteSerializer::AddValue(JsonElement * parent, const std::string & name, const V& value, JsonElement::Type type)
{
	if (parent == nullptr)
	{
		throw std::runtime_error("Invalid parent JSON element.");
	}

	JsonElement* newElem = new JsonValue<T>(this->SanitizeInput(name), value, type);

	parent->children.push_back(newElem);
	this->objectList.push_back(newElem);
	this->last = newElem;

	return newElem;
}

JsonElement* JsonLiteSerializer::AddArray(JsonElement* parent, const std::string& name)
{
	return this->AddElement(parent, name, JsonElement::Type::JsonArray);
}

JsonElement* JsonLiteSerializer::AddObject(JsonElement* parent, const std::string& name)
{
	return this->AddElement(parent, name, JsonElement::Type::JsonObject);
}

JsonElement* JsonLiteSerializer::AddNull(JsonElement* parent, const std::string& name)
{
	return this->AddElement(parent, name, JsonElement::Type::JsonNull);
}

JsonElement* JsonLiteSerializer::AddString(JsonElement* parent, const std::string& name, const std::string& value)
{
	return this->AddValue<std::string>(parent, name, this->SanitizeInput(value), JsonElement::Type::JsonString);
}

JsonElement* JsonLiteSerializer::AddInteger(JsonElement* parent, const std::string& name, int value)
{
	return this->AddValue<int>(parent, name, value, JsonElement::Type::JsonInt);
}

JsonElement* JsonLiteSerializer::AddFloat(JsonElement* parent, const std::string& name, float value)
{
	return this->AddValue<float>(parent, name, value, JsonElement::Type::JsonFloat);
}

JsonElement* JsonLiteSerializer::AddBoolean(JsonElement* parent, const std::string& name, bool value)
{
	return this->AddValue<bool>(parent, name, value, JsonElement::Type::JsonBool);
}

// Escape all json control characters
std::string JsonLiteSerializer::SanitizeInput(const std::string& input)
{
	std::ostringstream output;

	for (auto c = input.cbegin(); c != input.cend(); ++c)
	{
		// Encode special control characters in hex
		if (*c == '"' || *c == '\\' || ('\x00' <= *c && *c <= '\x1f'))
		{
			output << "\\u" << std::hex << std::setw(4) << std::setfill('0') << (int)* c;
		}
		else {
			output << *c;
		}
	}
	return output.str();
}