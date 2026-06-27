// DirectionalLight.cpp
#include "DirectionalLight.h"
#include "Transform.h"
#include "../Core/Scene.h"

DirectionalLight::DirectionalLight() :
	m_lightColor(1.0f, 1.0f, 1.0f, 1.0f),
	m_ambientColor(1.0f, 1.0f, 1.0f, 1.0f),
	m_lightIntensity(1.0f),
	m_lightSize(1.0f)
{
}

void DirectionalLight::SetLightColor(Color color)
{
	m_lightColor = color;
}

DirectionalLightCB DirectionalLight::GetLightCB()
{
	// ライト定数バッファ用データを作成
	DirectionalLightCB lightCB = {};
	Vector3 lightDir = GetTransform()->GetQuaternion() * Vector3::forward;
	lightCB.lightDir = { lightDir.x, lightDir.y, lightDir.z };
	lightCB.lightIntensity = m_lightIntensity;
	lightCB.lightColor = { m_lightColor.r, m_lightColor.g, m_lightColor.b };
	lightCB.ambientColor = { m_ambientColor.r, m_ambientColor.g, m_ambientColor.b };
	lightCB.lightSize = m_lightSize;
	return lightCB;
}

void DirectionalLight::SetAmbientColor(Color color)
{
	m_ambientColor = color;
}

void DirectionalLight::SetLightIntensity(float intensity)
{
	m_lightIntensity = intensity;
}

void DirectionalLight::SetLightSize(float size)
{
	m_lightSize = size;
}

Color DirectionalLight::GetLightColor()
{
	return m_lightColor;
}

Color DirectionalLight::GetAmbientColor()
{
	return m_ambientColor;
}