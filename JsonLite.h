#pragma once
#include <iostream>
#include <sstream>
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
			JsonBool,
			JsonNull
		};

		Type type;
		std::string name;
		std::vector<JsonElement*> children;

		JsonElement(const std::string& name, Type type) : children(), name(name), type(type) {}
	};

	template <typename T>
	class JsonValue : public JsonElement
	{
	public:
		T value;
		JsonValue(const std::string& name, const T& value, JsonElement::Type type) : JsonElement(name, type), value(value) {}
	};

	class JsonLiteSerializer
	{
	private:
		JsonElement* root;
		std::ostringstream buffer;
		std::vector<JsonElement*> objectList;

		void ToString(JsonElement* elem, int depth, bool prettyPrint);
		void AddTabs(int depth);
		void SanitizeInput(const std::string& input);
		JsonElement* AddElement(JsonElement* parent, const std::string& name, JsonElement::Type type);
		template<class T, typename V>
		JsonElement* AddValue(JsonElement* parent, const std::string& name, const V& value, JsonElement::Type type);

	public:
		JsonLiteSerializer();
		~JsonLiteSerializer();

		std::string ToString(bool prettyPrint = false);
		JsonElement* GetRoot();
		JsonElement* AddArray(JsonElement* parent, const std::string& name);
		JsonElement* AddObject(JsonElement* parent, const std::string& name);
		void AddString(JsonElement* parent, const std::string& name, const std::string& value);
		void AddInteger(JsonElement* parent, const std::string& name, int value);
		void AddFloat(JsonElement* parent, const std::string& name, float value);
		void AddBoolean(JsonElement* parent, const std::string& name, bool value);
		void AddNull(JsonElement* parent, const std::string& name);
	};
}