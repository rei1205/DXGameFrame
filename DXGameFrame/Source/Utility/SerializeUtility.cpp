// SerializeUtility.cpp
#include "SerializeUtility.h"

namespace SerializeUtility
{
	void SerializeValue(nlohmann::json& jsonData, const std::string& key, const bool& value)
	{
		jsonData[key] = value;
	}

	void SerializeValue(nlohmann::json& jsonData, const std::string& key, const int& value)
	{
		jsonData[key] = value;
	}

	void SerializeValue(nlohmann::json& jsonData, const std::string& key, const float& value)
	{
		jsonData[key] = value;
	}

	void SerializeValue(nlohmann::json& jsonData, const std::string& key, const std::string& value)
	{
		jsonData[key] = value;
	}

	void SerializeValue(nlohmann::json& jsonData, const std::string& key, const Vector2& value)
	{
		jsonData[key] = { value.x, value.y };
	}

	void SerializeValue(nlohmann::json& jsonData, const std::string& key, const Vector3& value)
	{
		jsonData[key] = { value.x, value.y, value.z };
	}

	void SerializeValue(nlohmann::json& jsonData, const std::string& key, const Quaternion& value)
	{
		jsonData[key] = { value.x, value.y, value.z, value.w };
	}

	void SerializeValue(nlohmann::json& jsonData, const std::string& key, const Color& value)
	{
		jsonData[key] = { value.r, value.g, value.b, value.a };
	}

	void SerializeValue(nlohmann::json& jsonData, const std::string& key, const GUID& value)
	{
		// ワイド文字列に変換
		wchar_t buffer[39];
		int length = StringFromGUID2(value, buffer, _countof(buffer));
		std::wstring ws(buffer);

		// 通常の文字列に変換
		std::string guidStr;
		guidStr.reserve(ws.size());
		std::transform(ws.begin(), ws.end(),
			std::back_inserter(guidStr),
			[](wchar_t c)
			{
				return static_cast<char>(c);
			});

		jsonData[key] = guidStr;
	}

	void DeserializeValue(const nlohmann::json& jsonData, const std::string& key, bool& value)
	{
		if (!jsonData.contains(key))
			return;

		value = jsonData[key];
	}

	void DeserializeValue(const nlohmann::json& jsonData, const std::string& key, int& value)
	{
		if (!jsonData.contains(key))
			return;

		value = jsonData[key];
	}

	void DeserializeValue(const nlohmann::json& jsonData, const std::string& key, float& value)
	{
		if (!jsonData.contains(key))
			return;

		value = jsonData[key];
	}

	void DeserializeValue(const nlohmann::json& jsonData, const std::string& key, std::string& value)
	{
		if (!jsonData.contains(key))
			return;

		value = jsonData[key];
	}

	void DeserializeValue(const nlohmann::json& jsonData, const std::string& key, Vector2& value)
	{
		if (!jsonData.contains(key))
			return;

		auto element = jsonData[key];
		value = Vector2(element[0], element[1]);
	}

	void DeserializeValue(const nlohmann::json& jsonData, const std::string& key, Vector3& value)
	{
		if (!jsonData.contains(key))
			return;

		auto element = jsonData[key];
		value = Vector3(element[0], element[1], element[2]);
	}

	void DeserializeValue(const nlohmann::json& jsonData, const std::string& key, Quaternion& value)
	{
		if (!jsonData.contains(key))
			return;

		auto element = jsonData[key];
		value = Quaternion(element[0], element[1], element[2], element[3]);
	}

	void DeserializeValue(const nlohmann::json& jsonData, const std::string& key, Color& value)
	{
		if (!jsonData.contains(key))
			return;

		auto element = jsonData[key];
		value = Color(element[0], element[1], element[2], element[3]);
	}

	void DeserializeValue(const nlohmann::json& jsonData, const std::string& key, GUID& value)
	{
		if (!jsonData.contains(key))
			return;

		std::string guidStr = jsonData[key];

		// ワイド文字列に変換
		std::wstring wGuidStr;
		wGuidStr.reserve(guidStr.size());
		std::transform(guidStr.begin(), guidStr.end(),
			std::back_inserter(wGuidStr),
			[](char c)
			{
				return static_cast<wchar_t>(static_cast<unsigned char>(c));
			});

		// GUIDに変換
		HRESULT hr = CLSIDFromString(wGuidStr.c_str(), &value);
	}
}
