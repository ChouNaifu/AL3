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
	delete deathParticles_;
	deathParticles_ = nullptr;
	delete mapchipField_;
	mapchipField_ = nullptr;
	delete skydome_;
	skydome_ = nullptr;
	delete cameraController_;
	cameraController_ = nullptr;
	delete fade_;
	fade_ = nullptr;

	for (Enemy* enemy : enemies_) {
		delete enemy;
	}
	enemies_.clear();
	for (Enemy* enemy : enemies2_) {
		delete enemy;
	}
	enemies2_.clear();

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks2_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks2_.clear();
}



void GameScene::Initialize() { 

	
#pragma region Setup
	textureHandle_ = TextureManager::Load("healthbar.png"); 

	soundDataHandle_ = Audio::GetInstance()->LoadWave("fanfare.wav");

	voiceHandle_ = Audio::GetInstance()->PlayWave(soundDataHandle_, false);

	sprite_ = Sprite::Create(textureHandle_, {15, 20});
	model_ = Model::CreateFromOBJ("robot", true);
	blockModel_ = Model::CreateFromOBJ("cube", true);
	deathParticlesModel_ = Model::CreateFromOBJ("particle", true);
	
	worldTransform_.Initialize();
	camera_.Initialize();
	//camera_.farZ = 500;	

	PrimitiveDrawer::GetInstance()->SetCamera(&camera_);

	//debugCamera_ = new DebugCamera(1280, 720);

	//AxisIndicator::GetInstance()->SetVisible(true);
	//AxisIndicator::GetInstance()->SetTargetCamera(&debugCamera_->GetCamera());
#pragma endregion
	time_t currentTime = time(nullptr);
	srand(static_cast<unsigned int>(currentTime));

	mapchipField_ = new Mapchip;
	mapchipField_->LoadMapchipCsv("Resources/map/mapchip.csv");

	player_ = new Player();
	Vector3 playerPosition = mapchipField_->GetMapchipPositionByIndex(1, 9);
	player_->Initialize(model_, &camera_, playerPosition);
	player_->SetMapchipField(mapchipField_);

	phase_ = Phase::kFadeIn;
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 1.0f);
	
	for (int32_t i = 0; i < enemiesCount; ++i) {
		Enemy* newEnemy = new Enemy();
		Vector3 enemyPosition = mapchipField_->GetMapchipPositionByIndex(rand() % 50 + 20, rand() % 8+2);
		newEnemy->Initialize(&camera_, enemyPosition);
		enemies_.push_back(newEnemy);
		newEnemy->SetMapchipField(mapchipField_);
		if (i % 3 == 0) {
			newEnemy->movePattern_ = Enemy::MovePattern::CosWave;
		} else if (i % 3 == 1) {
			newEnemy->movePattern_ = Enemy::MovePattern::Zigzag;
		} else if (i % 3 == 2) {
			newEnemy->movePattern_ = Enemy::MovePattern::SinWave;
		}
	}
	for (int32_t i = 0; i < 9; ++i) {
		Enemy* newEnemy2 = new Enemy();
		Vector3 enemyPosition = mapchipField_->GetMapchipPositionByIndex(0, i + 1);
		newEnemy2->Initialize(&camera_, Vector3{enemyPosition.x - 20.0f, enemyPosition.y - 1.0f, enemyPosition.z});
		enemies2_.push_back(newEnemy2);
		newEnemy2->SetMapchipField(mapchipField_);
		newEnemy2->movePattern_ = Enemy::MovePattern::Back;
	}

	skydome_ = new Skydome();
	skydome_->Initialize(&camera_);

	cameraController_ = new CameraController();
	cameraController_->Initialize(camera_);
	cameraController_->SetTarget(player_);
	cameraController_->Reset();
	GenerateMap();

	collision_.SetPlayer(player_);
	collision_.SetEnemies(&enemies_);
	collision_.SetEnemies2(&enemies2_);
	
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
	worldTransformBlocks2_.resize(kNumBlockVirtical);
	for (uint32_t i = 0; i < kNumBlockVirtical; i++) {
		worldTransformBlocks2_[i].resize(kNumBlockHorizontal);
	}
	for (uint32_t y = 0; y < kNumBlockVirtical; y++) {
		for (uint32_t x = 0; x < kNumBlockHorizontal; x++) {
			if (mapchipField_->GetMapchipTypeByIndex(x, y) == MapchipType::Goal) {
				WorldTransform* worldTransform2 = new WorldTransform();
				worldTransform2->Initialize();
				worldTransformBlocks2_[y][x] = worldTransform2;
				worldTransformBlocks2_[y][x]->translation_ = mapchipField_->GetMapchipPositionByIndex(x, y);
			}
		}
	}
}

void GameScene::ChangePhase() {
	switch (phase_) {
	case GameScene::Phase::kFadeIn:
		//
		break;
	case GameScene::Phase::kPlay:
		if (player_->IsDead()) {
			phase_ = Phase::kDeath;
			const Vector3& deathParticlePosition = player_->GetWorldPosition();
			deathParticles_ = new DeathParticles;
			deathParticles_->Initialize(deathParticlesModel_, &camera_, deathParticlePosition);
		}
		break;
	case GameScene::Phase::kDeath:
		if (deathParticles_ && deathParticles_->IsFinished()) {
			finished_ = true;
		}
		break;
	case GameScene::Phase::kFadeOut:
		//
		break;
	}
}



void GameScene::Update() {
	ChangePhase();
	switch (phase_) {
	case Phase::kFadeIn:
	
		cameraController_->Update();
		fade_->Update();
		if (fade_->IsFinished()) {
			phase_ = Phase::kPlay;
		}
		break;
	case Phase::kPlay:

		player_->Update();

		cameraController_->Update();
		collision_.CheckAllCollision();
		break;
	case Phase::kDeath:

		if (deathParticles_) {
			deathParticles_->Update();
		}
		if (deathParticles_ && deathParticles_->IsFinished()) {
			phase_ = Phase::kFadeOut;
			fade_->Start(Fade::Status::FadeOut, 1.0f);
		}
		break;
	case Phase::kFadeOut:


		if (deathParticles_) {
			deathParticles_->Update();
		}
		cameraController_->Update();
		fade_->Update();
		if (fade_->IsFinished()) {
			finished_ = true;
		}
		break;
	}
#pragma region Update
	//Vector2 position = sprite_->GetPosition();
	//position.x += 2.0f;
	//position.y += 1.0f;
	//sprite_->SetPosition(position);
	sprite_->SetSize({256.0f * (static_cast<float>(player_->GetLife())/100), 44.0f});
	//sprite_->SetRotation(45.0f);
	//sprite_->SetColor({1.0f, 1.0f, 1.0f, 1.0f});


	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			worldTransformBlock->UpdateMatrix();
		}
	}
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks2_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			worldTransformBlock->UpdateMatrix();
		}
	}

#ifdef _DEBUG
	//ImGui::Begin("Debug1");
	//ImGui::Text("Chou nobu %f", player_->GetAABB().max.x);
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
		
	int32_t targetEnemyCount = 6 + static_cast<int32_t>(player_->GetWorldPosition().x / 200.0f);
	while (enemies_.size() < targetEnemyCount) {
		Enemy* newEnemy = new Enemy();
		Vector3 enemyPosition = mapchipField_->GetMapchipPositionByIndex(rand() % 10 + 20, rand() % 8 + 2);
		newEnemy->Initialize(&camera_, Vector3{enemyPosition.x + player_->GetWorldPosition().x + 30.0f, enemyPosition.y, enemyPosition.z});			enemies_.push_back(newEnemy);
		newEnemy->SetMapchipField(mapchipField_);
		newEnemy->movePattern_ = Enemy::MovePattern::CosWave;
	}
	for (Enemy* enemy : enemies_) {
		enemy->Update();
		if (enemy->GetWorldPosition().x < player_->GetWorldPosition().x - 30.0f) {
			Vector3 enemyPosition = mapchipField_->GetMapchipPositionByIndex(rand() % 50 + 20, rand() % 8 + 2);
			enemy->Respawn(Vector3{enemyPosition.x + player_->GetWorldPosition().x, enemyPosition.y, enemyPosition.z});
		}
	}
	for (Enemy* enemy : enemies2_) {
		enemy->Update();
	}

	skydome_->Update();	
	if (player_->GetWorldPosition().x - skydome_->GetPositionX() > 300.0f) {
		skydome_->SetPosition(Vector3{player_->GetWorldPosition().x + 100.0f, 0.0f, 0.0f});
	}
}
void GameScene::Draw() {

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	// Drawing 2D Sprite
	Sprite::PreDraw(dxCommon->GetCommandList());
	//
	if (!deathParticles_) {
		sprite_->Draw();
	}
	//
	Sprite::PostDraw();

	// 3D Model Drawing
	Model::PreDraw(dxCommon->GetCommandList());
	//
	//model_->Draw(worldTransform_, camera_, textureHandle_);
	//model_->Draw(worldTransform_, debugCamera_->GetCamera(), textureHandle_);
	player_->Draw();
	skydome_->Draw();
	for (Enemy* enemy : enemies_) {
		enemy->Draw();
	}
	for (Enemy* enemy : enemies2_) {
		enemy->Draw();
	}
	if (deathParticles_) {
		deathParticles_->Draw();
	}
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			blockModel_->Draw(*worldTransformBlock, camera_);
		}
	}
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks2_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			model_->Draw(*worldTransformBlock, camera_);
		}
	}
	//
	Model::PostDraw();
	if (phase_ == Phase::kFadeIn || phase_ == Phase::kFadeOut) {
		if (fade_) {
			fade_->Draw();
		}
	}
	PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, 0}, {0, 10, 0}, {1, 0, 0, 1});

	
}



