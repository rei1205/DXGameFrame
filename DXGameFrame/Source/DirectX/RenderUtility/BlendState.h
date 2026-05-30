// BlendState.h
#pragma once
#include "../DirectXInclude.h"
#include <string>

/**
 * @brief ブレンドステートを扱う
 */
class BlendState
{
public:
	BlendState();
	~BlendState() = default;

	/**
	 * @brief ブレンドステートを作成する
	 * @param pDesc ブレンドステート設定情報へのポインタ
	 * @param name ブレンドステート名
	 * @return 成功したかを返す
	 */
	HRESULT Create(const D3D11_BLEND_DESC* pDesc, const std::string& name);

	/**
	 * @brief Direct3Dのブレンドステートを取得する
	 * @return ブレンドステートへのポインタ
	 */
	ID3D11BlendState* GetBlendState()
	{
		return m_pBlendState.Get();
	}

	/**
	 * @brief ブレンドステート名を取得する
	 * @return ブレンドステート名
	 */
	std::string GetName()
	{
		return m_name;
	}

private:
	/// ブレンドステート
	ComPtr<ID3D11BlendState> m_pBlendState;

	/// ブレンドステート名
	std::string m_name;
};
