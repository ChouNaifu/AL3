#include "DeathParticles.h"
#include <algorithm>

using namespace KamataEngine;
using namespace MathUtility;

void DeathParticles::Initialize(Model* model, Camera* camera, Player* player) { 
	for (WorldTransform& worldTransform : worldTransforms_) {
		worldTransform.Initialize();
		model_ = model;
		assert(camera);
		camera_ = camera;
		objectColor_.Initialize();
		color_ = {1.0f, 1.0f, 1.0f, 1.0f};
		worldTransform.translation_ = player->GetWorldPosition();
	}
}

void DeathParticles::Update() { 

	if (isFinished_) {
		return;
	}
	for (uint32_t i = 0; i < kMaxParticles; ++i) {
		Vector3 velocity = Vector3{kSpeed, 0.0f, 0.0f};
		float angle = kAngleUnit * i;
		Matrix4x4 matrixRotation = MakeRotateZMatrix(angle);
		velocity = Transform(velocity, matrixRotation);
		worldTransforms_[i].translation_ += velocity;
	}
	counter_ += 1.0f / 60.0f;
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		isFinished_ = true;
	}
	color_.w = std::clamp(kDuration - counter_, 0.0f, 1.0f);
	objectColor_.SetColor(color_);
	for (WorldTransform& worldTransform : worldTransforms_) {
		worldTransform.UpdateMatrix();		
	}
}

void DeathParticles::Draw() { 
	if (isFinished_) {
		return;
	}
	for (WorldTransform& worldTransform : worldTransforms_) {
		model_->Draw(worldTransform, *camera_, &objectColor_); 
	}
}
