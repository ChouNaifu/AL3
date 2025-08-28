#pragma once
#include "KamataEngine.h"
#include "AABB.h"
#include "Player.h"
#include "Enemy.h"

class Collision {

private:

	KamataEngine::WorldTransform worldTransform_;
	Player* player_ = nullptr;
	std::list<Enemy*>* enemies_;
	std::list<Enemy*>* enemies2_;


public:

	void SetPlayer(Player* player) { player_ = player; }
	void SetEnemies(std::list<Enemy*>* enemies) { enemies_ = enemies; }
	void SetEnemies2(std::list<Enemy*>* enemies) { enemies2_ = enemies; }
	KamataEngine::Vector3 GetWorldPosition();
	AABB GetAABB(float width, float height);
	void CheckAllCollision();

};

