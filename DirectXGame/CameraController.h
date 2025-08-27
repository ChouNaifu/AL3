#pragma once
#include "KamataEngine.h"

class Player;

struct Rect {
	float left = 0.0f;
	float right = 1.0f;
	float bottom = 0.0f;
	float top = 1.0f;
};

class CameraController {
public:
	CameraController();
	~CameraController();
	void Initialize(KamataEngine::Camera& camera);
	void Update();
	Player* target_ = nullptr;
	void SetTarget(Player* target) { target_ = target; }
	void Reset();
	void SetMovableArea(const Rect& area) { movableArea_ = area; }

private:
	KamataEngine::Camera* camera_;
	KamataEngine::Vector3 cameraTarget_;
	KamataEngine::Vector3 targetOffset_ = {0.0f, 0.0f, -30.0f};
	Rect movableArea_ = {0.0f, 100, 0.0f, 100.0f};
	static inline const float kInterpolationRate = 0.1f;
	static inline const float kVelocityBias = 10;
	static inline const Rect margin = {-10.0f, 10.0f, -10.0f, 10.0f};
	//KamataEngine::DebugCamera* debugCamera_ = nullptr;
	//bool isDebugCameraActive_ = false;
	//KamataEngine::Vector3 inputFloat3 = {0.0f, 0.0f, 0.0f};
	//KamataEngine::Vector3 cameraPosition = {0.0f, 10.0f, -10.0f};
	//KamataEngine::Vector3 cameraTarget = {0.0f, 0.0f, 0.0f};
};