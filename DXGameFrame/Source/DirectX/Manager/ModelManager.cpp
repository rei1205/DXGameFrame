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
	if (!model->Load(filePath))
	{
		return nullptr;
	}
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

	Debug::ConsoleLog("Garbage Collection : ModelManager");
	Debug::ConsoleLog("- Current = " + s_models.size());
}

void ModelManager::Clear()
{
	s_models.clear();

	Debug::ConsoleLog("Clear : ModelManager");
}

std::string ModelManager::GetFilePathFromModel(Model* pModel)
{
	for (const auto& pair : s_models)
	{
		if (pair.second.get() == pModel)
		{
			return pair.first;
		}
	}
	return "";
}
