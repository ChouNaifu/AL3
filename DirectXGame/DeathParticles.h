#pragma once
#include "KamataEngine.h"
#include "Player.h"
#include <array>
#include <numbers>

class DeathParticles {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, Player* player);
	void Update();
	void Draw();

private:
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;
	static inline const uint32_t kMaxParticles = 8;
	std::array<KamataEngine::WorldTransform, kMaxParticles> worldTransforms_;
	static inline const float kDuration = 1.0f;
	static inline const float kSpeed = 0.2f;
	static inline const float kAngleUnit = 2.0f * std::numbers::pi_v<float> / kMaxParticles;
	bool isFinished_ = false;
	float counter_ = 0.0f;
	KamataEngine::ObjectColor objectColor_;
	KamataEngine::Vector4 color_;
};
