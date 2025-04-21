#include "Player.h"
using namespace KamataEngine;

Player::Player() {}

Player::~Player() {}

void Player::Initialize(Model* model, uint32_t textureHandle, Camera* camera) { 
   assert(model); 
   model_ = model;
   textureHandle_ = textureHandle;
   worldTransform_.Initialize();
   assert(camera);
   camera_ = camera;
}

void Player::Update() {
	worldTransform_.TransferMatrix(); 
}

void Player::Draw() { 
	model_->Draw(worldTransform_, *camera_, textureHandle_);
}
