// RenderSystem.cpp
#include "RenderSystem.h"
#include "DefaultRenderPass.h"
#include "../Core/Scene.h"
#include "../Component/Renderer.h"
#include "../../DirectX/Manager/ShaderManager.h"
#include "../../DirectX/Manager/PipelineStateManager.h"
#include <unordered_map>
#include <algorithm>

void RenderSystem::Init(Scene* pScene)
{
	m_pScene = pScene;
	m_renderPasses.push_back(std::make_shared<DefaultRenderPass>());
}

void RenderSystem::Uninit()
{
	for (auto& renderPass : m_renderPasses)
	{
		renderPass->Uninit();
	}
	m_renderPasses.clear();
}

void RenderSystem::DrawAll()
{
	if (m_pScene == nullptr)
		return;

	// 描画関連コンポーネントを取得する
	ComponentManager& componentManager = m_pScene->GetComponentManager();
	std::vector<Renderer*> renderers = componentManager.GetRenderers();
	std::vector<Camera*> cameras = componentManager.GetCameras();
	std::vector<DirectionalLight*> directionalLights = componentManager.GetDirectionalLights();

	// 仮で通常描画のみ行う
	RenderContext renderContext;
	renderContext.pCamera = Camera::GetMain(m_pScene);
	if (!directionalLights.empty())
	{
		renderContext.pDirectionalLight = directionalLights.back();
	}
	else
	{
		renderContext.pDirectionalLight = nullptr;
	}

	// レンダーパスごとの描画を行う
	for (auto& renderPass : m_renderPasses)
	{
		// 描画リソースのキャッシュを削除
		ShaderManager::Refresh();
		PipelineStateManager::Refresh();

		renderPass->Render(renderers, renderContext);
	}
}
