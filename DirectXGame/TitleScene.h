#pragma once
#include "KamataEngine.h"

class TitleScene {
public:
	void Initialize();
	void Update();
	void Draw();
	~TitleScene();

	bool IsFinished() const { return finished_; }

private:

	bool finished_ = false;

	KamataEngine::Camera* camera_ = nullptr;
	KamataEngine::Model* modelTitle_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
};
