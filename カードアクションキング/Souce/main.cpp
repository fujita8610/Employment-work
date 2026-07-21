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

    if (!game.Init())
        return -1;

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