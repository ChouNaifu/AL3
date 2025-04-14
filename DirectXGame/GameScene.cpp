#include "GameScene.h"
using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete sprite_; 
	sprite_ = nullptr;
}

void GameScene::Initialize() { 
	textureHandle_ = TextureManager::Load("uvChecker.png"); 
	sprite_ = Sprite::Create(textureHandle_, {100, 50});
}

void GameScene::Update() {
	Vector2 position = sprite_->GetPosition();
	position.x += 2.0f;
	position.y += 1.0f;
	sprite_->SetPosition(position);
	//sprite_->SetScale({2.0f, 2.0f});
	//sprite_->SetRotation(45.0f);
	//sprite_->SetColor({1.0f, 1.0f, 1.0f, 1.0f});
}

void GameScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	Sprite::PreDraw(dxCommon->GetCommandList());
	sprite_->Draw();
	Sprite::PostDraw();
}
