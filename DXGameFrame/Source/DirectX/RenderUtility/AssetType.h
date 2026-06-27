// AssetType.h
#pragma once
#include <string>

/// アセットの種類
enum class AssetType : uint32_t
{
	UNKNOWN,		
	TEXTURE,
	MODEL,
	SHADER
};

/**
 * @brief ファイルパスからアセットの種類を取得する
 * @param アセットのファイルパス
 * @return アセットの種類
 */
AssetType GetAssetType(const std::string& filePath);
