#include "GameScene.h"
using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete sprite_; 
}

void GameScene::Initialize() { 
	textureHandle_ = TextureManager::Load("uvChecker.png"); 
	sprite_ = Sprite::Create(textureHandle_, {100, 50});
}

void GameScene::Update() {}

void GameScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	Sprite::PreDraw(dxCommon->GetCommandList());
	sprite_->Draw();
	Sprite::PostDraw();
}
