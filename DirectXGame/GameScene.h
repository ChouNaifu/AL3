#pragma once
#include <vector>
#include "KamataEngine.h"
#include "Player.h"
#include "Skydome.h"
#include "Mapchip.h"
#include "CameraController.h"
#include "Enemy.h"
#include "DeathParticles.h"
#include "Collision.h"
#include "Fade.h"

class GameScene {
public:
	GameScene();
	~GameScene();

	void Initialize();
	void Update();
	void Draw();
	void GenerateMap();
	Player* player_ = nullptr;
	Skydome* skydome_ = nullptr;
	Mapchip* mapchipField_ = nullptr;
	CameraController* cameraController_ = nullptr;
	std::list<Enemy*> enemies_;
	static inline const int enemiesCount = 10;
	DeathParticles* deathParticles_ = nullptr;
	Collision collision_;
	enum class Phase {
		kFadeIn,
		kPlay,
		kDeath,
		kFadeOut,
	};
	Phase phase_;
	bool IsFinished() const { return finished_; }
	Fade* fade_ = nullptr;

private:
	uint32_t textureHandle_ = 0u;
	uint32_t soundDataHandle_ = 0;
	uint32_t voiceHandle_ = 0;
	float inputFloat3[3] = {0.0f, 0.0f, 0.0f};
	bool isDebugCameraActive_ = false;
	std::vector < std::vector < KamataEngine::WorldTransform* >> worldTransformBlocks_;

	KamataEngine::Sprite* sprite_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Model* blockModel_ = nullptr;
	KamataEngine::Model* deathParticlesModel_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Camera camera_;
	KamataEngine::DebugCamera* debugCamera_ = nullptr;
	void ChangePhase();
	bool finished_ = false;

};
