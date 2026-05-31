#include "RenderSystem.h"
#include "Component/Renderer.h"
#include "../DirectX/RenderUtility/RenderLayer.h"
#include <unordered_map>

void RenderSystem::Uninit()
{
	for (auto& renderPass : m_renderPasses)
	{
		renderPass->Uninit();
	}
	m_renderPasses.clear();
	m_pRenderers.clear();
	m_pCameras.clear();
}

void RenderSystem::DrawAll()
{
	// 描画オブジェクト配列を作成
	std::unordered_map<int, std::vector<RenderObject>> renderObjectsMap;
	for (Renderer* renderer : m_pRenderers)
	{
		if (!renderer->IsActiveHierarchy() &&
			!renderer->IsStarted())
			continue;

		// マテリアルごとに描画オブジェクトを作成
		std::vector<Material>& materials = renderer->GetMaterials();
		UINT materialCount = (UINT)materials.size();
		for (UINT i = 0; i < materialCount; ++i)
		{
			RenderObject renderObject;
			renderObject.pRenderer = renderer;
			renderObject.materialIndex = i;

			int renderLayerID = materials[i].GetRenderLayerID();
			if (renderLayerID == RenderLayer::LayerID_None)
				continue;

			// 描画オブジェクト登録
			auto& vec = renderObjectsMap[renderLayerID];
			vec.push_back(renderObject);
		}
	}

	// カメラごとの描画を行う
	for (Camera* camera : m_pCameras)
	{
		RenderContext renderContext;
		renderContext.pCamera = camera;

		// レンダーパスごとの描画を行う
		for (auto& renderPass : m_renderPasses)
		{
			int targetLayerID = renderPass->GetTargetRenderLayerID();
			if (targetLayerID == RenderLayer::LayerID_None)
				continue;

			renderPass->Render(renderObjectsMap[targetLayerID], renderContext);
		}
	}
}

void RenderSystem::AddRenderPass(std::shared_ptr<RenderPass> pRenderPass)
{
	pRenderPass->Init();
	m_renderPasses.push_back(pRenderPass);
}

void RenderSystem::RegisterRenderer(Renderer* pRenderer)
{
	m_pRenderers.push_back(pRenderer);
}

void RenderSystem::UnregisterRenderer(Renderer* pRenderer)
{
	auto it = std::find(m_pRenderers.begin(), m_pRenderers.end(), pRenderer);
	if (it != m_pRenderers.end())
		m_pRenderers.erase(it);
}

void RenderSystem::RegisterCamera(Camera* pCamera)
{
	m_pCameras.push_back(pCamera);
}

void RenderSystem::UnregisterCamera(Camera* pCamera)
{
	auto it = std::find(m_pCameras.begin(), m_pCameras.end(), pCamera);
	if (it != m_pCameras.end())
		m_pCameras.erase(it);
}
