#define NOMINMAX
#include "Player.h"
#include "math/MathUtility.h"
#include <numbers>
#include <iostream>
#include <algorithm>
#include "mapchip.h"

using namespace KamataEngine;
using namespace MathUtility;

Player::Player() {}

Player::~Player() {}

void Player::Initialize(Model* model, Camera* camera, const Vector3& position) { 
   assert(model); 
   model_ = model;
   worldTransform_.Initialize();
   worldTransform_.translation_ = position;
   worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
   assert(camera);
   camera_ = camera;
}

KamataEngine::Vector3 Player::VertexPosition(const KamataEngine::Vector3& center, Vertex p) {
	Vector3 offsetTable[kNumVertex] = {
	    {kWidth / 2.0f, -kHeight / 2.0f, 0.0f }, // RightBottom
	    {-kWidth / 2.0f, -kHeight / 2.0f, 0.0f }, // LeftBottom
	    {kWidth / 2.0f, kHeight / 2.0f, 0.0f }, // RightTop
	    {-kWidth / 2.0f, +kHeight / 2.0f, 0.0f }  // LeftTop
	};
	return center + offsetTable[static_cast<uint32_t>(p)];
}

void Player::CheckTop(CollisionMapInfo& info) {
	if (info.movement.y <= 0) {
		return;
	}
	std::array<Vector3, kNumVertex> positionsNew;
	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
		positionsNew[i] = VertexPosition(worldTransform_.translation_ + info.movement, static_cast<Vertex>(i));
	}
	MapchipType mapchipType[2];
	bool hit = false;
	Mapchip::IndexSet indexSet[2];
	indexSet[0] = mapchipField_->GetIndexSetByPosition(positionsNew[kLeftTop]);
	mapchipType[0] = mapchipField_->GetMapchipTypeByIndex(indexSet[0].xIndex, indexSet[0].yIndex);
	indexSet[1] = mapchipField_->GetIndexSetByPosition(positionsNew[kRightTop]);
	mapchipType[1] = mapchipField_->GetMapchipTypeByIndex(indexSet[1].xIndex, indexSet[1].yIndex);

	if (mapchipType[0] == MapchipType::Wall || mapchipType[1] == MapchipType::Wall) {
		hit = true;
	}

}

void Player::MapCollisionCheck(CollisionMapInfo& info) {
	CheckTop(info);
	//CheckBottom(info);
	//CheckRight(info);
	//CheckLeft(info);
}


void Player::Update() {
	////移動
	if (onGround_) {
		if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
			Vector3 acceleration = {};
			if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
				if (velocity_.x < 0.0f) {
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x = kAcceleration;
				if (lrdirection_ != LRDirection::kRight) {
					lrdirection_ = LRDirection::kRight;
					turnInitialRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = kTurnTime;
				}
			} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
				if (velocity_.x > 0.0f) {
					velocity_.x *= (1.0f - kAttenuation);
				}
				if (lrdirection_ != LRDirection::kLeft) {
					lrdirection_ = LRDirection::kLeft;
					turnInitialRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = kTurnTime;
				}
				acceleration.x = -kAcceleration;
			}
			velocity_ += acceleration;
			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
		} else {
			velocity_.x *= (1.0f - kAttenuation);
		}
		if (Input::GetInstance()->PushKey(DIK_SPACE) || Input::GetInstance()->PushKey(DIK_UP)) {
			velocity_ += Vector3{0.0f, kJumpAcceleration, 0.0f};
		}
	} else {
		velocity_ += Vector3{0.0f, -kGravityAcceleration, 0.0f};
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);
	}
	// 衝突判定
	CollisionMapInfo collisionMapInfo;
	collisionMapInfo.movement = velocity_;
	MapCollisionCheck(collisionMapInfo);

	bool landing = false;
	if (velocity_.y < 0.0f) {
		if (worldTransform_.translation_.y <= 2.0f) {
			landing = true;
		}
	} 
	if (onGround_) {
		if (velocity_.y > 0.0f) {
			onGround_ = false;
		} 
	} else {
		if (landing) {
			worldTransform_.translation_.y = 2.0f;
			velocity_.x *= (1.0f - kAttenuation);
			velocity_.y = 0.0f;
			onGround_ = true;
		}
	}
	// 回転
	if (turnTimer_ > 0.0f) {
		turnTimer_ -= 1 / 60.0f;
		float destinationRotationYTable[] = {
		    std::numbers::pi_v<float> / 2.0f,       // Right
		    std::numbers::pi_v<float> * 3.0f / 2.0f // Left
		};
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrdirection_)];
		float t = 1.0f - (turnTimer_ / kTurnTime); // t: 0→1
		float easeT = t * t * (3 - 2 * t);         // EaseInOut
		worldTransform_.rotation_.y = Lerp(turnInitialRotationY_, destinationRotationY, easeT);
	}

	worldTransform_.translation_ += velocity_;
	worldTransform_.UpdateMatrix();	
}

void Player::Draw() { 
	model_->Draw(worldTransform_, *camera_, textureHandle_); }


