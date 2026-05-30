// PipelineStateManager.h
#pragma once
#include "../RenderUtility/BlendState.h"
#include "../RenderUtility/DepthStencilState.h"
#include "../RenderUtility/RasterizerState.h"
#include "../RenderUtility/SamplerState.h"
#include <memory>
#include <unordered_map>

/// 初期ブレンドステート名
namespace BlendStateName
{
	constexpr const char* None = "None";			// ブレンド無し
	constexpr const char* Alpha = "Alpha";			// 通常のアルファブレンド
	constexpr const char* Add = "Add";				// 加算
	constexpr const char* Subtract = "Subtract";	// 減算
	constexpr const char* Multiply = "Multiply";	// 乗算
	constexpr const char* Disable = "Disable";		// カラー描画無し

	constexpr const char* Default = None;			// デフォルトブレンドステート
}

/// 初期深度ステンシルステート名
namespace DepthStencilStateName
{
	constexpr const char* Write = "Write";			// 深度テストON 深度書き込みON (通常)
	constexpr const char* ReadOnly = "ReadOnly";	// 深度テストON 深度書き込みOFF (半透明用)
	constexpr const char* Disable = "Disable";		// 深度テストOFF (UI・2D用)

	constexpr const char* Default = Write;			// デフォルト深度ステンシルステート
}

/// 初期ラスタライザーステート名
namespace RasterizerStateName
{
	constexpr const char* Front = "Front";				// 前面描画
	constexpr const char* Back = "Back";				// 背面描画
	constexpr const char* None = "None";				// 両面描画
	constexpr const char* Wireframe = "Wireframe";		// ワイヤーフレーム描画

	constexpr const char* Default = Front;				// デフォルトラスタライザーステート
}

/// 初期サンプラーステート名
namespace SamplerStateName
{
	constexpr const char* Linear_Wrap = "Linear_Wrap";					// 線形補間 + 繰り返し
	constexpr const char* Linear_Clamp = "Linear_Clamp";				// 線形補間 + 端固定
	constexpr const char* Linear_Border_Black = "Linear_Border_Black";	// 線形補間 + 枠外黒
	constexpr const char* Linear_Border_White = "Linear_Border_White";	// 線形補間 + 枠外白
	constexpr const char* Point_Wrap = "Point_Wrap";					// 最近傍 + 繰り返し
	constexpr const char* Point_Clamp = "Point_Clamp";					// 最近傍 + 端固定
	constexpr const char* Point_Border_Black = "Point_Border_Black";	// 最近傍 + 枠外黒
	constexpr const char* Point_Border_White = "Point_Border_White";	// 最近傍 + 枠外白

	constexpr const char* Default = Linear_Wrap;						// デフォルトサンプラーステート
}

/**
 * @brief パイプラインステートを扱う
 */
class PipelineStateManager
{
public:
	/**
	 * @brief パイプラインステートの初期化を行う
	 * @return 成功したかを返す
	 */
	static HRESULT Init();

	/**
	 * @brief 終了処理
	 */
	static void Uninit();

	/**
	 * @brief ブレンドステートを取得する
	 * @param name ブレンドステート名
	 * @return ブレンドステートへのポインタ
	 */
	static BlendState* GetBlendState(const std::string& name);

	/**
	 * @brief 深度ステンシルステートを取得する
	 * @param name 深度ステンシルステート名
	 * @return 深度ステンシルステートへのポインタ
	 */
	static DepthStencilState* GetDepthStencilState(const std::string& name);

	/**
	 * @brief ラスタライザーステートを取得する
	 * @param name ラスタライザーステート名
	 * @return ラスタライザーステートへのポインタ
	 */
	static RasterizerState* GetRasterizerState(const std::string& name);

	/**
	 * @brief サンプラーステートを取得する
	 * @param name サンプラーステート名
	 * @return サンプラーステートへのポインタ
	 */
	static SamplerState* GetSamplerState(const std::string& name);

	/**
	 * @brief ブレンドステートを作成する
	 * @param pDesc ブレンドステート設定情報へのポインタ
	 * @param name ブレンドステート名
	 * @return 成功したかを返す
	 */
	static HRESULT CreateBlendStates(const D3D11_BLEND_DESC* pDesc, const std::string& name);

	/**
	 * @brief 深度ステンシルステートを作成する
	 * @param pDesc 深度ステンシルステート設定情報へのポインタ
	 * @param name 深度ステンシルステート名
	 * @return 成功したかを返す
	 */
	static HRESULT CreateDepthStencilStates(const D3D11_DEPTH_STENCIL_DESC* pDesc, const std::string& name);

	/**
	 * @brief ラスタライザーステートを作成する
	 * @param pDesc ラスタライザーステート設定情報へのポインタ
	 * @param name ラスタライザーステート名
	 * @return 成功したかを返す
	 */
	static HRESULT CreateRasterizerStates(const D3D11_RASTERIZER_DESC* pDesc, const std::string& name);

	/**
	 * @brief サンプラーステートを作成する
	 * @param pDesc サンプラーステート設定情報へのポインタ
	 * @param name サンプラーステート名
	 * @return 成功したかを返す
	 */
	static HRESULT CreateSamplerStates(const D3D11_SAMPLER_DESC* pDesc, const std::string& name);

private:
	PipelineStateManager() = delete;

	/// ブレンドステートの名前マップ
	static std::unordered_map<std::string, std::shared_ptr<BlendState>> s_blendStates;

	/// 深度ステンシルステートの名前マップ
	static std::unordered_map<std::string, std::shared_ptr<DepthStencilState>> s_depthStencilStates;

	/// ラスタライザーステートの名前マップ
	static std::unordered_map<std::string, std::shared_ptr<RasterizerState>> s_rasterizerStates;

	/// サンプラーステートの名前マップ
	static std::unordered_map<std::string, std::shared_ptr<SamplerState>> s_samplerStates;

	/// 現在セットされているブレンドステート
	static BlendState* s_pCurrentBlendState;

	/// 現在セットされているブレンドステート
	static DepthStencilState* s_pCurrentDepthStencilState;

	/// 現在セットされているブレンドステート
	static RasterizerState* s_pCurrentRasterizerState;

	/// 現在セットされているブレンドステート
	static SamplerState* s_pCurrentSamplerState;

	/**
	 * @brief 初期ブレンドステートを作成する
	 * @return 成功したかを返す
	 */
	static HRESULT CreateDefaultBlendStates();

	/**
	 * @brief 初期深度ステンシルステートを作成する
	 * @return 成功したかを返す
	 */
	static HRESULT CreateDefaultDepthStencilStates();

	/**
	 * @brief 初期ラスタライザーステートを作成する
	 * @return 成功したかを返す
	 */
	static HRESULT CreateDefaultRasterizerStates();

	/**
	 * @brief 初期サンプラーステートを作成する
	 * @return 成功したかを返す
	 */
	static HRESULT CreateDefaultSamplerStates();
};
