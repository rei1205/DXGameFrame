// DepthStencilState.h
#pragma once
#include "../DirectXInclude.h"
#include <string>

/**
 * @brief 深度ステンシルステートを扱う
 */
class DepthStencilState
{
public:
	DepthStencilState();
	~DepthStencilState() = default;

	/**
	 * @brief 深度ステンシルステートを作成する
	 * @param pDesc 深度ステンシルステート設定情報へのポインタ
	 * @param name 深度ステンシルステート名
	 * @return 成功したかを返す
	 */
	HRESULT Create(const D3D11_DEPTH_STENCIL_DESC* pDesc, const std::string& name);

	/**
	 * @brief Direct3Dの深度ステンシルステートを取得する
	 * @return 深度ステンシルステートへのポインタ
	 */
	ID3D11DepthStencilState* GetDepthStencilState()
	{
		return m_pDepthStencilState.Get();
	}

	/**
	 * @brief 深度ステンシルステート名を取得する
	 * @return 深度ステンシルステート名
	 */
	std::string GetName()
	{
		return m_name;
	}

private:
	/// 深度ステンシルステート
	ComPtr<ID3D11DepthStencilState> m_pDepthStencilState;

	/// 深度ステンシルステート名
	std::string m_name;
};
