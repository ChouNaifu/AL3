#include "Enemy.h"
#include "math/MathUtility.h"
#include <numbers>
#include "Mapchip.h"

using namespace KamataEngine;
using namespace MathUtility;

Enemy::Enemy() {}

Enemy::~Enemy() {}

KamataEngine::Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;
	return worldPos;
}

AABB Enemy::GetAABB() const { 
	return AABBUtil::GetAABB(worldTransform_, GetEnemyWidth(), GetEnemyHeight()); 
}

void Enemy::OnCollision(const Player* player) { 
	(void)player; 
}

void Enemy::Initialize(KamataEngine::Camera* camera, const KamataEngine::Vector3& position) {
	model_ = Model::CreateFromOBJ("skeleton", true);
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;	
	worldTransform_.rotation_.y = std::numbers::pi_v<float> * 1.5f;
	assert(camera);
	camera_ = camera;

	velocity_ = Vector3{-kSpeed, 0.0f, 0.0f};
	walkTimer_ = 0.0f;
	baseY_ = worldTransform_.translation_.y + 1.0f;
}

void Enemy::Update() {

	walkTimer_ += 1.0f / 60.0f;

	switch (movePattern_) {
	case MovePattern::CosWave:
		worldTransform_.translation_ += velocity_;
		waveY = std::cos(walkTimer_ * (2.0f * std::numbers::pi_v<float> / kWalkMotionTime)) * amplitude;
		break;
	case MovePattern::SinWave:		
		worldTransform_.translation_ += velocity_;
		waveY = std::sin(walkTimer_ * (2.0f * std::numbers::pi_v<float> / kWalkMotionTime)) * amplitude;
		break;
	case MovePattern::Zigzag:
		worldTransform_.translation_ += velocity_;
		waveY = std::sin(walkTimer_ * (2.0f * std::numbers::pi_v<float> / 0.5f)) * 0.3f;
		break;
	case MovePattern::Back:
		worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
		worldTransform_.translation_ += Vector3{0.2f, 0.0f, 0.0f};
		waveY = std::sin(walkTimer_ * (2.0f * std::numbers::pi_v<float> / 0.5f)) * 0.3f;
		break;
	}
	worldTransform_.translation_.y = baseY_ + waveY;
	worldTransform_.UpdateMatrix();	
}

void Enemy::Draw() {
	model_->Draw(worldTransform_, *camera_); 
}

void Enemy::Respawn(KamataEngine::Vector3 position) { 
	worldTransform_.translation_ = position;
}
