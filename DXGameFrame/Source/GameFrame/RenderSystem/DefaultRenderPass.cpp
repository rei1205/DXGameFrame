// DefaultRenderPass.h
#include "DefaultRenderPass.h"
#include "../../DirectX/Direct3D.h"

void DefaultRenderPass::Render(
	const std::vector<Renderer*>& renderers, const RenderContext& renderContext)
{
	if (renderContext.pCamera == nullptr)
		return;

	// レンダーターゲットの設定
	SetRenderTarget(renderContext);

	// フレーム定数バッファを更新する
	UpdateFrameCB(renderContext);

	// 描画オブジェクトを描画する
	for (auto& renderer : renderers)
	{
		renderer->Draw();
	}
}

void DefaultRenderPass::SetRenderTarget(const RenderContext& renderContext)
{
	Camera* pCamera = renderContext.pCamera;

	// 描画対象RTVを取得
	Texture* rtTexture = pCamera->GetRTTexture();
	auto rtv = rtTexture->GetRTV();
	if (rtv == nullptr)
		return;

	// 描画対象DSVを取得
	Texture* dsTexture = pCamera->GetDSTexture();
	auto dsv = dsTexture->GetDSV();
	if (dsv == nullptr)
		return;

	// RTV・DSVを設定
	Direct3D::GetContext()->OMSetRenderTargets(1, &rtv, dsv);

	// ビューポートを設定
	Vector2 topLeft = pCamera->GetViewportTopLeft();
	Vector2 size = pCamera->GetViewportSize();
	Texture::Size RTSize = rtTexture->GetSize();
	Direct3D::SetViewport(
		topLeft.x * RTSize.x, topLeft.y * RTSize.y,
		size.x * RTSize.x, size.y * RTSize.y
	);
}

void DefaultRenderPass::UpdateFrameCB(const RenderContext& renderContext)
{
	Camera* pCamera = renderContext.pCamera;

	// ビュー・プロジェクション行列をセット
	DirectX::XMMATRIX view = pCamera->GetViewMatrix();
	DirectX::XMMATRIX projention;
	if (pCamera->IsPerspective())
	{
		projention = pCamera->GetPerspectiveProjectionMatrix();
	}
	else
	{
		projention = pCamera->GetOrthographicProjectionMatrix();
	}
	ConstantBufferManager::SetView(view);
	ConstantBufferManager::SetProjection(projention);

	if (renderContext.pDirectionalLight != nullptr)
	{
		// ライト定数バッファをセット
		DirectionalLightCB lightCB = renderContext.pDirectionalLight->GetLightCB();
		ConstantBufferManager::SetLight(lightCB);
	}

	// フレーム定数バッファ更新
	ConstantBufferManager::ShaderSetBuffer();
	ConstantBufferManager::UpdateFrameCB();
}
