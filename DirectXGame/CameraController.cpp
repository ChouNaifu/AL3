#include "CameraController.h"
#include "Player.h"
#include "math/MathUtility.h"
#include <algorithm>


using namespace KamataEngine;
using namespace MathUtility;

CameraController::CameraController() {}

CameraController::~CameraController() {}

void CameraController::Initialize(Camera& camera) {
	camera_ = &camera;
	camera_->Initialize();
	camera_->farZ = 2000.0f;
	movableArea_ = {21.0f, 2036.0f, 11.0f, 11.0f};
}

void CameraController::Update() {
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();

	cameraTarget_ = targetWorldTransform.translation_ + targetOffset_ + target_->GetVelocity() * kVelocityBias;
	camera_->translation_.x = Lerp(camera_->translation_.x, cameraTarget_.x, kInterpolationRate);
	camera_->translation_.y = Lerp(camera_->translation_.y, cameraTarget_.y, 0.01f);

	camera_->translation_.x = std::clamp(camera_->translation_.x, 
		targetWorldTransform.translation_.x + margin.left, 
		targetWorldTransform.translation_.x + margin.right);
	camera_->translation_.y = std::clamp(camera_->translation_.y, 
		targetWorldTransform.translation_.y + margin.bottom, 
		targetWorldTransform.translation_.y + margin.top);
	camera_->translation_.x = std::clamp(camera_->translation_.x, movableArea_.left, movableArea_.right);
	camera_->translation_.y = std::clamp(camera_->translation_.y, movableArea_.bottom, movableArea_.top);
	camera_->UpdateMatrix();
}

void CameraController::Reset() {
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	camera_->translation_ = targetWorldTransform.translation_ + targetOffset_;
	camera_->translation_.y = 1000;
}
