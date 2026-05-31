// RenderPass.cpp
#include "RenderPass.h"
#include "../../DirectX/RenderUtility/RenderLayer.h"

RenderPass::RenderPass() :
	m_targetRenderLayerID(RenderLayer::LayerID_None)
{
}

void RenderPass::SetTargetRenderLayer(const std::string& layerName)
{
	m_targetRenderLayerID = RenderLayer::GetLayerID(layerName);
}