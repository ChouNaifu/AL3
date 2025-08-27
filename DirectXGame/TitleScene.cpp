#include "TitleScene.h"

using namespace KamataEngine;

void TitleScene::Initialize() {

	camera_ = new Camera();
	camera_->Initialize();

	modelTitle_ = Model::CreateFromOBJ("title");
	worldTransform_.Initialize();

	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 1.0f);
}

void TitleScene::Update() {
	switch (phase_) {
	case TitleScene::Phase::kFadeIn:
		camera_->UpdateMatrix();
		fade_->Update();
		if (fade_->IsFinished()) {
			phase_ = TitleScene::Phase::kMain;
		}
		break;
	case TitleScene::Phase::kMain:
		camera_->UpdateMatrix();

		if (Input::GetInstance()->PushKey(DIK_SPACE)) {
			fade_->Start(Fade::Status::FadeOut, 1.0f);
			phase_ = TitleScene::Phase::kFadeOut;
		}
		break;
	case TitleScene::Phase::kFadeOut:
		camera_->UpdateMatrix();
		fade_->Update();

		if (fade_->IsFinished()) {
			finished_ = true;
		}   
		break;
	}
}

void TitleScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 3Dモデルの描画前処理
	Model::PreDraw(dxCommon->GetCommandList());

	modelTitle_->Draw(worldTransform_, *camera_);

	// 3Dモデルの描画後処理
	Model::PostDraw();

	fade_->Draw();
}

TitleScene::~TitleScene() {
	delete modelTitle_;
	modelTitle_ = nullptr;
	delete camera_;
	camera_ = nullptr;
	delete fade_;
	fade_ = nullptr;
}