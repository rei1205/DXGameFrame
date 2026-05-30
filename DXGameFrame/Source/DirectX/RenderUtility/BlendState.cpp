// BlendState.cpp
#include "BlendState.h"
#include "../Direct3D.h"

BlendState::BlendState() :
	m_pBlendState(nullptr),
	m_name("No Name")
{
}

HRESULT BlendState::Create(const D3D11_BLEND_DESC* pDesc, const std::string& name)
{
	HRESULT hr = S_OK;

	// ブレンドステートの作成
	hr = Direct3D::GetDevice()->CreateBlendState(pDesc, m_pBlendState.GetAddressOf());
	if (FAILED(hr)) { return hr; }

	m_name = name;
	return hr;
}
