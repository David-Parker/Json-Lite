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
		JsonArray(const std::string& name) : JsonElement(name, JsonElement::Type::JsonArray)
		{
		}
	};

	class JsonObject : public JsonElement
	{
	public:
		JsonObject(const std::string& name) : JsonElement(name, JsonElement::Type::JsonObject)
		{
		}
	};

	class JsonString : public JsonElement
	{
	public:
		std::string value;

		JsonString(const std::string& name, const std::string& value) : JsonElement(name, JsonElement::Type::JsonString), value(value)
		{
		}
	};

	class JsonInteger : public JsonElement
	{
	public:
		int value;

		JsonInteger(const std::string& name, int value) : JsonElement(name, JsonElement::Type::JsonInt), value(value)
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
		std::string SanitizeInput(const std::string& input);

	public:
		JsonLiteSerializer();
		~JsonLiteSerializer();

		std::string ToString();
		JsonElement* GetRoot();
		JsonElement* GetLast();
		JsonElement* AddArray(JsonElement* parent, const std::string& name);
		JsonElement* AddObject(JsonElement* parent, const std::string& name);
		JsonElement* AddString(JsonElement* parent, const std::string& name, const std::string& value);
		JsonElement* AddInteger(JsonElement* parent, const std::string& name, int value);
		JsonElement* AddFloat(JsonElement* parent, const std::string& name, float value);
		JsonElement* AddBoolean(JsonElement* parent, const std::string& name, bool value);
	};
}