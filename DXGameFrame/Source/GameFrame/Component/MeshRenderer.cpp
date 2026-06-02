// MeshRenderer.cpp
#include "MeshRenderer.h"
#include "Transform.h"

MeshRenderer::MeshRenderer() :
	m_pMesh(nullptr)
{
	m_pMesh = Geometry::GetModel(Geometry::Type::BOX);
	GetMaterials().clear();
	Material material;
	material.SetTexture("Assets/TestImage.png", TextureSlot::Main);
	material.SetVertexShader("output/x64/Debug/VS_Test.cso");
	material.SetPixelShader("output/x64/Debug/PS_Test.cso");
	GetMaterials().push_back(material);
}

void MeshRenderer::Draw(UINT materialIndex)
{
	// Transformからワールド行列をセット
	DirectX::XMMATRIX matrix;
	matrix = GetTransform()->GetWorldMatrix();
	ConstantBufferManager::SetWorld(matrix);

	GetMaterials()[materialIndex].Bind();
	m_pMesh->Draw();
}

void MeshRenderer::SetGeometry(Geometry::Type geometryType)
{
	m_pMesh = Geometry::GetModel(geometryType);
}
