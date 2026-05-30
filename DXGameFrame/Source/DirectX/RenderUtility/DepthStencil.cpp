// DepthStencilState.cpp
#include "DepthStencilState.h"
#include "../Direct3D.h"

DepthStencilState::DepthStencilState() :
	m_pDepthStencilState(nullptr),
	m_name("No Name")
{
}

HRESULT DepthStencilState::Create(const D3D11_DEPTH_STENCIL_DESC* pDesc, const std::string& name)
{
	HRESULT hr = S_OK;

	// 深度ステンシルステートの作成
	hr = Direct3D::GetDevice()->CreateDepthStencilState(pDesc, m_pDepthStencilState.GetAddressOf());
	if (FAILED(hr)) { return hr; }

	m_name = name;
	return hr;
}
