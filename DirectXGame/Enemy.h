#pragma once
#include "KamataEngine.h"
#include "AABB.h"

class Mapchip;
class Player;

class Enemy {
private:

	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Camera* camera_ = nullptr;
	KamataEngine::Vector3 velocity_ = {};
	Mapchip* mapchipField_ = nullptr;

	static inline const float kSpeed = 0.05f;
	static inline const float kWidth = 2.0f;
	static inline const float kHeight = 2.0f;
	static inline const float kWalkMotionAngleStart = 0.5f;
	static inline const float kWalkMotionAngleEnd = 0.5f;
	static inline const float kWalkMotionTime = 3.0f;
	static inline const float amplitude = 1.0f;

	float walkTimer_ = 0.0f;
	float baseY_ = 0.0f;
	float waveY = 0.0f;

public:

	Enemy();
	~Enemy();

	void Initialize(KamataEngine::Camera* camera, const KamataEngine::Vector3& position);
	void Update();
	void Draw();
	KamataEngine::WorldTransform& GetWorldTransform() { return worldTransform_; }
	const KamataEngine::Vector3& GetVelocity() const { return velocity_; }
	void SetMapchipField(Mapchip* mapchipField) { mapchipField_ = mapchipField; }

	enum class MovePattern {
		CosWave,
		SinWave,
		Zigzag,
	};
	MovePattern movePattern_ = MovePattern::CosWave;

	KamataEngine::Vector3 GetWorldPosition();
	float GetEnemyWidth() const { return kWidth; }
	float GetEnemyHeight() const { return kHeight; }
	AABB GetAABB() const;
	void OnCollision(const Player* player);
};