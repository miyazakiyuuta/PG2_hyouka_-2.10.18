#include <Novice.h>
#include "Scene.h"
#include "Player.h"
#include "PlayerBullet.h"
#include "Enemy.h"
#include "EnemyBullet.h"

Scene::Scene()
{
	scene_ = GAMETITLE;
	isSceneChange_ = false;
	darkenAlpha_ = 0;
	player_ = new Player();
	enemy_ = new Enemy();
}

Scene::~Scene()
{
	delete player_;
	delete enemy_;
}

void Scene::Update(char keys[], char preKeys[])
{
	switch (scene_)
	{
	case GAMETITLE:

		if (!isSceneChange_)
		{
			if (darkenAlpha_ > 0)
			{
				darkenAlpha_ -= 3;
			}
		}

		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE])
		{
			isSceneChange_ = true;
		}
		if (isSceneChange_)
		{
			darkenAlpha_ += 3;
			if (darkenAlpha_ >= 255)
			{
				darkenAlpha_ = 255;
				isSceneChange_ = false;
				player_ = new Player();
				enemy_ = new Enemy();
				scene_ = GAMEPLAY;
			}
		}

		break;
	case GAMEPLAY:
		if (!isSceneChange_)
		{
			if (darkenAlpha_ > 0)
			{
				darkenAlpha_ -= 3;
			}
		}
		if (player_->GetLife() <= 0 || !enemy_->GetIsAlive())
		{
			isSceneChange_ = true;
		}
		if (isSceneChange_)
		{
			darkenAlpha_ += 3;
			if (darkenAlpha_ >= 255)
			{
				darkenAlpha_ = 255;
				isSceneChange_ = false;
				if (player_->GetLife() <= 0)
				{
					scene_ = GAMEOVER;
				}
				if (!enemy_->GetIsAlive())
				{
					scene_ = GAMECLEAR;
				}
				delete player_;
				delete enemy_;
			}
		}

		break;
	case GAMEOVER:

		if (!isSceneChange_)
		{
			if (darkenAlpha_ > 0)
			{
				darkenAlpha_ -= 3;
			}
			else if (keys[DIK_SPACE] && !preKeys[DIK_SPACE])
			{
				isSceneChange_ = true;
			}
		}

		if (isSceneChange_)
		{
			darkenAlpha_ += 3;
			if (darkenAlpha_ >= 255)
			{
				darkenAlpha_ = 255;
				isSceneChange_ = false;
				scene_ = GAMETITLE;
			}
		}

		break;
	case GAMECLEAR:

		if (!isSceneChange_)
		{
			if (darkenAlpha_ > 0)
			{
				darkenAlpha_ -= 3;
			}
			else if (keys[DIK_SPACE] && !preKeys[DIK_SPACE])
			{
				isSceneChange_ = true;
			}
		}

		if (isSceneChange_)
		{
			darkenAlpha_ += 3;
			if (darkenAlpha_ >= 255)
			{
				darkenAlpha_ = 255;
				isSceneChange_ = false;
				scene_ = GAMETITLE;
			}
		}

		break;
	}

	if (scene_ == GAMEPLAY)
	{
		player_->Update(keys);
		enemy_->Update();
		if (enemy_->GetIsAttack()) //攻撃のフラグがtrue
		{
			for (int i = 0; i < enemy_->GetKMaxBullet(); i++)
			{
				if (!enemy_->GetBullet(i)->GetIsShot())
				{
					enemy_->SetBulletEnd(i, player_->GetPos());
				}
			}
		}

#pragma region 当たり判定
		//自機と敵
		if (enemy_->GetIsAlive() && player_->GetIsAlive())
		{
			player_->IsHit(enemy_->GetPos(), enemy_->GetRadius());
		}
		//自機の弾と敵
		if (enemy_->GetIsAlive())
		{
			for (int i = 0; i < player_->GetKMaxBullet(); i++)
			{
				if (player_->GetBullet(i)->IsHit(enemy_->GetPos(), enemy_->GetRadius()))
				{
					enemy_->SetHp(enemy_->GetHp() - 1); //enemy.hp -= 1;
				}
			}
		}
		//自機と敵の弾
		for (int i = 0; i < enemy_->GetKMaxBullet(); i++)
		{
			if (enemy_->GetBullet(i)->GetIsAlive())
			{
				if (player_->IsHit(enemy_->GetBullet(i)->GetPos(),
					enemy_->GetBullet(i)->GetRadius_()))
				{
					enemy_->SetBulletIsShot(i, false);
					enemy_->SetBulletIsAlive(i, false);
				}
			}
		}
#pragma endregion

	}

}

void Scene::Draw()
{
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLACK, kFillModeSolid);
	if (scene_ == GAMETITLE)
	{
		Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x800000ff, kFillModeSolid);
		Novice::ScreenPrintf(600, 300, "GAMETITLE");
	}
	if (scene_ == GAMEPLAY)
	{
		player_->Draw();
		enemy_->Draw();
	}
	if (scene_ == GAMEOVER)
	{
		Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x800080ff, kFillModeSolid);
		Novice::ScreenPrintf(600, 300, "GAMEOVER");
	}
	if (scene_ == GAMECLEAR)
	{
		Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0xaaaa00ff, kFillModeSolid);
		Novice::ScreenPrintf(600, 300, "GAMECLEAR");
	}
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0xffffff00 + darkenAlpha_, kFillModeSolid);
}
