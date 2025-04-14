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

	ImGuiManager* imguiManager = ImGuiManager::GetInstance();

	//GameScene Initialize
	GameScene* gameScene = new GameScene();
	gameScene->Initialize();
	
	//Main Loop
	while (true) {
		if (KamataEngine::Update()) {
			break;
		}
		imguiManager->Begin();
		gameScene->Update();
		imguiManager->End();

		//Draw initiate
		dxCommon->PreDraw();
		
		gameScene->Draw();

		AxisIndicator::GetInstance()->Draw();

		imguiManager->Draw();

		//Draw Cease
		dxCommon->PostDraw();
	}
	
	delete gameScene;
	gameScene = nullptr;

	KamataEngine::Finalize();
	return 0;
}
