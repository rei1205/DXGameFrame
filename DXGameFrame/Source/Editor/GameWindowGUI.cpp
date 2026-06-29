// GameWindowGUI.cpp
#include "GameWindowGUI.h"
#include "../DirectX/Manager/RenderTargetManager.h"
#include <ImGui/imgui.h>

GameWindowGUI::GameWindowGUI():
	EditorWindow("ゲームビュー")
{
}

void GameWindowGUI::OnGUI()
{
    // シーン描画結果を取得
    auto RTTexture = RenderTargetManager::GetRTVTexture(RTVType::SCENE);
    auto srv = RTTexture->GetSRV();
    if (srv == nullptr)
        return;

    // 描画サイズ計算
    ImVec2 avail = ImGui::GetContentRegionAvail();
    Texture::Size RTSize = RTTexture->GetSize();
    float aspect = (float)RTSize.x / (float)RTSize.y;
    ImVec2 imageSize;
    imageSize.x = avail.x;
    imageSize.y = avail.x / aspect;

    // 高さが収まらなければ高さ基準に変更
    if (imageSize.y > avail.y)
    {
        imageSize.y = avail.y;
        imageSize.x = imageSize.y * aspect;
    }

    // 描画位置計算
    ImVec2 cursor = ImGui::GetCursorPos();
    cursor.x += (avail.x - imageSize.x) * 0.5f;
    cursor.y += (avail.y - imageSize.y) * 0.5f;
    ImGui::SetCursorPos(cursor);

    ImGui::Image((ImTextureID)srv, imageSize);
}
