#include "GameScene.h"

using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete sprite_; 
	sprite_ = nullptr;
	delete model_;
	model_ = nullptr;
	delete debugCamera_;
	debugCamera_ = nullptr;
	delete player_;
	player_ = nullptr;
	delete blockModel_;
	blockModel_ = nullptr;
	delete mapchipField_;
	mapchipField_ = nullptr;
	delete skydome_;
	skydome_ = nullptr;

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();
}



void GameScene::Initialize() { 

	
#pragma region Setup
	textureHandle_ = TextureManager::Load("uvChecker.png"); 

	soundDataHandle_ = Audio::GetInstance()->LoadWave("fanfare.wav");
	Audio::GetInstance()->PlayWave(soundDataHandle_);

	voiceHandle_ = Audio::GetInstance()->PlayWave(soundDataHandle_, true);

	sprite_ = Sprite::Create(textureHandle_, {100, 50});
	model_ = Model::CreateFromOBJ("robot", true);
	blockModel_ = Model::CreateFromOBJ("cube", true);
	
	worldTransform_.Initialize();
	camera_.Initialize();
	//camera_.farZ = 500;

	PrimitiveDrawer::GetInstance()->SetCamera(&camera_);

	debugCamera_ = new DebugCamera(1280, 720);

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetCamera(&debugCamera_->GetCamera());
#pragma endregion
	player_ = new Player();
	Vector3 playerPosition = mapchipField_->GetMapchipPositionByIndex(1, 9);
	player_->Initialize(model_, &camera_, playerPosition);

	skydome_ = new Skydome();
	skydome_->Initialize(&camera_);

	mapchipField_ = new Mapchip;
	mapchipField_->LoadMapchipCsv("Resources/map/mapchip.csv");

	GenerateMap();
}

void GameScene::GenerateMap() {
	const uint32_t kNumBlockHorizontal = mapchipField_->GetNumBlockHorizontal();
	const uint32_t kNumBlockVirtical = mapchipField_->GetNumBlockVertical();
	// const float kBlockWidth = 2.0f;
	// const float kBlockHeight = 2.0f;
	worldTransformBlocks_.resize(kNumBlockVirtical);
	for (uint32_t i = 0; i < kNumBlockVirtical; i++) {
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	}
	for (uint32_t y = 0; y < kNumBlockVirtical; y++) {
		for (uint32_t x = 0; x < kNumBlockHorizontal; x++) {
			if (mapchipField_->GetMapchipTypeByIndex(x, y) == MapchipType::Wall) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[y][x] = worldTransform;
				worldTransformBlocks_[y][x]->translation_ = mapchipField_->GetMapchipPositionByIndex(x, y);
			}
		}
	}
}

void GameScene::Update() {
#pragma region Update
	Vector2 position = sprite_->GetPosition();
	//position.x += 2.0f;
	//position.y += 1.0f;
	//sprite_->SetPosition(position);
	//sprite_->SetScale({2.0f, 2.0f});
	//sprite_->SetRotation(45.0f);
	//sprite_->SetColor({1.0f, 1.0f, 1.0f, 1.0f});

	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		Audio::GetInstance()->StopWave(voiceHandle_);
	}

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			worldTransformBlock->UpdateMatrix();
		}
	}

#ifdef _DEBUG
	//ImGui::Begin("Debug1");
	//ImGui::Text("Chou nobu %d %d %d", 2050, 12, 32);
	//ImGui::InputFloat3("InputFloat3", inputFloat3);
	//ImGui::SliderFloat3("SliderFloat %f %f", &(position.x), 0, 1000);
	//ImGui::ShowDemoWindow();
	//ImGui::End();
	if (Input::GetInstance()->TriggerKey(DIK_F1)) {
		isDebugCameraActive_ ^= true;
	}
	if (isDebugCameraActive_) {
		debugCamera_->Update();
		camera_.matView = debugCamera_->GetCamera().matView;
		camera_.matProjection = debugCamera_->GetCamera().matProjection;
		camera_.TransferMatrix();
	} else {
		camera_.UpdateMatrix();
	}

#endif // DEBUG
#pragma endregion Update
#pragma region Player
	player_->Update();
#pragma endregion Player
	skydome_->Update();
}
void GameScene::Draw() {

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	// Drawing 2D Sprite
	Sprite::PreDraw(dxCommon->GetCommandList());
	//
	//sprite_->Draw();
	//
	Sprite::PostDraw();

	// 3D Model Drawing
	Model::PreDraw(dxCommon->GetCommandList());
	//
	//model_->Draw(worldTransform_, camera_, textureHandle_);
	//model_->Draw(worldTransform_, debugCamera_->GetCamera(), textureHandle_);
	player_->Draw();
	skydome_->Draw();

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			blockModel_->Draw(*worldTransformBlock, debugCamera_->GetCamera());
		}
	}
	//
	Model::PostDraw();
	PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, 0}, {0, 10, 0}, {1, 0, 0, 1});

	
}



