#include "DxLib.h"

//ゲームマネージャー
#include "Manager/GameManager/GameManager.h"


int WINAPI WinMain( HINSTANCE,HINSTANCE,LPSTR,int)
{
	// ウィンドウモードに変更
    ChangeWindowMode(TRUE);

	// 画面サイズを設定
    SetGraphMode(1600, 900, 32);

	// DxLibの初期化
    if (DxLib_Init() == -1)
        return -1;

	// 裏画面を描画先に設定
    SetDrawScreen(DX_SCREEN_BACK);

	// ゲームマネージャーのインスタンスを取得
    GameManager& game = GameManager::GetInstance();

	// ゲームマネージャーの初期化
    if (!game.Init())
    {
        // 初期化失敗時は画面を表示したままにする
        while (ProcessMessage() == 0)
        {
            ClearDrawScreen();

            DrawString(
                40,
                40,
                "GameManager Init Failed!",
                GetColor(255, 0, 0));

            DrawString(
                40,
                80,
                "Card Load Failed!",
                GetColor(255, 0, 0));

            ScreenFlip();
        }

        DxLib_End();

        return -1;
    }

	// メインループ
    while (ProcessMessage() == 0)
    {
        ClearDrawScreen();

        game.Update();

        game.Draw();

        ScreenFlip();
    }

    game.Release();

    DxLib_End();

    return 0;
}