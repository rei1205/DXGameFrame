// SamplerState.h
#pragma once
#include "../DirectXInclude.h"
#include <string>

/**
 * @brief サンプラーステートを扱う
 */
class SamplerState
{
public:
	SamplerState();
	~SamplerState() = default;

	/**
	 * @brief サンプラーステートを作成する
	 * @param pDesc サンプラーステート設定情報へのポインタ
	 * @param name サンプラーステート名
	 * @return 成功したかを返す
	 */
	HRESULT Create(const D3D11_SAMPLER_DESC* pDesc, const std::string& name);

	/**
	 * @brief Direct3Dのサンプラーステートを取得する
	 * @return サンプラーステートへのポインタ
	 */
	ID3D11SamplerState* GetSamplerState()
	{
		return m_pSamplerState.Get();
	}

	/**
	 * @brief サンプラーステート名を取得する
	 * @return サンプラーステート名
	 */
	std::string GetName()
	{
		return m_name;
	}

private:
	/// サンプラーステート
	ComPtr<ID3D11SamplerState> m_pSamplerState;

	/// サンプラーステート名
	std::string m_name;
};
