#include "GameScene.h"

using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete sprite_; 
	sprite_ = nullptr;
	delete model_;
	model_ = nullptr;
	delete debugCamera_;
	debugCamera_ = nullptr;
}

void GameScene::Initialize() { 
	textureHandle_ = TextureManager::Load("uvChecker.png"); 

	soundDataHandle_ = Audio::GetInstance()->LoadWave("fanfare.wav");
	Audio::GetInstance()->PlayWave(soundDataHandle_);

	voiceHandle_ = Audio::GetInstance()->PlayWave(soundDataHandle_, true);

	sprite_ = Sprite::Create(textureHandle_, {100, 50});
	model_ = Model::Create();
	worldTransform_.Initialize();
	camera_.Initialize();

	PrimitiveDrawer::GetInstance()->SetCamera(&camera_);

	debugCamera_ = new DebugCamera(1280, 720);
}

void GameScene::Update() {
	Vector2 position = sprite_->GetPosition();
	position.x += 2.0f;
	position.y += 1.0f;
	sprite_->SetPosition(position);
	//sprite_->SetScale({2.0f, 2.0f});
	//sprite_->SetRotation(45.0f);
	//sprite_->SetColor({1.0f, 1.0f, 1.0f, 1.0f});

	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		Audio::GetInstance()->StopWave(voiceHandle_);
	}
#ifdef _DEBUG
	ImGui::Begin("Debug1");
	ImGui::Text("Chou nobu %d %d %d", 2050, 12, 32);
	ImGui::InputFloat3("InputFloat3", inputFloat3);
	ImGui::SliderFloat3("SliderFloat %f %f", &(position.x), 0, 1000);
	ImGui::ShowDemoWindow();
	ImGui::End();

	debugCamera_->Update();

#endif // DEBUG
}

void GameScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	// Drawing 2D Sprite
	Sprite::PreDraw(dxCommon->GetCommandList());
	//
	sprite_->Draw();
	//
	Sprite::PostDraw();

	// 3D Model Drawing
	Model::PreDraw(dxCommon->GetCommandList());
	//
	model_->Draw(worldTransform_, debugCamera_->GetCamera(), textureHandle_);
	//
	Model::PostDraw();
	PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, 0}, {0, 10, 0}, {1, 0, 0, 1});
}
