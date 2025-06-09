#pragma once
#include "KamataEngine.h"

class Player {
public:
	Player();
	~Player();

	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);
	void Update();
	void Draw();

private:

	enum LRDirection {
		kRight,
		kLeft,	
	};
	LRDirection lrdirection_ = LRDirection::kRight;

	uint32_t textureHandle_ = 0;
	uint32_t soundDataHandle_ = 0;
	uint32_t voiceHandle_ = 0;
	KamataEngine::Vector3 velocity_ = {};	
	static inline const float kAcceleration = 0.1f;
	static inline const float kAttenuation = 0.1f;
	static inline const float kLimitRunSpeed = 1.0f;
	static inline const float kGravityAcceleration = 0.1f;
	static inline const float kLimitFallSpeed = 3.0f;
	static inline const float kJumpAcceleration = 1.5f;
	float turnInitialRotationY_ = 0.0f;
	float turnTimer_ = 0.0f;
	static inline const float kTurnTime = 0.3f;

	bool onGround_ = true;

	float inputFloat3[3] = {0.0f, 0.0f, 0.0f};
	KamataEngine::Sprite* sprite_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Camera* camera_;
};
