#include "Skydome.h"
using namespace KamataEngine;

Skydome::Skydome() {}

Skydome::~Skydome() { 
	delete model_;
	model_ = nullptr;
}

void Skydome::Initialize(KamataEngine::Camera* camera) {
	camera_ = camera;
	model_ = Model::CreateFromOBJ("skydome", true);
	worldTransform_.Initialize();

}

void Skydome::Update() { 
	worldTransform_.TransferMatrix(); 
}

void Skydome::Draw() { 
	model_->Draw(worldTransform_, *camera_); 
}
