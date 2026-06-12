// Camera.h
#pragma once
#include "Component.h"
#include "../../DirectX/DirectXInclude.h"
#include "../../Utility/Vector2.h"

/**
 * @brief カメラ情報を扱う
 */
class Camera : public Component
{
public:
	Camera();
	~Camera() = default;

	virtual void Awake();
	virtual void OnDestroy();
	
	/**
	 * @brief カメラ優先度を設定する
	 * @param priority カメラ優先度 (値が大きいほど優先されます)
	 */
	void SetPriority(int priority);

	/**
	 * @brief カメラ優先度を取得する
	 * @return カメラ優先度
	 */
	int GetPriority() const
	{
		return m_priority;
	}

	/**
	 * @brief 視野角を設定する
	 * @param fovAngle 視野角
	 */
	void SetFovAngle(float fovAngle)
	{
		m_fovAngle = fovAngle;
	}

	/**
	 * @brief 視野角を取得する
	 * @return 視野角
	 */
	float GetFovAngle() const
	{
		return m_fovAngle;
	}

	/**
	 * @brief カメラの描画Z範囲を設定する
	 * @param nearZ 奥行き最小値
	 * @param farZ 奥行き最大値
	 */
	void SetNearFar(float nearZ, float farZ)
	{
		m_nearZ = nearZ;
		m_farZ = farZ;
	}

	/**
	 * @brief カメラの奥行き最小値を取得する
	 * @return 奥行き最小値
	 */
	float GetNear() const
	{
		return m_nearZ;
	}

	/**
	 * @brief カメラの奥行き最大値を取得する
	 * @return 奥行き最大値
	 */
	float GetFar() const
	{
		return m_farZ;
	}

	/**
	 * @brief カメラのサイズを設定する (平行投影用)
	 * @param cameraSize カメラサイズ
	 */
	void SetCameraSize(float cameraSize)
	{
		m_cameraSize = cameraSize;
	}

	/**
	 * @brief カメラサイズを取得する (平行投影用)
	 * @return カメラサイズ
	 */
	float GetCameraSize() const
	{
		return m_cameraSize;
	}

	/**
	 * @brief このカメラの透視投影フラグを設定する
	 * @param isPerspective このカメラを透視投影カメラとして使用するか
	 */
	void SetPerspective(bool isPerspective)
	{
		m_isPerspective = isPerspective;
	}

	/**
	 * @brief このカメラの透視投影フラグを取得する
	 * @return このカメラを透視投影カメラとして使用するか
	 */
	bool IsPerspective() const
	{
		return m_isPerspective;
	}

	/**
	 * @brief ビューポートを設定する (0～1指定)
	 * @param x 左上のx座標
	 * @param y 左上のy座標
	 * @param w ビューポートの幅
	 * @param h ビューポートの高さ
	 * @return 
	 */
	float SetViewportRect(float x, float y, float w, float h)
	{
		m_viewportTopLeft.SetVector(x, y);
		m_viewportSize.SetVector(w, h);
	}

	/**
	 * @brief ビューポートの左上座標を取得する
	 * @return ビューポートの左上座標
	 */
	Vector2 GetViewportTopLeft() const
	{
		return m_viewportTopLeft;
	}

	/**
	 * @brief ビューポートのサイズを取得する
	 * @return ビューポートのサイズ
	 */
	Vector2 GetViewportSize() const
	{
		return m_viewportSize;
	}

	/**
	 * @brief このカメラからビュー行列を作成する
	 * @return ビュー行列
	 */
	DirectX::XMMATRIX GetViewMatrix();

	/**
	 * @brief このカメラからプロジェクション行列を作成する
	 * @return プロジェクション行列
	 */
	DirectX::XMMATRIX GetPerspectiveProjectionMatrix();

	/**
	 * @brief このカメラから平行投影プロジェクション行列を作成する
	 * @return プロジェクション行列
	 */
	DirectX::XMMATRIX GetOrthographicProjectionMatrix();

private:
	/// カメラ優先度
	int m_priority;

	/// 視野角
	float m_fovAngle;

	/// 奥行き最小値
	float m_nearZ;	

	/// 奥行き最大値
	float m_farZ;

	/// カメラサイズ (平行投影で使用)
	float m_cameraSize;

	/// 透視投影フラグ
	bool m_isPerspective;

	/// ビューポートの右上
	Vector2 m_viewportTopLeft;

	/// ビューポートのサイズ
	Vector2 m_viewportSize;

public:
	/**
	 * @brief メインカメラを取得する
	 * @param pScnen シーンへのポインタ
	 * @return メインカメラへのポインタ
	 */
	static Camera* GetMain(Scene* pScnen);

	/**
	 * @brief デフォルトビュー行列を取得する
	 * @return デフォルトビュー行列
	 */
	static DirectX::XMMATRIX GetDefaultViewMatrix();
};