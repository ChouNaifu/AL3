#include <Windows.h>
#include"KamataEngine.h"
#include"GameScene.h"

using namespace KamataEngine;

    // Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	//Engine Initialize
	KamataEngine::Initialize(L"GC2A_07_チョウ_ナイーフ");
	//DirectX Function Aquire
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	//GameScene Initialize
	GameScene* gameScene = new GameScene();
	gameScene->Initialize();

	//Main Loop
	while (true) {
		if (KamataEngine::Update()) {
			break;
		}
		//Draw initiate
		dxCommon->PreDraw();
		//Draw Cease
		dxCommon->PostDraw();
	}
	
	delete gameScene;
	gameScene = nullptr;

	KamataEngine::Finalize();
	return 0;
}
