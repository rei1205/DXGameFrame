// TextureManager.cpp
#include "TextureManager.h"
#include "../Direct3D.h"

std::unordered_map<std::string, std::shared_ptr<Texture>> TextureManager::s_textures;

std::shared_ptr<Texture> TextureManager::LoadTexture(const std::string& filePath)
{
	// テクスチャ検索
	auto it = s_textures.find(filePath);
	if (it != s_textures.end())
	{
		// 既存のテクスチャを返す
		return it->second;
	}

	// 新規テクスチャ読み込み・追加
	auto newTex = std::make_shared<Texture>();
	if (FAILED(newTex->Load(filePath)))
	{
		return nullptr;
	}
	s_textures[filePath] = newTex;
	return newTex;
}

void TextureManager::SetTexture(Texture* pTexture, UINT slot)
{
	ID3D11ShaderResourceView* pSRV = pTexture->GetSRV();
	Direct3D::GetContext()->PSSetShaderResources(slot, 1, &pSRV);
}

void TextureManager::CollectGarbage()
{
	for (auto it = s_textures.begin(); it != s_textures.end();)
	{
		// 使用中チェック
		if (it->second.use_count() > 1)
		{
			++it;
			continue;
		}

		it = s_textures.erase(it);
	}
}

void TextureManager::Clear()
{
	s_textures.clear();
}
