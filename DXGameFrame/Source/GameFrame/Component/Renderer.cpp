// Renderer.cpp
#include "Renderer.h"
#include "../Scene.h"

void Renderer::Awake()
{
	GetScene()->GetRenderSystem().RegisterRenderer(this);
}

void Renderer::OnDestroy()
{
	GetScene()->GetRenderSystem().UnregisterRenderer(this);
}
