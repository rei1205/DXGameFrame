// ObjectSerializer.h
#pragma once
#include "Scene.h"

/**
 * @brief オブジェクトのシリアライズ・デシリアライズを行う
 */
class ObjectSerializer
{
public:
	static std::unique_ptr<Scene> DeserializeScene();

	static GameObject* DeserializeGameObject();

private:

};
