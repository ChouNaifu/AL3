#pragma once
#include <vector>
#include "KamataEngine.h"
#include "Player.h"
#include "Skydome.h"
#include "Mapchip.h"
#include "CameraController.h"

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
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Camera camera_;
	KamataEngine::DebugCamera* debugCamera_ = nullptr;
};
