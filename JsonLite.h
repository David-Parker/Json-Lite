#pragma once
#include <string>
#include <vector>

/* JsonLite: Lightweight JSON serializer for C++. No complex dependencies. */
namespace JsonLite
{
	// Quick C++ 'reflection' base class, determine class type at runtime for pointer down casting.
	class JsonElement
	{
	public:
		enum Type
		{
			JsonObject,
			JsonArray,
			JsonString,
			JsonInt,
			JsonFloat,
			JsonBool
		};

		JsonElement(const std::string& name, Type type) : children(), name(name), type(type) 
		{
		}

		Type type;
		std::string name;
		std::vector<JsonElement*> children;
	};

	class JsonArray : public JsonElement
	{
	public:
		JsonArray(std::string name) : JsonElement(name, JsonElement::Type::JsonArray)
		{
		}
	};

	class JsonObject : public JsonElement
	{
	public:
		JsonObject(std::string name) : JsonElement(name, JsonElement::Type::JsonObject)
		{
		}
	};

	class JsonString : public JsonElement
	{
	public:
		std::string value;

		JsonString(std::string name, std::string value) : JsonElement(name, JsonElement::Type::JsonString), value(value)
		{
		}
	};

	class JsonInteger : public JsonElement
	{
	public:
		int value;

		JsonInteger(std::string name, int value) : JsonElement(name, JsonElement::Type::JsonInt), value(value)
		{
		}
	};

	class JsonFloat : public JsonElement
	{
	public:
		float value;

		JsonFloat(std::string name, float value) : JsonElement(name, JsonElement::Type::JsonFloat), value(value)
		{
		}
	};

	class JsonBoolean : public JsonElement
	{
	public:
		bool value;

		JsonBoolean(std::string name, bool value) : JsonElement(name, JsonElement::Type::JsonBool), value(value)
		{
		}
	};

	class JsonLiteSerializer
	{
	private:
		JsonElement* root;
		JsonElement* last;
		std::string ToString(JsonElement* elem, int depth);
		std::vector<JsonElement*> objectList;

	public:
		JsonLiteSerializer();
		~JsonLiteSerializer();

		std::string ToString();
		JsonElement* GetRoot();
		JsonElement* GetLast();
		JsonElement* AddArray(JsonElement* parent, std::string name);
		JsonElement* AddObject(JsonElement* parent, std::string name);
		JsonElement* AddString(JsonElement* parent, std::string name, std::string value);
		JsonElement* AddInteger(JsonElement* parent, std::string name, int value);
		JsonElement* AddFloat(JsonElement* parent, std::string name, float value);
		JsonElement* AddBoolean(JsonElement* parent, std::string name, bool value);
	};
}