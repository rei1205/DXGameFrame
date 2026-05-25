// Scene.h
#pragma once

/**
 * @brief シーンの基底クラス
 */
class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual void Init() {}
	virtual void Uninit() {}

	/**
	 * @brief シーンの更新を行う
	 */
	void Update();

	/**
	 * @brief シーンの描画を行う
	 */
	void Draw();
};
