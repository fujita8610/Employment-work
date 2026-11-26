#include "TitleScene.h"

#include "DxLib.h"

#include "../Base/SceneManager.h" //sceneManager

// 次のシーン
//#include "../Load/LoadScene.h"


// 初期化
bool TitleScene::Init()
{
    return true;
}


// 更新
void TitleScene::Update()
{
    // マウス座標取得
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);

    // STARTボタン
    if (IsMouseInButton(mouseX, mouseY, 700, 400, 200, 70))
    {
        if (GetMouseInput() & MOUSE_INPUT_LEFT)
        {
           // SceneManager::GetInstance().ChangeScene(new LoadScene())
            return;
        }
    }

    // EXITボタン
    if (IsMouseInButton(mouseX, mouseY, 700, 510, 200, 70))
    {
        if (GetMouseInput() & MOUSE_INPUT_LEFT)
        {
            // ゲーム終了
            DxLib_End();
        }
    }
}


// 描画
void TitleScene::Draw()
{
    // タイトル
    DrawString(600, 180, "CARD ACTION KING",GetColor(255, 215, 100));

    // STARTボタン
    DrawBox(
        700, 400,
        900, 470,
        GetColor(70, 100, 150),
        TRUE
    );

    DrawString(
        760, 425,
        "START",
        GetColor(255, 255, 255)
    );

    // EXITボタン
    DrawBox(
        700, 510,
        900, 580,
        GetColor(100, 70, 70),
        TRUE
    );

    DrawString(
        770, 535,
        "EXIT",
        GetColor(255, 255, 255)
    );
}


// 解放
void TitleScene::Release()
{

}


// ボタン判定
bool TitleScene::IsMouseInButton(
    int mouseX,
    int mouseY,
    int x,
    int y,
    int width,
    int height
)
{
    return (
        mouseX >= x &&
        mouseX <= x + width &&
        mouseY >= y &&
        mouseY <= y + height
        );
}