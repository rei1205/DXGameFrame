// RenderPass.h
#pragma once
#include "DirectXInclude.h"

/**
 * @brief 描画パスの基底クラス
 */
class RenderPass
{
public:
	virtual void Init() {}
	virtual void Uninit() {}
	virtual void Render() = 0;
};
