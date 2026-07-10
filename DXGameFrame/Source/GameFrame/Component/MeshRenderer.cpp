// MeshRenderer.cpp
#include "MeshRenderer.h"
#include "Transform.h"
#include "../../DirectX/Manager/ModelManager.h"
#include "../../Utility/InspectorUtility.h"

MeshRenderer::MeshRenderer() :
	m_pModel(nullptr)
{
}

void MeshRenderer::Draw()
{
	if (m_pModel == nullptr)
		return;

	// Transformからワールド行列をセット
	DirectX::XMMATRIX matrix;
	matrix = GetTransform()->GetWorldMatrix();
	ConstantBufferManager::SetWorld(matrix);

	m_pModel->Draw(m_materials);
}

void MeshRenderer::LoadModel(const std::string filePath)
{
	m_pModel = ModelManager::Load(filePath);
}

void MeshRenderer::OnInspector()
{
	// モデルパス入力欄
	static char buffer[256] = {};
	strncpy_s(buffer, sizeof(buffer), m_filePath.c_str(), _TRUNCATE);
	ImGui::InputTextWithHint("FilePath", "path...", buffer, sizeof(buffer));
	m_filePath = buffer;
	ImGui::GetDragAssets(&m_filePath);
	if (ImGui::Button("Load Model"))
	{
		LoadModel(m_filePath);
	}
}

void MeshRenderer::Serialize(nlohmann::json& jsonData)
{
	jsonData["FilePath"] = ModelManager::GetFilePathFromModel(m_pModel.get());
}

void MeshRenderer::Deserialize(const nlohmann::json& jsonData)
{
	m_filePath = jsonData.value("FilePath", "");
	if(m_filePath != "")
	{
		LoadModel(m_filePath);
	}
}
