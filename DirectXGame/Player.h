#pragma once
#include "KamataEngine.h"
#include "AABB.h"

class Mapchip;
class Enemy;
class AABBUtil;

class Player {

private:
	enum Vertex {
		kRightBottom,
		kLeftBottom,
		kRightTop,
		kLeftTop,

		kNumVertex
	};
	enum LRDirection {
		kRight,
		kLeft,
	};

	LRDirection lrdirection_ = LRDirection::kRight;

	uint32_t textureHandle_ = 0;
	uint32_t soundDataHandle_ = 0;
	uint32_t voiceHandle_ = 0;
	KamataEngine::Vector3 velocity_ = {};
	static inline const float kAcceleration = 0.05f;
	static inline const float kAttenuation = 0.2f;
	static inline const float kLimitRunSpeed = 1.0f;
	static inline const float kGravityAcceleration = 0.1f;
	static inline const float kLimitFallSpeed = 3.0f;
	static inline const float kJumpAcceleration = 1.5f;
	static inline const float kWidth = 1.6f;
	static inline const float kHeight = 1.6f;
	static inline const float kBlank = 0.5f;
	static inline const float kAttenuationLanding = 0.1f;
	static inline const float kAttenuationWall = 0.5f;
	float turnInitialRotationY_ = 0.0f;
	float turnTimer_ = 0.0f;
	static inline const float kTurnTime = 0.3f;

	bool onGround_ = true;

	float inputFloat3[3] = {0.0f, 0.0f, 0.0f};
	KamataEngine::Sprite* sprite_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Camera* camera_;

	Mapchip* mapchipField_ = nullptr;

public:
	Player();
	~Player();

	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);
	void Update();
	void Draw();
	KamataEngine::WorldTransform& GetWorldTransform() { return worldTransform_; }
	const KamataEngine::Vector3& GetVelocity() const { return velocity_; }
	void SetMapchipField(Mapchip* mapchipField) { mapchipField_ = mapchipField; }

	struct CollisionMapInfo {
		bool top = false;
		bool ground = false;
		bool wall = false;
		KamataEngine::Vector3 movement;
	};
	
	KamataEngine::Vector3 VertexPosition(const KamataEngine::Vector3& center, Vertex p);

	void CheckTop(CollisionMapInfo& info);
	void CheckGround(CollisionMapInfo& info);
	void CheckRight(CollisionMapInfo& info);
	void CheckLeft(CollisionMapInfo& info);
	void MapCollisionCheck(CollisionMapInfo& info);
	void CollisionMove(const CollisionMapInfo& info);
	void TopCollided(const CollisionMapInfo& info);
	void GroundCollided(const CollisionMapInfo& info);
	void WallCollided(const CollisionMapInfo& info);

	KamataEngine::Vector3 GetWorldPosition();
	float GetPlayerHeight() const { return kHeight; }
	float GetPlayerWidth() const { return kWidth; }
	AABB GetAABB() const;
	void OnCollision(const Enemy* enemy);
};
