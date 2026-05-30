// Geometry.h
#pragma once
#include "Mesh.h"
#include <memory>
#include <array>

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
	static HRESULT Init();

	/**
	 * @brief 終了処理
	 */
	static void Uninit();

	/**
	 * @brief ジオメトリメッシュを取得する
	 */
	static std::shared_ptr<Mesh> GetModel(Type geometryType)
	{
		return s_pMeshs[geometryType];
	}

private:
	Geometry() = delete;

	/// 円の頂点数
	static constexpr int CircleVertex = 16;

	/// ジオメトリモデル配列
	static std::array<std::shared_ptr<Mesh>, Type::COUNT> s_pMeshs;

	/**
	 * @brief 箱のメッシュを生成する
	 * @return 成功したかを返す
	 */
	static HRESULT CreateBox();

	/**
	 * @brief 円柱のメッシュを生成する
	 * @return 成功したかを返す
	 */
	static HRESULT CreateCylinder();

	/**
	 * @brief 球のメッシュを生成する
	 * @return 成功したかを返す
	 */
	static HRESULT CreateSphere();

	/**
	 * @brief 板のメッシュを作成する
	 * @return 成功したかを返す
	 */
	static HRESULT CreatePlane();
};
