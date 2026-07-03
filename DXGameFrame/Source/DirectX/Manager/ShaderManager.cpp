// ShaderManager.cpp
#include "ShaderManager.h"
#include "../Direct3D.h"
#include "../../System/Debug.h"

std::unordered_map<std::string, std::shared_ptr<VertexShader>> ShaderManager::s_vertexShaders;
std::unordered_map<std::string, std::shared_ptr<PixelShader>> ShaderManager::s_pixelShaders;
ID3D11VertexShader* ShaderManager::s_pCurrentVS = nullptr;
ID3D11PixelShader* ShaderManager:: s_pCurrentPS = nullptr;

std::shared_ptr<VertexShader> ShaderManager::LoadVertexShader(const std::string& filePath)
{
	// 頂点シェーダー検索
	auto it = s_vertexShaders.find(filePath);
	if (it != s_vertexShaders.end())
	{
		// 既存のシェーダーを返す
		return it->second;
	}

	// 新規シェーダー読み込み・追加
	auto newVS = std::make_shared<VertexShader>();
	newVS->Load(filePath);
	s_vertexShaders[filePath] = newVS;
	return newVS;
}

std::shared_ptr<PixelShader> ShaderManager::LoadPixelShader(const std::string& filePath)
{
	// ピクセルシェーダー検索
	auto it = s_pixelShaders.find(filePath);
	if (it != s_pixelShaders.end())
	{
		// 既存のシェーダーを返す
		return it->second;
	}

	// 新規シェーダー読み込み・追加
	auto newPS = std::make_shared<PixelShader>();
	newPS->Load(filePath);
	s_pixelShaders[filePath] = newPS;
	return newPS;
}

void ShaderManager::SetVertexShader(VertexShader* pVertexShader)
{
	ID3D11VertexShader* pVS = pVertexShader->GetVertexShader();
	if (pVS == s_pCurrentVS)
		return;

	// シェーダーをセット
	s_pCurrentVS = pVS;
	Direct3D::GetContext()->VSSetShader(pVS, nullptr, 0);
	Direct3D::GetContext()->IASetInputLayout(pVertexShader->GetInputLayout());
}

void ShaderManager::SetPixelShader(PixelShader* pPixelShader)
{
	ID3D11PixelShader* pPS = pPixelShader->GetPixelShader();
	if (pPS == s_pCurrentPS)
		return;

	// シェーダーをセット
	s_pCurrentPS = pPS;
	Direct3D::GetContext()->PSSetShader(pPS, nullptr, 0);
}

void ShaderManager::Clear()
{
	s_vertexShaders.clear();
	s_pixelShaders.clear();
	s_pCurrentVS = nullptr;
	s_pCurrentPS = nullptr;

	Debug::ConsoleLog("Clear : ShaderManager");
}
