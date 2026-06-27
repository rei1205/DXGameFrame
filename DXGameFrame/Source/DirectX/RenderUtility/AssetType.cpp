// AssetType.cpp
#include "AssetType.h"
#include <filesystem>

AssetType GetAssetType(const std::string& filePath)
{
    std::filesystem::path path = filePath;
    auto ext = path.extension();

    if (ext == ".png")return AssetType::TEXTURE;
    if (ext == ".jpg") return AssetType::TEXTURE;
    if (ext == ".fbx") return AssetType::MODEL;
    if (ext == ".cso") return AssetType::SHADER;

    return AssetType::UNKNOWN;
}
