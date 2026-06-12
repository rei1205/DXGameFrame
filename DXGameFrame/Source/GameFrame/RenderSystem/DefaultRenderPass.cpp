// DefaultRenderPass.h
#include "DefaultRenderPass.h"
#include "RenderLayer.h"
#include "../../DirectX/Direct3D.h"

DefaultRenderPass::DefaultRenderPass()
{
	SetTargetRenderLayer("Default");
}

void DefaultRenderPass::Render(
	const std::vector<RenderObject>& renderObjects, const RenderContext& renderContext)
{
	if (renderContext.pSortedCameras.size() == 0)
		return;

	auto rtv = Direct3D::GetBackBufferRTV();
	Direct3D::GetContext()->OMSetRenderTargets(1, &rtv, nullptr);

	// ビュー・プロジェクション行列をセット
	Camera* camera = renderContext.pSortedCameras.back();
	DirectX::XMMATRIX view = camera->GetViewMatrix();
	DirectX::XMMATRIX projention;
	if (camera->IsPerspective())
	{
		projention = camera->GetPerspectiveProjectionMatrix();
	}
	else
	{
		projention = camera->GetOrthographicProjectionMatrix();
	}
	ConstantBufferManager::SetView(view);
	ConstantBufferManager::SetProjection(projention);

	// ライト定数バッファをセット
	DirectionalLightCB lightCB = renderContext.pMainLight->GetLightCB();
	ConstantBufferManager::SetLight(lightCB);

	// フレーム定数バッファ更新
	ConstantBufferManager::ShaderSetBuffer();
	ConstantBufferManager::UpdateFrameCB();

	// 描画オブジェクトを描画する
	int renderObjectCount = (int)renderObjects.size();
	for (int i = 0; i < renderObjectCount; ++i)
	{
		renderObjects[0].pRenderer->Draw(renderObjects[0].materialIndex);
	}
}
