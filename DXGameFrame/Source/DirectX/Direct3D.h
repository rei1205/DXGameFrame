// Direct3D.h
#pragma once
#include "DirectXInclude.h"

/**
 * @brief Direct3Dを扱うクラス
 */
class Direct3D
{
public:
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
	 * @brief Direct3Dデバイスを取得する
	 * @return Direct3Dデバイスへのポインタ
	 */
	static ID3D11Device* GetDevice()
	{
		return s_pDevice.Get();
	}

	/**
	 * @brief Direct3Dデバイスコンテキスト
	 * @return Direct3Dデバイスコンテキストへのポインタ
	 */
	static ID3D11DeviceContext* GetContext()
	{
		return s_pContext.Get();
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
	static 	HRESULT ResizeSwapChain(UINT width, UINT height);

	/**
	 * @brief ビューポートを設定する
	 * @param width クライアント領域の幅
	 * @param height クライアント領域の高さ
	 */
	static void SetViewport(UINT width, UINT height);
};
