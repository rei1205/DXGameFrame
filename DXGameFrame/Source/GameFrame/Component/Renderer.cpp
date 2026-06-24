// Renderer.cpp
#include "Renderer.h"
#include "../Core/Scene.h"

Renderer::Renderer()
{
	m_renderLayerID = RenderLayer::GetLayerID(RenderLayerName::DefaultLayer);
}

void Renderer::Awake()
{
	GetScene()->GetRenderSystem().RegisterRenderer(this);
}

void Renderer::OnDestroy()
{
	GetScene()->GetRenderSystem().UnregisterRenderer(this);
}

void Renderer::SetRenderLayer(const std::string& layerName)
{
	m_renderLayerID = RenderLayer::GetLayerID(layerName);
}
