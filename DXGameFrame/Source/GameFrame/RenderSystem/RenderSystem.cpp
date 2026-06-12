// RenderSystem.cpp
#include "RenderSystem.h"
#include "../Component/Renderer.h"
#include "RenderLayer.h"
#include <unordered_map>
#include <algorithm>

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
		if (!renderer->IsActiveHierarchy())
			continue;

		int renderLayerID = renderer->GetRenderLayerID();
		if (renderLayerID == RenderLayer::LayerID_None)
			continue;

		// マテリアルごとに描画オブジェクトを作成
		std::vector<Material>& materials = renderer->GetMaterials();
		UINT materialCount = (UINT)materials.size();
		for (UINT i = 0; i < materialCount; ++i)
		{
			RenderObject renderObject;
			renderObject.pRenderer = renderer;
			renderObject.materialIndex = i;

			// 描画オブジェクト登録
			auto& vec = renderObjectsMap[renderLayerID];
			vec.push_back(renderObject);
		}
	}

	// カメラをソート
	if (m_cateraSortDirty)
		CameraSort();

	// レンダーコンテキストを作成
	RenderContext renderContext;
	renderContext.pMainLight = m_pMainLight;

	// アクティブなカメラ配列を作成
	renderContext.pSortedCameras = m_pCameras;
	std::erase_if(renderContext.pSortedCameras,
		[](Camera* ptr) { return!ptr->IsActiveHierarchy(); }
	);

	// レンダーパスごとの描画を行う
	for (auto& renderPass : m_renderPasses)
	{
		int targetLayerID = renderPass->GetTargetRenderLayerID();
		if (targetLayerID == RenderLayer::LayerID_None)
			continue;

		// 描画リソースのキャッシュを削除
		ShaderManager::Refresh();
		PipelineStateManager::Refresh();

		renderPass->Render(renderObjectsMap[targetLayerID], renderContext);
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
	SetCameraSortDirty();
}

void RenderSystem::UnregisterCamera(Camera* pCamera)
{
	auto it = std::find(m_pCameras.begin(), m_pCameras.end(), pCamera);
	if (it != m_pCameras.end())
		m_pCameras.erase(it);
}

Camera* RenderSystem::GetMainCamera()
{
	// カメラの描画順ソート
	if (m_cateraSortDirty)
	{
		CameraSort();
	}

	for (int i = (int)m_pCameras.size() - 1; i >= 0; --i)
	{
		if (m_pCameras[i]->IsActiveHierarchy())
			return m_pCameras[i];
	}

	return nullptr;
}

void RenderSystem::CameraSort()
{
	std::sort(m_pCameras.begin(), m_pCameras.end(),
		[](Camera* a, Camera* b)
		{return a->GetPriority() > b->GetPriority(); }
	);
	m_cateraSortDirty = false;
}
