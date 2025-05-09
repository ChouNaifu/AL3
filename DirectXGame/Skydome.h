#pragma once
#include "KamataEngine.h"
#include "3d/WorldTransform.h"
#include "3d/Model.h"
#include "3d/Camera.h"

class Skydome {
public:
	Skydome();
	~Skydome();

	void Initialize(KamataEngine::Camera* camera);
	void Update();
	void Draw();

private:
	KamataEngine::WorldTransform worldTransform_ = {};
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Camera* camera_;
};