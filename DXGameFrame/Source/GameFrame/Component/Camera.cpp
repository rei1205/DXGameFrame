// Camera.cpp
#include "Camera.h"
#include "Transform.h"
#include "../Core/Scene.h"
#include "../../DirectX/Manager/RenderTargetManager.h"
#include "../../Utility/InspectorUtility.h"
#include "../../Utility/SerializeUtility.h"

Camera::Camera():
	m_priority(0),
	m_fovAngle(60.0f),
	m_nearZ(0.1f),
	m_farZ(1000.0f),
	m_cameraSize(5.0f),
	m_isPerspective(true),
	m_pRTTexture(nullptr),
	m_pDSTexture(nullptr)
{
	m_viewportTopLeft.SetVector(0.0f, 0.0f);
	m_viewportSize.SetVector(1.0f, 1.0f);

	m_pRTTexture = RenderTargetManager::GetRTVTexture(RTVType::SCENE);
	m_pDSTexture = RenderTargetManager::GetDSVTexture(DSVType::SCENE);
}

DirectX::XMMATRIX Camera::GetViewMatrix()
{
	DirectX::XMMATRIX view;		// 計算用ビュー行列

	// ビュー行列を求める
	view = GetTransform()->GetWorldMatrix();
	view = DirectX::XMMatrixInverse(nullptr, view);
	return view;
}

DirectX::XMMATRIX Camera::GetPerspectiveProjectionMatrix()
{
	DirectX::XMMATRIX projection;		// 計算用プロジェクション行列

	Texture::Size RTSize = m_pRTTexture->GetSize();
	float aspect = (float)RTSize.x / (float)RTSize.y;

	// プロジェクション行列を求める
	projection = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XMConvertToRadians(m_fovAngle),
		aspect, m_nearZ, m_farZ
	);
	return projection;
}

DirectX::XMMATRIX Camera::GetOrthographicProjectionMatrix()
{
	DirectX::XMMATRIX projection;		// 計算用プロジェクション行列

	Texture::Size RTSize = m_pRTTexture->GetSize();
	float aspect = (float)RTSize.x / (float)RTSize.y;

	// 投影サイズを求める
	float halfWidth = m_cameraSize;
	float halfHeight = m_cameraSize / aspect;

	// プロジェクション行列を求める
	projection = DirectX::XMMatrixOrthographicOffCenterLH(
		-halfWidth, halfWidth, -halfHeight, halfHeight,
		m_nearZ, m_farZ
	);
	return projection;
}

void Camera::OnInspector()
{
	ImGui::DragInt("カメラ優先度", &m_priority, 0.01f);

	ImGui::Checkbox("透視投影", &m_isPerspective);
	if (m_isPerspective)
	{
		ImGui::DragFloat("視野角", &m_fovAngle, 0.1f, 0.1f, 180.0f);
	}
	else
	{
		ImGui::DragFloat("カメラサイズ", &m_cameraSize, 0.01f, 0.01f, 100.0f);
	}

	ImGui::DragVector2("ビューポート左上座標", &m_viewportTopLeft, 0.01f, 0.0f, 1.0f);
	ImGui::DragVector2("ビューポートサイズ", &m_viewportSize, 0.01f, 0.01f, 1.0f);
}

void Camera::Serialize(nlohmann::json& jsonData)
{
	SerializeUtility::SerializeValue(jsonData, "m_priority", m_priority);
	SerializeUtility::SerializeValue(jsonData, "m_isPerspective", m_isPerspective);
	SerializeUtility::SerializeValue(jsonData, "m_fovAngle", m_fovAngle);
	SerializeUtility::SerializeValue(jsonData, "m_cameraSize", m_cameraSize);
	SerializeUtility::SerializeValue(jsonData, "m_viewportTopLeft", m_viewportTopLeft);
	SerializeUtility::SerializeValue(jsonData, "m_viewportSize", m_viewportSize);
}

void Camera::Deserialize(const nlohmann::json& jsonData)
{
	SerializeUtility::DeserializeValue(jsonData, "m_priority", m_priority);
	SerializeUtility::DeserializeValue(jsonData, "m_isPerspective", m_isPerspective);
	SerializeUtility::DeserializeValue(jsonData, "m_fovAngle", m_fovAngle);
	SerializeUtility::DeserializeValue(jsonData, "m_cameraSize", m_cameraSize);
	SerializeUtility::DeserializeValue(jsonData, "m_viewportTopLeft", m_viewportTopLeft);
	SerializeUtility::DeserializeValue(jsonData, "m_viewportSize", m_viewportSize);
}

Camera* Camera::GetMain(Scene* pScnen)
{
	auto cameras = pScnen->GetComponentManager().GetCameras();
	auto it = std::max_element(cameras.begin(), cameras.end(),
		[](Camera* a, Camera* b)
		{
			return a->GetPriority() < b->GetPriority();
		});

	if (it == cameras.end())
		return nullptr;

	return *it;
}

DirectX::XMMATRIX Camera::GetDefaultViewMatrix()
{
	DirectX::XMMATRIX view;		// 計算用ビュー行列

	// ビュー行列を求める
	view = DirectX::XMMatrixTranslation(0.0f, 0.0f, -10.0f);
	view = DirectX::XMMatrixInverse(nullptr, view);
	return view;
}
