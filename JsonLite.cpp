#include <exception>
#include <iomanip>
#include "JsonLite.h"

using namespace JsonLite;

JsonLiteSerializer::JsonLiteSerializer() : objectList(), buffer()
{
	this->root = new JsonElement("", JsonElement::Type::JsonObject);
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
	ToString(root, 0, prettyPrint);

	std::string ret = this->buffer.str();
	this->buffer.str("");
	this->buffer.clear();

	return ret;
}

void JsonLiteSerializer::AddTabs(int depth)
{
	for (int i = 0; i < depth; ++i)
	{
		this->buffer << "  ";
	}
}

void JsonLiteSerializer::ToString(JsonElement* elem, int depth, bool prettyPrint)
{
	// Tabs
	if (prettyPrint)
		AddTabs(depth);

	// Add element name
	if (elem->name != "")
	{
		this->buffer << "\"";
		SanitizeInput(elem->name);
		this->buffer << "\": ";
	}

	// Add open grouping chars if neccessary
	switch (elem->type)
	{
	case JsonElement::Type::JsonArray:
		this->buffer << '[';
		if (prettyPrint) this->buffer << std::endl;
		break;
	case JsonElement::Type::JsonObject:
		this->buffer << '{';
		if (prettyPrint) this->buffer << std::endl;
		break;
	case JsonElement::Type::JsonString:
		this->buffer << "\"";
		SanitizeInput(((JsonValue<std::string>*)elem)->value);
		this->buffer << "\"";
		break;
	case JsonElement::Type::JsonInt:
		this->buffer << ((JsonValue<int>*)elem)->value;
		break;
	case JsonElement::Type::JsonFloat:
		this->buffer << ((JsonValue<float>*)elem)->value;
		break;
	case JsonElement::Type::JsonBool:
		this->buffer << ((JsonValue<bool>*)elem)->value;
		break;
	case JsonElement::Type::JsonNull:
		this->buffer << "null";
		break;
	default:
		throw std::runtime_error("Type not implemented.");
	}

	// recurse on all nested elements
	for (JsonElement* child : elem->children)
	{
		ToString(child, depth + 1, prettyPrint);

		if (child != elem->children.back())
		{
			this->buffer << ",";
		}

		if (prettyPrint)
			this->buffer << std::endl;
	}

	// Add closing grouping chars if neccessary
	switch (elem->type)
	{
	case JsonElement::Type::JsonArray:
		if (prettyPrint) AddTabs(depth);
		this->buffer << ']';
		break;
	case JsonElement::Type::JsonObject:
		if (prettyPrint) AddTabs(depth);
		this->buffer << '}';
		break;
	}
}

JsonElement* JsonLiteSerializer::GetRoot()
{
	return this->root;
}

JsonElement* JsonLiteSerializer::AddElement(JsonElement * parent, const std::string & name, JsonElement::Type type)
{
	if (parent == nullptr)
	{
		throw std::runtime_error("Invalid parent JSON element.");
	}

	JsonElement* newElem = new JsonElement(name, type);

	parent->children.push_back(newElem);
	this->objectList.push_back(newElem);

	return newElem;
}

template<class T, typename V>
JsonElement* JsonLiteSerializer::AddValue(JsonElement * parent, const std::string & name, const V& value, JsonElement::Type type)
{
	if (parent == nullptr)
	{
		throw std::runtime_error("Invalid parent JSON element.");
	}

	if (parent->type == JsonElement::Type::JsonObject)
	{
		if (name == "")
		{
			throw std::runtime_error("String value must contain a name.");
		}
	}
	else if (parent->type == JsonElement::Type::JsonArray)
	{
		if (name != "")
		{
			throw std::runtime_error("String value must not contain a name.");
		}
	}
	else
	{
		throw std::runtime_error("Cannot add a string value to this element.");
	}

	JsonElement* newElem = new JsonValue<T>(name, value, type);

	parent->children.push_back(newElem);
	this->objectList.push_back(newElem);

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

void JsonLiteSerializer::AddNull(JsonElement* parent, const std::string& name)
{
	this->AddElement(parent, name, JsonElement::Type::JsonNull);
}

void JsonLiteSerializer::AddString(JsonElement* parent, const std::string& name, const std::string& value)
{
	this->AddValue<std::string>(parent, name, value, JsonElement::Type::JsonString);
}

void JsonLiteSerializer::AddInteger(JsonElement* parent, const std::string& name, int value)
{
	this->AddValue<int>(parent, name, value, JsonElement::Type::JsonInt);
}

void JsonLiteSerializer::AddFloat(JsonElement* parent, const std::string& name, float value)
{
	this->AddValue<float>(parent, name, value, JsonElement::Type::JsonFloat);
}

void JsonLiteSerializer::AddBoolean(JsonElement* parent, const std::string& name, bool value)
{
	this->AddValue<bool>(parent, name, value, JsonElement::Type::JsonBool);
}

// Escape all json control characters
void JsonLiteSerializer::SanitizeInput(const std::string& input)
{
	for (auto c = input.cbegin(); c != input.cend(); ++c)
	{
		char ch = *c;

		// Encode special control characters in hex
		if (ch == '"' || ch == '\\' || ('\x00' <= ch && ch <= '\x1f'))
		{
			this->buffer << "\\u" << std::hex << std::setw(4) << std::setfill('0') << (int)ch;
		}
		else {
			this->buffer << ch;
		}
	}
}