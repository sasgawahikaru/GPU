#include "GameScene.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	delete spriteBG;
	delete ParticleMan;

	//delete sprite1;
	//delete sprite2;
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	// デバッグテキスト用テクスチャ読み込み
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	// テクスチャ読み込み
	Sprite::LoadTexture(1, L"Resources/background.png");

	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	// 3Dオブジェクト生成
	ParticleMan = ParticleManager::Create();
	//ParticleMan->Update();


	//Sprite::LoadTexture(2, L"Resources/texture.png");

//	sprite1 = Sprite::Create(2, { 0,0 });
//	sprite2 = Sprite::Create(2, { 500,500 }, { 1,0,0,1 }, { 0,0 }, false, true);
}

void GameScene::Update()
{
	// オブジェクト移動
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{
		// 現在の座標を取得
//		XMFLOAT3 position = ParticleMan->GetPosition();

		// 移動後の座標を計算
		//if (input->PushKey(DIK_UP)) { position.y += 1.0f; }
		//else if (input->PushKey(DIK_DOWN)) { position.y -= 1.0f; }
		//if (input->PushKey(DIK_RIGHT)) { position.x += 1.0f; }
		//else if (input->PushKey(DIK_LEFT)) { position.x -= 1.0f; }

		//// 座標の変更を反映
		//ParticleMan->SetPosition(position);
	}

	// カメラ移動
	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
	{
		if (input->PushKey(DIK_W)) { ParticleManager::CameraMoveVector({ 0.0f,+1.0f,0.0f }); }
		else if (input->PushKey(DIK_S)) { ParticleManager::CameraMoveVector({ 0.0f,-1.0f,0.0f }); }
		if (input->PushKey(DIK_D)) { ParticleManager::CameraMoveVector({ +1.0f,0.0f,0.0f }); }
		else if (input->PushKey(DIK_A)) { ParticleManager::CameraMoveVector({ -1.0f,0.0f,0.0f }); }
	}
	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
	{
		if (input->PushKey(DIK_W)) { ParticleManager::CameraMoveEyeVector({ 0.0f,+2.0f,0.0f }); }
		else if (input->PushKey(DIK_S)) { ParticleManager::CameraMoveEyeVector({ 0.0f,-2.0f,0.0f }); }
		if (input->PushKey(DIK_D)) { ParticleManager::CameraMoveEyeVector({ +2.0f,0.0f,0.0f }); }
		else if (input->PushKey(DIK_A)) { ParticleManager::CameraMoveEyeVector({ -2.0f,0.0f,0.0f }); }
	}
	//if (input->PushKey(DIK_SPACE)) {
	//	XMFLOAT2 position = sprite1->GetPosition();
	//	position.x += 1.0f;
	//	sprite1->SetPosition(position);
	//}
	for (int i = 0; i < 10; i++) {
		const float md_pos = 10.0f;
		XMFLOAT3 pos{};
		pos.x = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.y = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.z = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;

		const float md_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;

		XMFLOAT3 acc{};
		const float md_acc = 0.001f;
		acc.y =- (float)rand() / RAND_MAX * md_acc;

		ParticleMan->Add(60, pos, vel, acc, 1.0f, 0.0f);
	}

	ParticleMan->Update();
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	//spriteBG->Draw();

	//sprite1->Draw();
	//sprite2->Draw();
	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	ParticleManager::PreDraw(cmdList);

	// 3Dオブクジェクトの描画
	ParticleMan->Draw();

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	ParticleManager::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText.DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}
