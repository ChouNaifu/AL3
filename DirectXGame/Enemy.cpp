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

//Enemy::AABB Enemy::GetAABB() {
//	Vector3 worldPos = GetWorldPosition();
//	AABB aabb;
//	aabb.min = worldPos + Vector3{-kWidth / 2.0f, -kHeight / 2.0f, -kWidth / 2.0f};
//	aabb.max = worldPos + Vector3{kWidth / 2.0f, kHeight / 2.0f, kWidth / 2.0f};
//	return aabb;
//}

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

	worldTransform_.translation_ += velocity_;
	walkTimer_ += 1.0f / 60.0f;

	switch (movePattern_) {
	case MovePattern::CosWave:
		waveY = std::cos(walkTimer_ * (2.0f * std::numbers::pi_v<float> / kWalkMotionTime)) * amplitude;
		break;
	case MovePattern::SinWave:		
		waveY = std::sin(walkTimer_ * (2.0f * std::numbers::pi_v<float> / kWalkMotionTime)) * amplitude;
		break;
	case MovePattern::Zigzag:
		waveY = std::sin(walkTimer_ * (2.0f * std::numbers::pi_v<float> / 0.5f)) * 0.3f;
		break;
	}
	worldTransform_.translation_.y = baseY_ + waveY;
	worldTransform_.UpdateMatrix();	
}

void Enemy::Draw() {
	model_->Draw(worldTransform_, *camera_); 
}
