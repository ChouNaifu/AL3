#include "Collision.h"
#include "Player.h"
#include "Enemy.h"
#include "GameScene.h"
#include "math/MathUtility.h"
#include <numbers>
#include <algorithm>

using namespace KamataEngine;
using namespace MathUtility;

KamataEngine::Vector3 Collision::GetWorldPosition() {
	KamataEngine::Vector3 worldPos;
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;
	return worldPos;
}

AABB Collision::GetAABB(float width, float height) {
	Vector3 worldPos = GetWorldPosition();
	AABB aabb;
	aabb.min = worldPos + Vector3{-width / 2.0f, -height / 2.0f, -width / 2.0f};
	aabb.max = worldPos + Vector3{width / 2.0f, height / 2.0f, width / 2.0f};
	return aabb;
}

void Collision::CheckAllCollision() {
#pragma region CheckP2E
	// Player to Enemy collision check
	//SetPlayer(GameScene::GetInstance()->player_);
	//SetEnemies(GameScene::GetInstance()->player_);
	if (!player_ || !enemies_ || !enemies2_)
	return;
	AABB aabb1;
	AABB aabb2;
	AABB aabb3;
	aabb1 = player_->GetAABB();
	for (Enemy* enemy : *enemies_) {
		 aabb2 = enemy->GetAABB();
		if (AABBUtil::CheckAABBCollision(aabb1, aabb2)) {
			player_->OnCollision(enemy);
			enemy->OnCollision(player_);
		}		
	}
	for (Enemy* enemy : *enemies2_) {
		aabb3 = enemy->GetAABB();
		if (AABBUtil::CheckAABBCollision(aabb1, aabb3)) {
			player_->OnCollision(enemy);
			enemy->OnCollision(player_);
			player_->SetLife(0);
		}
	}

#pragma endregion CheckP2E
#pragma region CheckP2I

#pragma endregion CheckP2I
#pragma region CheckB2E

#pragma endregion CheckB2E
	
}
