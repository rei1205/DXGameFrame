// Material.cpp
#include "Material.h"
#include "../Manager/ShaderManager.h"

Material::Material()
{
	m_pVertexShader = ShaderManager::LoadVertexShader("output/x64/Debug/VS_Test.cso");
	m_pPixelShader = ShaderManager::LoadPixelShader("output/x64/Debug/PS_Test.cso");

	SetBlendState(BlendStateName::Default);
	SetDepthStencilState(DepthStencilStateName::Default);
	SetRasterizerState(RasterizerStateName::Default);
	for (int i = 0; i < TextureSlot::MaterialSlotCount; ++i)
	{
		SetSamplerState(SamplerStateName::Default, i);
	}
}

void Material::Bind() const
{
	// テクスチャをセット
	for (int i = 0; i < TextureSlot::MaterialSlotCount; ++i)
	{
		if (m_pTextures[i] == nullptr)
			continue;

		TextureManager::SetTexture(m_pTextures[i].get(), i);
	}

	// シェーダーをセット
	ShaderManager::SetVertexShader(m_pVertexShader.get());
	ShaderManager::SetPixelShader(m_pPixelShader.get());

	// 定数バッファをセット
	ConstantBufferManager::SetCustomData(m_customParameter);

	// パイプラインステートをセット
	PipelineStateManager::SetBlendState(m_pBlendState);
	PipelineStateManager::SetDepthStencilState(m_pDepthStencilState);
	PipelineStateManager::SetRasterizerState(m_pRasterizerState);
	for (int i = 0; i < TextureSlot::MaterialSlotCount; ++i)
	{
		PipelineStateManager::SetSamplerState(m_pSamplerState[i], i);
	}
}

void Material::SetTexture(const std::string& filePath, UINT slot)
{
	if (slot >= TextureSlot::MaterialSlotCount)
		return;

	m_pTextures[slot] = TextureManager::LoadTexture(filePath);
}

void Material::SetTexture(std::shared_ptr<Texture> pTexture, UINT slot)
{
	m_pTextures[slot] = pTexture;
}

Texture* Material::GetTexture(UINT slot)
{
	return m_pTextures[slot].get();
}

void Material::SetVertexShader(const std::string& filePath)
{
	m_pVertexShader = ShaderManager::LoadVertexShader(filePath);
}

void Material::SetVertexShader(std::shared_ptr<VertexShader> pVertexShader)
{
	m_pVertexShader = pVertexShader;
}

void Material::SetPixelShader(const std::string& filePath)
{
	m_pPixelShader = ShaderManager::LoadPixelShader(filePath);
}

void Material::SetPixelShader(std::shared_ptr<PixelShader> pPixelShader)
{
	m_pPixelShader = pPixelShader;
}

void Material::SetParameter(const void* pData, UINT size)
{
	if (pData == nullptr || size > CustomCBSize)
		return;

	// データコピー
	m_customParameter.clear();
	m_customParameter.resize(size);
	memcpy(m_customParameter.data(), pData, size);
}

void Material::SetBlendState(const std::string& blendStateName)
{
	m_pBlendState = PipelineStateManager::GetBlendState(blendStateName);
}

void Material::SetDepthStencilState(const std::string& depthStencilStateName)
{
	m_pDepthStencilState = PipelineStateManager::GetDepthStencilState(depthStencilStateName);
}

void Material::SetRasterizerState(const std::string& rasterizerStateName)
{
	m_pRasterizerState = PipelineStateManager::GetRasterizerState(rasterizerStateName);
}

void Material::SetSamplerState(const std::string& samplerStateName, UINT slot)
{
	m_pSamplerState[slot] = PipelineStateManager::GetSamplerState(samplerStateName);
}
