#include <Windows.h>
#include"KamataEngine.h"
#include "TitleScene.h"
#include"GameScene.h"

using namespace KamataEngine;

GameScene* gameScene = nullptr;
TitleScene* titleScene = nullptr;

enum class Scene {
	kUnknown = 0,
	kTitle,
	kGame,
};

Scene scene = Scene::kUnknown;

void ChangeScene() {
	switch (scene) {
	case Scene::kTitle:
		if (titleScene->IsFinished()) {
			scene = Scene::kGame;
			delete titleScene;
			titleScene = nullptr;

			gameScene = new GameScene;
			gameScene->Initialize();
		}
		break;
	case Scene::kGame:
		if (gameScene->IsFinished()) {
			scene = Scene::kTitle;
			delete gameScene;
			gameScene = nullptr;

			titleScene = new TitleScene();
			titleScene->Initialize();
		}
		break;
	}
}

void UpdateScene() {
	switch (scene) {
	case Scene::kTitle:
		titleScene->Update();
		break;
	case Scene::kGame:
		gameScene->Update();
		break;
	default:
		break;
	}
}

void DrawScene() {
	switch (scene) {
	case Scene::kTitle:
		titleScene->Draw();
		break;
	case Scene::kGame:
		gameScene->Draw();
		break;
	default:
		break;
	}
}

    // Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	//Engine Initialize
	KamataEngine::Initialize(L"GC2A_07_チョウ_ナイーフ");
	//DirectX Function Aquire
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	ImGuiManager* imguiManager = ImGuiManager::GetInstance();

	scene = Scene::kTitle;
	titleScene = new TitleScene();
	titleScene->Initialize();
	
	//Main Loop
	while (true) {
		if (KamataEngine::Update()) {
			break;
		}
		imguiManager->Begin();

		ChangeScene();
		UpdateScene();

		imguiManager->End();

		//Draw initiate
		dxCommon->PreDraw();
		
		DrawScene();

		AxisIndicator::GetInstance()->Draw();

		imguiManager->Draw();

		//Draw Cease
		dxCommon->PostDraw();
	}
	
	delete gameScene;
	gameScene = nullptr;
	delete titleScene;
	titleScene = nullptr;

	KamataEngine::Finalize();
	return 0;
}
