#pragma once
#include <string>
#include <vector>

/* JsonLite: Lightweight JSON serializer for C++. No complex dependencies. */
namespace JsonLite
{
	// Quick C++ 'reflection' base class, determine class type at runtime for pointer down casting.
	class JsonElement
	{
	friend class JsonLiteSerializer;

	private:
		std::vector<JsonElement*> children;
		std::string name;
		JsonElement* parent;

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
		JsonElement(const std::string& name, Type type, JsonElement* parent) : children(), name(name), type(type), parent(parent) {}
	};

	template <typename T>
	class JsonValue : public JsonElement
	{
	public:
		T value;
		JsonValue(const std::string& name, const T& value, JsonElement::Type type, JsonElement* parent) : JsonElement(name, type, parent), value(value) {}
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
		void Clear();
		JsonElement* GetParent(JsonElement* elem);
		JsonElement* GetRoot();
		std::string ToString(bool prettyPrint = false);
	};
}