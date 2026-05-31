// RenderLayer.cpp
#include "RenderLayer.h"

std::unordered_map<std::string, int> RenderLayer::s_renderLayerMap;
IDManager RenderLayer::s_idManager;

void RenderLayer::AddLayer(const std::string& layerName)
{
	auto it = s_renderLayerMap.find(layerName);
	if (it == s_renderLayerMap.end())
	{
		// ƒŒƒCƒ„[‚ª‘¶Ý‚µ‚È‚¢ê‡’Ç‰Á
		s_renderLayerMap[layerName] = s_idManager.GenerateID();
	}
}

int RenderLayer::GetLayerID(const std::string& layerName)
{
	auto it = s_renderLayerMap.find(layerName);
	if (it == s_renderLayerMap.end())
		return LayerID_None;

	return it->second;
}

std::string RenderLayer::GetLayerName(int layerID)
{
	for (auto& pair : s_renderLayerMap)
	{
		if (pair.second == layerID)
		{
			return pair.first;
		}
	}
	return "Unknown RenderLayer";
}
