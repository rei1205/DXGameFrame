// Direct3D.cpp
#include "Direct3D.h"

ComPtr<ID3D11Device> Direct3D::s_pDevice = nullptr;
ComPtr<ID3D11DeviceContext> Direct3D::s_pContext = nullptr;
ComPtr<IDXGISwapChain> Direct3D::s_pSwapChain = nullptr;
ComPtr<ID3D11Texture2D> Direct3D::s_pBackBuffer = nullptr;
ComPtr<ID3D11RenderTargetView> Direct3D::s_pBackBufferRTV = nullptr;

HRESULT Direct3D::Init(HWND hWnd, UINT width, UINT height, bool fullScreen)
{
	HRESULT hr = S_OK;

	// デバイス・スワップチェインを作成
	hr = CreateDeviceAndSwapChain(hWnd, width, height, fullScreen);
	if (FAILED(hr)) { return hr; }

	// バックバッファのレンダーターゲットビューを作成
	hr = CreateBackBufferRTV(width, height);
	if (FAILED(hr)) { return hr; }

	return hr;
}

void Direct3D::Uninit()
{
	// リソースの解放
	s_pBackBufferRTV.Reset();
	s_pBackBuffer.Reset();
	s_pSwapChain.Reset();
	s_pContext.Reset();
	s_pDevice.Reset();
}

HRESULT Direct3D::Resize(UINT width, UINT height)
{
	HRESULT hr = S_OK;		// 関数の結果

	// 描画リソースのリセット
	s_pBackBuffer.Reset();

	// スワップチェインのサイズを変更
	hr = ResizeSwapChain(width, height);
	if (FAILED(hr)) { return hr; }

	// バックバッファのレンダーターゲットビューを作成
	hr = CreateBackBufferRTV(width, height);
	if (FAILED(hr)) { return hr; }

	// ビューポート再設定
	SetViewport(width, height);

	return hr;
}

HRESULT Direct3D::CreateDeviceAndSwapChain(HWND hWnd, UINT width, UINT height, bool fullScreen)
{
	HRESULT hr = S_OK;

	// スワップチェインの設定
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.SampleDesc.Count = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 2;
	sd.OutputWindow = hWnd;
	sd.Windowed = fullScreen ? FALSE : TRUE;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// ドライバの種類を設定
	D3D_DRIVER_TYPE driverType;
	D3D_DRIVER_TYPE driverTypes[] = {
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	// 機能レベルを設定
	D3D_FEATURE_LEVEL featureLevel;
	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	// デバイス作成時の動作フラグを設定
	UINT createDeviceFlag = 0;		// デバイス作成時の動作フラグ (デフォルト)
#ifdef _DEBUG
	createDeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;		// デバッグレイヤーをサポート
#endif

	// 作成可能な設定でDirectXの機能を有効化 
	for (UINT i = 0; i < numDriverTypes; ++i)
	{
		// ドライバの種類を一つずつ試す
		driverType = driverTypes[i];

		// ドライバとスワップチェインの作成 (作成可能な範囲で最も性能が良いものを作成)
		hr = D3D11CreateDeviceAndSwapChain(
			NULL,
			driverType,
			NULL,
			createDeviceFlag,
			featureLevels,
			numFeatureLevels,
			D3D11_SDK_VERSION,
			&sd,
			s_pSwapChain.GetAddressOf(),
			s_pDevice.GetAddressOf(),
			&featureLevel,
			s_pContext.GetAddressOf()
		);

		// 作成に成功したら終了
		if (SUCCEEDED(hr)) { break; }
	}

	return hr;
}

HRESULT Direct3D::CreateBackBufferRTV(UINT width, UINT height)
{
	HRESULT hr = S_OK;

	// フレームバッファへのポインタを取得 (IID_PPV_ARGSはGetAddressOf()不要)
	hr = s_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&s_pBackBuffer));
	if (FAILED(hr)) { return hr; }

	// フレームバッファへのポインタで紐づけて、レンダーターゲットビューを作成
	hr = s_pDevice->CreateRenderTargetView(s_pBackBuffer.Get(), NULL, s_pBackBufferRTV.GetAddressOf());

	return hr;
}

HRESULT Direct3D::ResizeSwapChain(UINT width, UINT height)
{
	HRESULT hr = S_OK;

	if (s_pSwapChain == nullptr)
		return S_FALSE;

	hr = s_pSwapChain->ResizeBuffers(
		0, width, height,
		DXGI_FORMAT_UNKNOWN,
		DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH
	);
	if (FAILED(hr)) { return hr; }

	return hr;
}

void Direct3D::SetViewport(UINT width, UINT height)
{
	// ビューポートの設定
	D3D11_VIEWPORT vp = {};			// ビューポート設定情報
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = (float)width;
	vp.Height = (float)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	// ビューポートを設定
	s_pContext->RSSetViewports(1, &vp);
}
