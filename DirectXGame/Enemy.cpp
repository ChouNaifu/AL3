#include "Enemy.h"
#include "math/MathUtility.h"
#include <numbers>
#include "Mapchip.h"

using namespace KamataEngine;
using namespace MathUtility;

Enemy::Enemy() {}

Enemy::~Enemy() {}

void Enemy::Initialize(KamataEngine::Camera* camera, const KamataEngine::Vector3& position) {
	model_ = Model::CreateFromOBJ("skeleton", true);
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;	
	worldTransform_.rotation_.y = std::numbers::pi_v<float> * 1.5f;
	assert(camera);
	camera_ = camera;

	velocity_ = Vector3{-kSpeed, 0.0f, 0.0f};
	walkTimer_ = 0.0f;
}

void Enemy::Update() {

	worldTransform_.translation_ += velocity_;
	walkTimer_ += 1.0f / 60.0f;
	worldTransform_.translation_.y += std::sin(walkTimer_ * (2.0f * std::numbers::pi_v<float> / kWalkMotionTime)) * amplitude;
	worldTransform_.UpdateMatrix();	
}

void Enemy::Draw() {
	model_->Draw(worldTransform_, *camera_); 
}
