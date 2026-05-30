// ConstantBufferManager.h
#pragma once
#include "../DirectXInclude.h"
#include <vector>

 /// 最大ボーン数
constexpr UINT MaxBone = 64;

/// カスタム定数バッファサイズ
constexpr UINT CustomCBSize = 256;

/// ディレクショナルライト定数バッファ
struct DirectionalLightCB
{
	DirectX::XMFLOAT3 lightDir;				// ライト方向
	float lightIntensity;					// ライトの強さ
	DirectX::XMFLOAT3 lightColor;			// ライト色
	float lightSize;						// ライトの大きさ（シャドウ用）
	DirectX::XMFLOAT3 ambientColor;			// 環境光
	float pad;
	DirectX::XMFLOAT4X4 lightViewProj;		// ライトビュー・プロジェクション行列
};

/// ボーン定数バッファ
struct BoneCB
{
	DirectX::XMFLOAT4X4 bones[MaxBone];		// ボーン行列
};

/// カスタム定数バッファ
struct CustomCB
{
	BYTE data[CustomCBSize];	// カスタムパラメータ
};

/**
 * @brief 定数バッファを扱う
 */
class ConstantBufferManager
{
public:
	/**
	 * @brief 定数バッファの初期化
	 * @return 成功したかを返す
	 */
	static HRESULT Init();

	/**
	 * @brief 終了処理
	 */
	static void Uninit();

	/**
	 * @brief シェーダーに定数バッファをセットする
	 */
	static void ShaderSetBuffer();

	/**
	 * @brief ワールド行列を設定する
	 * @param world 設定するワールド行列
	 */
	static void SetWorld(const DirectX::XMMATRIX& world);

	/**
	 * @brief ビュー行列を設定する
	 * @param view 設定するビュー行列
	 */
	static void SetView(const DirectX::XMMATRIX& view);

	/**
	 * @brief プロジェクション行列を設定する
	 * @param view 設定するプロジェクション行列
	 */
	static void SetProjection(const DirectX::XMMATRIX& projection);

	/**
	 * @brief ライト定数バッファを設定する
	 * @param light 設定するライト定数バッファ情報
	 */
	static void SetLight(const DirectionalLightCB& light);

	/**
	 * @brief 現在の経過時間を設定する
	 * @param time ゲーム開始から現在の経過時間
	 */
	static void SetTime(float time);

	/**
	 * @brief ボーン情報を設定する
	 * @param bones ボーン定数バッファ
	 */
	static void SetBone(DirectX::XMFLOAT4X4 bones[MaxBone]);

	/**
	 * @brief カスタムデータを設定する
	 * @param data カスタムデータへのポインタ
	 */
	static void SetCustomData(const std::vector<BYTE>& data);

	/**
	 * @brief フレーム更新定数バッファを更新する
	 */
	static void UpdateFrameCB();

private:
	ConstantBufferManager() = delete;

	/// WVP定数バッファのスロット番号
	enum class SlotNum : UINT
	{
		WORLD,		// ワールド行列
		FRAME,		// フレーム更新情報
		BONE,		// ボーン情報
		CUSTOM,		// カスタムパラメータ
		COUNT		// 使用スロット数
	};

	/// ワールド行列定数バッファ
	struct WorldCB
	{
		DirectX::XMFLOAT4X4 world;		// ワールド行列
		DirectX::XMFLOAT4X4 invWorld;	// ワールド逆行列
	};

	/// フレーム更新定数バッファ
	struct FrameCB
	{
		DirectX::XMFLOAT4X4 view;			// ビュー行列
		DirectX::XMFLOAT4X4 projection;		// プロジェクション行列

		DirectX::XMFLOAT3 cameraPos;		// カメラ位置
		float time;							// 経過時間

		DirectionalLightCB lightCB;			// ライト定数バッファ
	};

	// フレーム更新定数バッファの情報
	static FrameCB m_frameCB;

	/// ワールド行列定数バッファ
	static ComPtr<ID3D11Buffer> m_pWorldBuffer;

	/// フレーム更新定数バッファ
	static ComPtr<ID3D11Buffer> m_pFrameBuffer;

	/// ボーン定数バッファ
	static ComPtr<ID3D11Buffer> m_pBoneBuffer;

	/// カスタム定数バッファ
	static ComPtr<ID3D11Buffer> m_pCustomBuffer;

	/**
	 * @brief 全ての定数バッファを作成する
	 * @return 成功したかを返す
	 */
	static HRESULT CreateAllBuffer();
};