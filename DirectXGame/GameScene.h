#pragma once
#include "KamataEngine.h"

class GameScene {
public:
	GameScene();
	~GameScene();


	void Initialize();
	void Update();
	void Draw();

private:
	uint32_t textureHandle_ = 0;
	uint32_t soundDataHandle_ = 0;
	uint32_t voiceHandle_ = 0;
	float inputFloat3[3] = {0.0f, 0.0f, 0.0f};

	KamataEngine::Sprite* sprite_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Camera camera_;
	KamataEngine::DebugCamera* debugCamera_ = nullptr;
};
