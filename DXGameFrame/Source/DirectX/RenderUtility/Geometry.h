// Geometry.h
#pragma once
#include <memory>
#include <array>
#include "Mesh.h"

class Geometry
{
public:
	/// ジオメトリタイプ
	enum Type
	{
		BOX,		// 箱
		CYLINDER,	// 円柱
		SHPERE,		// 球
		PLANE,		// 板
		COUNT
	};

	/**
	 * @brief ジオメトリの初期化
	 * @return 成功したかを返す
	 */
	HRESULT Init();

	/**
	 * @brief 終了処理
	 */
	void Uninit();

	/**
	 * @brief ジオメトリメッシュを取得する
	 */
	std::shared_ptr<Mesh> GetModel(Type geometryType);

private:
	Geometry() = default;

	/// 円の頂点数
	static constexpr int CircleVertex = 16;

	/// ジオメトリモデル配列
	std::array<std::shared_ptr<Mesh>, Type::COUNT> m_pMeshs;

	/**
	 * @brief 箱のメッシュを生成する
	 * @return 成功したかを返す
	 */
	HRESULT CreateBox();

	/**
	 * @brief 円柱のメッシュを生成する
	 * @return 成功したかを返す
	 */
	HRESULT CreateCylinder();

	/**
	 * @brief 球のメッシュを生成する
	 * @return 成功したかを返す
	 */
	HRESULT CreateSphere();

	/**
	 * @brief 板のメッシュを作成する
	 * @return 成功したかを返す
	 */
	HRESULT CreatePlane();
};
