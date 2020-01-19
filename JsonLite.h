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
		std::string buffer;
		std::vector<JsonElement*> objectList;

		void AddTabs(int depth);
		JsonElement* AddElement(JsonElement* parent, const std::string& name, JsonElement::Type type);
		template<class T, typename V>
		JsonElement* AddValue(JsonElement* parent, const std::string& name, const V& value, JsonElement::Type type);
		void SanitizeInput(const std::string& input);
		void ToString(JsonElement* elem, int depth, bool prettyPrint);

	public:
		JsonLiteSerializer();
		~JsonLiteSerializer();

		JsonElement* AddArray(JsonElement* parent, const std::string& name);
		JsonElement* AddObject(JsonElement* parent, const std::string& name);
		void AddBoolean(JsonElement* parent, const std::string& name, bool value);
		void AddFloat(JsonElement* parent, const std::string& name, float value);
		void AddInteger(JsonElement* parent, const std::string& name, int value);
		void AddNull(JsonElement* parent, const std::string& name);
		void AddString(JsonElement* parent, const std::string& name, const std::string& value);
		JsonElement* GetRoot();
		std::string ToString(bool prettyPrint = false);
	};
}