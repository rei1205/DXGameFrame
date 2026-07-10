// DirectionalLight.h
#pragma once
#include "../Core/Component.h"
#include "../../Utility/Color.h"
#include "../../DirectX/Manager/ConstantBufferManager.h"
#include "../Core/ComponentRegisterMeta.h"

REGISTER_COMPONENT(DirectionalLight);

/**
 * @brief 指向性ライト情報を扱う
 */
class DirectionalLight : public Component
{
public:
	DirectionalLight();
	~DirectionalLight() = default;

	/**
	 * @brief 光源色を設定する
	 * @param color 光源色
	 */
	void SetLightColor(Color color);

	/**
	 * @brief ライト情報を取得する
	 * @return 定数バッファ用ライト情報
	 */
	DirectionalLightCB GetLightCB();

	/**
	 * @brief 環境光を設定する
	 * @param color 環境光色
	 */
	void SetAmbientColor(Color color);

	/**
	 * @brief ライトの強さを設定する
	 * @param intensity ライト強度 (デフォルト1)
	 */
	void SetLightIntensity(float intensity);

	/**
	 * @brief ライトの大きさを設定する（シャドウ用）
	 * @param size ライトの大きさ (デフォルト1)
	 */
	void SetLightSize(float size);

	/**
	 * @brief 光源色を取得する
	 * @return 光源色
	 */
	Color GetLightColor();

	/**
	 * @brief 光源色を取得する
	 * @return 光源色
	 */
	Color GetAmbientColor();

	void OnInspector() override;
	void Serialize(nlohmann::json& jsonData) override;
	void Deserialize(const nlohmann::json& jsonData) override;

private:
	/// 光源カラー
	Color m_lightColor;

	/// 環境光
	Color m_ambientColor;

	/// ライトの強さ
	float m_lightIntensity;

	/// ライトの大きさ（シャドウ用）
	float m_lightSize;

public:
	/**
	 * @brief メインライトを取得する
	 * @param シーンへのポインタ
	 * @return メインライトへのポインタ
	 */
	static DirectionalLight* GetMain(Scene* pScene);
};