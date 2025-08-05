#include "TitleScene.h"

using namespace KamataEngine;

void TitleScene::Initialize() {

	camera_ = new Camera();
	camera_->Initialize();

	modelTitle_ = Model::CreateFromOBJ("robot");
	worldTransform_.Initialize();
}

void TitleScene::Update() {
	camera_->UpdateMatrix();

	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		finished_ = true;
	}
}

void TitleScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 3Dモデルの描画前処理
	Model::PreDraw(dxCommon->GetCommandList());

	modelTitle_->Draw(worldTransform_, *camera_);

	// 3Dモデルの描画後処理
	Model::PostDraw();
}

TitleScene::~TitleScene() {
	delete modelTitle_;
	delete camera_;
}