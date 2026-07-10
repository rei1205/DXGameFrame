// SerializeUtility.h
#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Color.h"
#include <objbase.h>
#include <nlohmann/json.hpp>

/// シリアライズ補助機能
namespace SerializeUtility
{
	/**
	 * @brief データをシリアライズする
	 * @param jsonData 書き込み先jsonデータへの参照
	 * @praam key キー文字列
	 * @pram value 書き込む値
	 */
	void SerializeValue(nlohmann::json& jsonData, const std::string& key, const bool& value);
	void SerializeValue(nlohmann::json& jsonData, const std::string& key, const int& value);
	void SerializeValue(nlohmann::json& jsonData, const std::string& key, const float& value);
	void SerializeValue(nlohmann::json& jsonData, const std::string& key, const std::string& value);
	void SerializeValue(nlohmann::json& jsonData, const std::string& key, const Vector2& value);
	void SerializeValue(nlohmann::json& jsonData, const std::string& key, const Vector3& value);
	void SerializeValue(nlohmann::json& jsonData, const std::string& key, const Quaternion& value);
	void SerializeValue(nlohmann::json& jsonData, const std::string& key, const Color& value);
	void SerializeValue(nlohmann::json& jsonData, const std::string& key, const GUID& value);

	/**
	 * @brief データをデシリアライズする
	 * @param jsonData 読み込み先jsonデータへの参照
	 * @praam key キー文字列
	 * @pram value 読み込んだ値の格納先
	 */
	void DeserializeValue(const nlohmann::json& jsonData, const std::string& key, bool& value);
	void DeserializeValue(const nlohmann::json& jsonData, const std::string& key, int& value);
	void DeserializeValue(const nlohmann::json& jsonData, const std::string& key, float& value);
	void DeserializeValue(const nlohmann::json& jsonData, const std::string& key, std::string& value);
	void DeserializeValue(const nlohmann::json& jsonData, const std::string& key, Vector2& value);
	void DeserializeValue(const nlohmann::json& jsonData, const std::string& key, Vector3& value);
	void DeserializeValue(const nlohmann::json& jsonData, const std::string& key, Quaternion& value);
	void DeserializeValue(const nlohmann::json& jsonData, const std::string& key, Color& value);
	void DeserializeValue(const nlohmann::json& jsonData, const std::string& key, GUID& value);
}