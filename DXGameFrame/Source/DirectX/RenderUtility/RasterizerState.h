// RasterizerState.h
#pragma once
#include "../DirectXInclude.h"
#include <string>

/**
 * @brief ラスタライザーステートを扱う
 */
class RasterizerState
{
public:
	RasterizerState();
	~RasterizerState() = default;

	/**
	 * @brief ラスタライザーステートを作成する
	 * @param pDesc ラスタライザーステート設定情報へのポインタ
	 * @param name ラスタライザーステート名
	 * @return 成功したかを返す
	 */
	HRESULT Create(const D3D11_RASTERIZER_DESC* pDesc, const std::string& name);

	/**
	 * @brief Direct3Dのラスタライザーステートを取得する
	 * @return ラスタライザーステートへのポインタ
	 */
	ID3D11RasterizerState* GetRasterizerState()
	{
		return m_pRasterizerState.Get();
	}

	/**
	 * @brief ラスタライザーステート名を取得する
	 * @return ラスタライザーステート名
	 */
	std::string GetName()
	{
		return m_name;
	}

private:
	/// ラスタライザーステート
	ComPtr<ID3D11RasterizerState> m_pRasterizerState;

	/// ラスタライザーステート名
	std::string m_name;
};
