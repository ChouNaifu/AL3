#include "Player.h"
#include "math/MathUtility.h"
#include "numbers"
using namespace KamataEngine;

Player::Player() {}

Player::~Player() {}

void Player::Initialize(Model* model, uint32_t textureHandle, Camera* camera) { 
   assert(model); 
   model_ = model;
   textureHandle_ = textureHandle;
   worldTransform_.Initialize();
   worldTransform_.translation_ = {2.0f, 2.0f, 0.0f};
   worldTransform_.rotation_.y = std::numbers::pi_v<float> * 1.5f;
   assert(camera);
   camera_ = camera;
}

void Player::Update() {
	worldTransform_.UpdateMatrix();
}

void Player::Draw() { 
	model_->Draw(worldTransform_, *camera_, textureHandle_);
}
