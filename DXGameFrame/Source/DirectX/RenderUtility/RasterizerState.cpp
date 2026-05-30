// RasterizerState.cpp
#include "RasterizerState.h"
#include "../Direct3D.h"

RasterizerState::RasterizerState() :
	m_pRasterizerState(nullptr),
	m_name("No Name")
{
}

HRESULT RasterizerState::Create(const D3D11_RASTERIZER_DESC* pDesc, const std::string& name)
{
	HRESULT hr = S_OK;

	// ラスタライザーステートの作成
	hr = Direct3D::GetDevice()->CreateRasterizerState(pDesc, m_pRasterizerState.GetAddressOf());
	if (FAILED(hr)) { return hr; }

	m_name = name;
	return hr;
}
