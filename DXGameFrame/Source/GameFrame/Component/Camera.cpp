// Camera.cpp
#include "Camera.h"
#include "Transform.h"
#include "../Core/Scene.h"
#include "../../System/GameWindow.h"

Camera::Camera():
	m_priority(0),
	m_fovAngle(60.0f),
	m_nearZ(0.1f),
	m_farZ(1000.0f),
	m_cameraSize(5.0f),
	m_isPerspective(true)
{
}

void Camera::Awake()
{
	GetScene()->GetRenderSystem().RegisterCamera(this);
}

void Camera::OnDestroy()
{
	GetScene()->GetRenderSystem().UnregisterCamera(this);
}

void Camera::SetPriority(int priority)
{
	m_priority = priority;
	GetScene()->GetRenderSystem().SetCameraSortDirty();
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

	GameWindow::Size screenSize = GameWindow::GetClientSize();
	float aspect = (float)screenSize.width / (float)screenSize.height;

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

	GameWindow::Size screenSize = GameWindow::GetClientSize();
	float aspect = (float)screenSize.width / (float)screenSize.height;

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

Camera* Camera::GetMain(Scene* pScnen)
{
	return pScnen->GetRenderSystem().GetMainCamera();
}

DirectX::XMMATRIX Camera::GetDefaultViewMatrix()
{
	DirectX::XMMATRIX view;		// 計算用ビュー行列

	// ビュー行列を求める
	view = DirectX::XMMatrixTranslation(0.0f, 0.0f, -10.0f);
	view = DirectX::XMMatrixInverse(nullptr, view);
	return view;
}
