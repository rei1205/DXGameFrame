// Direct3D.h
#pragma once
#include "DirectXInclude.h"

/**
 * @brief Direct3Dを扱うクラス
 */
class Direct3D
{
public:
	/// 0～1に正規化されたビューポート
	struct NormalizedViewport
	{
		float top = 0.0f;		// 上端
		float left = 0.0f;		// 左端
		float width = 1.0f;		// 幅
		float height = 1.0f;	// 高さ
	};

	/**
	 * @brief DirectXの初期化を行う
	 * @param hWnd ウィンドウハンドル
	 * @param width クライアント領域の幅
	 * @param height クライアント領域の高さ
	 * @param fullScreen フルスクリーン設定
	 * @return 成功したかを返す
	 */
	static HRESULT Init(HWND hWnd, UINT width, UINT height, bool fullScreen);

	/**
	 * @brief DirectXの終了処理
	 */
	static void Uninit();

	/**
	 * @brief ウィンドウサイズが変更時に呼ぶ処理
	 * @param width クライアント領域の幅
	 * @param height クライアント領域の高さ
	 * @return 成功したかを返す
	 */
	static HRESULT Resize(UINT width, UINT height);

	/**
	 * @brief ビューポートを設定する
	 * @param viewport 正規化されたビューポート設定
	 */
	static void SetViewport(NormalizedViewport viewport);

	/**
	 * @brief 描画を開始する
	 * @param clearColor 画面クリア色
	 */
	static void BeginDraw(const float clearColor[4]);

	/**
	 * @brief 描画を終了し画面に出力する
	 */
	static void EndDraw();

	/**
	 * @brief Direct3Dデバイスを取得する
	 * @return Direct3Dデバイスへのポインタ
	 */
	static ID3D11Device* GetDevice()
	{
		return s_pDevice.Get();
	}

	/**
	 * @brief Direct3Dデバイスコンテキストを取得する
	 * @return Direct3Dデバイスコンテキストへのポインタ
	 */
	static ID3D11DeviceContext* GetContext()
	{
		return s_pContext.Get();
	}

	/**
	 * @brief バックバッファのRTVを取得する
	 * @return バックバッファのRTVへのポインタ
	 */
	static ID3D11RenderTargetView* GetBackBufferRTV()
	{
		return s_pBackBufferRTV.Get();
	}

private:
	/// Direct3Dデバイス
	static ComPtr<ID3D11Device> s_pDevice;

	/// Direct3Dデバイスコンテキスト
	static ComPtr<ID3D11DeviceContext> s_pContext;

	/// スワップチェイン
	static ComPtr<IDXGISwapChain> s_pSwapChain;

	/// バックバッファ
	static ComPtr<ID3D11Texture2D> s_pBackBuffer;

	/// バックバッファのRTV
	static ComPtr<ID3D11RenderTargetView> s_pBackBufferRTV;

	/// 画面の幅
	static UINT s_width;

	/// 画面の高さ
	static UINT s_height;

	/// 正規化されたビューポート
	static NormalizedViewport s_normalizedViewport;

	/**
	 * @brief Direct3Dデバイスとスワップチェインを作成する
	 * @param hWnd ウィンドウハンドル
	 * @param width クライアント領域の幅
	 * @param height クライアント領域の高さ
	 * @param fullScreen フルスクリーン設定
	 * @return 成功したかを返す
	 */
	static HRESULT CreateDeviceAndSwapChain(HWND hWnd, UINT width, UINT height, bool fullScreen);

	/**
	 * @brief バックバッファのRTVを作成する
	 * @param width クライアント領域の幅
	 * @param height クライアント領域の高さ
	 * @return 成功したかを返す
	 */
	static HRESULT CreateBackBufferRTV(UINT width, UINT height);

	/**
	 * @brief スワップチェインのサイズを変更する
	 * @param width クライアント領域の幅
	 * @param height クライアント領域の高さ
	 * @return 成功したかを返す
	 */
	static HRESULT ResizeSwapChain(UINT width, UINT height);

	/**
	 * @brief ビューポートに実際のサイズを設定する
	 * @param width クライアント領域の幅
	 * @param height クライアント領域の高さ
	 */
	static void SetViewportSize(UINT width, UINT height);
};
