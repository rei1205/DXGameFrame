// ImGuiManager.h
#pragma once
#include "../DirectX/DirectXInclude.h"
#include <ImGui/imgui.h>

/**
 * @brief ImGuiの機能を扱う
 */
class ImGuiManager
{
public:
	/**
	 * @brief ImGuiの初期化を行う
	 * @param hWnd ウィンドウハンドル
	 * @param pDevice D3Dデバイスへのポインタ
	 * @param pContext D3Dデバイスコンテキストへのポインタ
	 */
	static void Init(HWND hWnd, ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/**
	 * @brief 終了処理
	 */
	static void Uninit();

	/**
	 * @brief フレーム開始処理
	 */
	static void BeginFrame();
	
	/**
	 * @brief フレーム終了処理
	 */
	static void EndFrame();

private:
	/// 初期化済みフラグ
	static bool m_isInitialized;

	/**
	 * @brief ドッキングスペースを描画
	 */
	static void DrawDockSpace();
};
