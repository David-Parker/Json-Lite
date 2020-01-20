#include "CppUnitTest.h"
#include "JsonLite.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace JsonLite;

namespace JsonLiteTests
{		
	TEST_CLASS(JsonLiteTests)
	{
	public:
		
		TEST_METHOD(JsonLite_JsonLiteSerializer_Empty)
		{
			std::string expected = "{}";
			JsonLiteSerializer serializer;

			std::string json = serializer.ToString();
			Assert::AreEqual(expected, json);
		}

		TEST_METHOD(JsonLite_JsonLiteSerializer_Object)
		{
			std::string expected = "{{}}";
			JsonLiteSerializer serializer;

			JsonElement* parent = serializer.GetRoot();
			serializer.AddObject(parent, "");

			std::string json = serializer.ToString();
			Assert::AreEqual(expected, json);
		}

		TEST_METHOD(JsonLite_JsonLiteSerializer_MultiObject)
		{
			std::string expected = "{{},{}}";
			JsonLiteSerializer serializer;

			JsonElement* parent = serializer.GetRoot();
			serializer.AddObject(parent, "");
			serializer.AddObject(parent, "");

			std::string json = serializer.ToString();
			Assert::AreEqual(expected, json);
		}

		TEST_METHOD(JsonLite_JsonLiteSerializer_NamedObject)
		{
			std::string expected = "{\"foo\": {}}";
			JsonLiteSerializer serializer;

			JsonElement* parent = serializer.GetRoot();
			serializer.AddObject(parent, "foo");

			std::string json = serializer.ToString();
			Assert::AreEqual(expected, json);
		}

		TEST_METHOD(JsonLite_JsonLiteSerializer_Array)
		{
			std::string expected = "{[]}";
			JsonLiteSerializer serializer;

			JsonElement* parent = serializer.GetRoot();
			serializer.AddArray(parent, "");

			std::string json = serializer.ToString();
			Assert::AreEqual(expected, json);
		}

		TEST_METHOD(JsonLite_JsonLiteSerializer_MultiArray)
		{
			std::string expected = "{[],[]}";
			JsonLiteSerializer serializer;

			JsonElement* parent = serializer.GetRoot();
			serializer.AddArray(parent, "");
			serializer.AddArray(parent, "");

			std::string json = serializer.ToString();
			Assert::AreEqual(expected, json);
		}

		TEST_METHOD(JsonLite_JsonLiteSerializer_NamedArray)
		{
			std::string expected = "{\"foo\": []}";
			JsonLiteSerializer serializer;

			JsonElement* parent = serializer.GetRoot();
			serializer.AddArray(parent, "foo");

			std::string json = serializer.ToString();
			Assert::AreEqual(expected, json);
		}

		TEST_METHOD(JsonLite_JsonLiteSerializer_IntArray)
		{
			std::string expected = "{[1]}";
			JsonLiteSerializer serializer;

			JsonElement* parent = serializer.GetRoot();
			parent = serializer.AddArray(parent, "");
			serializer.AddInteger(parent, "", 1);

			std::string json = serializer.ToString();
			Assert::AreEqual(expected, json);
		}

		TEST_METHOD(JsonLite_JsonLiteSerializer_IntArray_MultiValues)
		{
			std::string expected = "{[1,2,3]}";
			JsonLiteSerializer serializer;

			JsonElement* parent = serializer.GetRoot();
			parent = serializer.AddArray(parent, "");
			serializer.AddInteger(parent, "", 1);
			serializer.AddInteger(parent, "", 2);
			serializer.AddInteger(parent, "", 3);

			std::string json = serializer.ToString();
			Assert::AreEqual(expected, json);
		}

		TEST_METHOD(JsonLite_JsonLiteSerializer_FloatArray)
		{
			std::string expected = "{[1.000000]}";
			JsonLiteSerializer serializer;

			JsonElement* parent = serializer.GetRoot();
			parent = serializer.AddArray(parent, "");
			serializer.AddFloat(parent, "", 1.0f);

			std::string json = serializer.ToString();
			Assert::AreEqual(expected, json);
		}

		TEST_METHOD(JsonLite_JsonLiteSerializer_FloatArray_MultiValues)
		{
			std::string expected = "{[1.000000,2.000000,3.000000]}";
			JsonLiteSerializer serializer;

			JsonElement* parent = serializer.GetRoot();
			parent = serializer.AddArray(parent, "");
			serializer.AddFloat(parent, "", 1.0f);
			serializer.AddFloat(parent, "", 2.0f);
			serializer.AddFloat(parent, "", 3.0f);

			std::string json = serializer.ToString();
			Assert::AreEqual(expected, json);
		}

		TEST_METHOD(JsonLite_JsonLiteSerializer_String)
		{
			std::string expected = "{\"foo\": \"bar\"}";
			JsonLiteSerializer serializer;

			JsonElement* parent = serializer.GetRoot();
			serializer.AddString(parent, "foo", "bar");

			std::string json = serializer.ToString();
			Assert::AreEqual(expected, json);
		}

		TEST_METHOD(JsonLite_JsonLiteSerializer_String_EscapedValue)
		{
			std::string expected = "{\"foo\": \"\\u0022\"}";
			JsonLiteSerializer serializer;

			JsonElement* parent = serializer.GetRoot();
			serializer.AddString(parent, "foo", "\"");

			std::string json = serializer.ToString();
			Assert::AreEqual(expected, json);
		}

		TEST_METHOD(JsonLite_JsonLiteSerializer_String_EscapedName)
		{
			std::string expected = "{\"\\u0022\": \"bar\"}";
			JsonLiteSerializer serializer;

			JsonElement* parent = serializer.GetRoot();
			serializer.AddString(parent, "\"", "bar");

			std::string json = serializer.ToString();
			Assert::AreEqual(expected, json);
		}

		TEST_METHOD(JsonLite_JsonLiteSerializer_Null)
		{
			std::string expected = "{\"foo\": null}";
			JsonLiteSerializer serializer;

			JsonElement* parent = serializer.GetRoot();
			serializer.AddNull(parent, "foo");

			std::string json = serializer.ToString();
			Assert::AreEqual(expected, json);
		}

		TEST_METHOD(JsonLite_JsonLiteSerializer_Boolean_True)
		{
			std::string expected = "{\"foo\": true}";
			JsonLiteSerializer serializer;

			JsonElement* parent = serializer.GetRoot();
			serializer.AddBoolean(parent, "foo", true);

			std::string json = serializer.ToString();
			Assert::AreEqual(expected, json);
		}

		TEST_METHOD(JsonLite_JsonLiteSerializer_Boolean_False)
		{
			std::string expected = "{\"foo\": false}";
			JsonLiteSerializer serializer;

			JsonElement* parent = serializer.GetRoot();
			serializer.AddBoolean(parent, "foo", false);

			std::string json = serializer.ToString();
			Assert::AreEqual(expected, json);
		}

		TEST_METHOD(JsonLite_JsonLiteSerializer_ToString_Twice)
		{
			std::string expected = "{\"foo\": \"bar\"}";
			JsonLiteSerializer serializer;

			JsonElement* parent = serializer.GetRoot();
			serializer.AddString(parent, "foo", "bar");

			std::string json = serializer.ToString();
			Assert::AreEqual(expected, json);

			json = serializer.ToString();
			Assert::AreEqual(expected, json);
		}

		TEST_METHOD(JsonLite_JsonLiteSerializer_ToString_Clear)
		{
			std::string expected = "{\"foo\": \"bar\"}";
			JsonLiteSerializer serializer;

			JsonElement* parent = serializer.GetRoot();
			serializer.AddString(parent, "foo", "bar");

			std::string json = serializer.ToString();
			Assert::AreEqual(expected, json);

			serializer.Clear();
			json = serializer.ToString();
			Assert::AreEqual(std::string("{}"), json);
		}

		TEST_METHOD(JsonLite_JsonLiteSerializer_Array_InvalidValue)
		{
			JsonLiteSerializer serializer;

			JsonElement* parent = serializer.GetRoot();
			parent = serializer.AddArray(parent, "");

			try
			{
				serializer.AddInteger(parent, "foo", 1);
			}
			catch (std::exception& ex)
			{
				return;
			}

			Assert::Fail();
		}

		TEST_METHOD(JsonLite_JsonLiteSerializer_Object_InvalidValue)
		{
			JsonLiteSerializer serializer;

			JsonElement* parent = serializer.GetRoot();
			parent = serializer.AddObject(parent, "");

			try
			{
				serializer.AddInteger(parent, "", 1);
			}
			catch (std::exception& ex)
			{
				return;
			}

			Assert::Fail();
		}

		TEST_METHOD(JsonLite_JsonLiteSerializer_Complex)
		{
			std::string expected = "{{},\"Numbers\": [0,1,2,3,4,5,6,7,8,9],\"Stuff\": {\"Int\": 1,\"Float\": 1.000000,\"Bool\": true,\"Null\": null,\"String\": \"foo\",\"Arr\": []}}";
			JsonLiteSerializer serializer;

			JsonElement* parent = serializer.GetRoot();
			serializer.AddObject(parent, "");
			parent = serializer.AddArray(parent, "Numbers");

			for (int i = 0; i < 10; ++i)
			{
				serializer.AddInteger(parent, "", i);
			}

			parent = serializer.GetParent(parent);

			parent = serializer.AddObject(parent, "Stuff");
			serializer.AddInteger(parent, "Int", 1);
			serializer.AddFloat(parent, "Float", 1.0f);
			serializer.AddBoolean(parent, "Bool", true);
			serializer.AddNull(parent, "Null");
			serializer.AddString(parent, "String", "foo");
			serializer.AddArray(parent, "Arr");

			std::string json = serializer.ToString();
			Assert::AreEqual(expected, json);
		}

		TEST_METHOD(JsonLite_JsonLiteSerializer_StressTest)
		{
			JsonLiteSerializer serializer;

			JsonElement* parent = serializer.GetRoot();

			parent = serializer.AddArray(parent, "Stuff");

			for (int i = 0; i < 100000; ++i)
			{
				serializer.AddObject(parent, "Test");
			}

			for (int i = 0; i < 100000; ++i)
			{
				serializer.AddArray(parent, "Test");
			}

			for (int i = 0; i < 100000; ++i)
			{
				serializer.AddInteger(parent, "", i);
			}

			for (int i = 0; i < 100000; ++i)
			{
				serializer.AddFloat(parent, "", i);
			}

			for (int i = 0; i < 100000; ++i)
			{
				serializer.AddBoolean(parent, "", true);
			}

			for (int i = 0; i < 100000; ++i)
			{
				serializer.AddNull(parent, "");
			}

			parent = serializer.GetRoot();

			std::string result = serializer.ToString();
		}
	};
}