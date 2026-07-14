// GameWindowGUI.cpp
#include "GameWindowGUI.h"
#include "Editor.h"
#include "../System/ProjectData.h"
#include "../DirectX/Manager/RenderTargetManager.h"
#include <ImGui/imgui.h>

GameWindowGUI::GameWindowGUI() :
    EditorWindow("ゲームビュー"),
    m_screenSize{ 1280, 720 }
{
}

void GameWindowGUI::OnGUI()
{
    // 再生ボタン
    if (Editor::IsPlayMode())
    {
        if (ImGui::Button("Stop"))
        {
			Editor::StopPlayMode();
        }
    }
    else
    {
        if (ImGui::Button("Play"))
        {
			Editor::StartPlayMode();
        }
    }

    ImGui::SameLine();
    if (ImGui::InputInt2("画面サイズ", m_screenSize))
    {
        for (int i = 0; i < 2; ++i)
        {
            if (m_screenSize[i] < 1)
                m_screenSize[i] = 1;
        }

        RenderTargetManager::ReSize(m_screenSize[0], m_screenSize[1]);
    }
    ImGui::Separator();

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
