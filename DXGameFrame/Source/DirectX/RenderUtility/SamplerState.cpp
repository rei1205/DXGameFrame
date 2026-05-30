// SamplerState.cpp
#include "SamplerState.h"
#include "../Direct3D.h"

SamplerState::SamplerState() :
	m_pSamplerState(nullptr),
	m_name("No Name")
{
}

HRESULT SamplerState::Create(const D3D11_SAMPLER_DESC* pDesc, const std::string& name)
{
	HRESULT hr = S_OK;

	// サンプラーステートの作成
	hr = Direct3D::GetDevice()->CreateSamplerState(pDesc, m_pSamplerState.GetAddressOf());
	if (FAILED(hr)) { return hr; }

	m_name = name;
	return hr;
}
