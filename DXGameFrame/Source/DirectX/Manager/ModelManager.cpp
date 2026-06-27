// ModelManager.cpp
#include "ModelManager.h"
#include "../../System/Debug.h"

std::unordered_map<std::string, std::shared_ptr<Model>> ModelManager::s_models;

std::shared_ptr<Model> ModelManager::Load(const std::string& filePath)
{
	// すでに読み込まれているかチェック
	auto it = s_models.find(filePath);
	if (it != s_models.end())
	{
		// 読み込まれていれば再利用
		return it->second;
	}

	// モデルデータ作成
	auto model = std::make_shared<Model>();
	model->Load(filePath);
	s_models[filePath] = model;

	return model;
}

void ModelManager::CollectGarbage()
{
	for (auto it = s_models.begin(); it != s_models.end();)
	{
		// 使用中チェック
		if (it->second.use_count() > 1)
		{
			++it;
			continue;
		}

		it = s_models.erase(it);
	}

	Debug::ConsoleLog("TextureManager : CollectGarbage");
	Debug::ConsoleLog("- Current = " + s_models.size());
}

void ModelManager::Clear()
{
	s_models.clear();
}
