#include <Novice.h>
#include <math.h>
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Function.h"

Enemy::Enemy()
{
	pos_ = { 640.0f,100.0f };
	radius_ = 50.0f;
	hp_ = kMaxHp_;
	isAlive_ = true;

	bulletFalseCount_ = 0;
	isAttack_ = false;
	bulletT_ = 0.0f;
	bulletEasedT_ = 0.0f;
	for (int i = 0; i < kMaxBullet_; i++)
	{
		bullet_[i] = new EnemyBullet();
		bullet_[i]->SetStart(Vector2{ pos_.x_ +
			((i % 2 * -1.0f) + ((i + 1) % 2)) * ((i + (i + 1) % 2) * 100.0f) ,pos_.y_ });
		bullet_[i]->SetAuxiliary(bullet_[i]->GetStart() + Vector2{
			((i % 2 * -1.0f) + ((i + 1) % 2)) * ((i + (i + 1) % 2) * 50.0f),pos_.y_ + 100.0f });
	}
}

Enemy::~Enemy()
{
	for (int i = 0; i < kMaxBullet_; i++)
	{
		delete bullet_[i];
	}
}

void Enemy::Update()
{
	if (isAlive_)
	{
		if (!isAttack_)
		{
			if (hp_ != 500 && hp_ % 50 == 0)
			{
				isAttack_ = true;
				bulletT_ = 0.0f;
				for (int i = 0; i < kMaxBullet_; i++)
				{
					bullet_[i]->SetPos(pos_);//enemy座標に呼び出す
					bullet_[i]->SetIsAlive(true);
				}
			}
		}
		else //攻撃フラグがtrue
		{
			if (bulletT_ < 1.0f)//スタート位置への移動
			{
				bulletT_ += 1.0f / 90.0f;
				bulletEasedT_ = 1.0f - powf(1.0f - bulletT_, 3.0f);
			}
			for (int i = 0; i < kMaxBullet_; i++)
			{
				if (!bullet_[i]->GetIsShot())
				{
					bullet_[i]->SetPos(Lerp(pos_, bullet_[i]->GetStart(), bulletEasedT_));
					if (bulletT_ >= 1.0f)
					{
						bullet_[i]->SetIsShot(true);
					}
				}
				bullet_[i]->Update();
			}
			for (int i = 0; i < kMaxBullet_; i++) //isSoulAttackをfalseにする
			{
				if (bullet_[i]->GetIsShot())
				{
					if (!bullet_[i]->GetIsAlive())
					{
						bullet_[i]->SetIsShot(false);
						bulletFalseCount_++;
						if (bulletFalseCount_ >= kMaxBullet_)
						{
							isAttack_ = false;
						}
					}
					else
					{
						bulletFalseCount_ = 0;
						break;
					}
				}
			}
		}
		if (hp_ <= 0)
		{
			isAlive_ = false;
		}
	}
}

void Enemy::Draw()
{
	if (isAlive_)
	{

		for (int i = 0; i < kMaxBullet_; i++)
		{
			bullet_[i]->Draw();
			if (isAttack_) //照準
			{
				Novice::DrawEllipse
				(
					static_cast<int>(bullet_[i]->GetEnd().x_),
					static_cast<int>(bullet_[i]->GetEnd().y_),
					10, 10, 0.0f, RED, kFillModeWireFrame
				);
				Novice::DrawEllipse
				(
					static_cast<int>(bullet_[i]->GetEnd().x_),
					static_cast<int>(bullet_[i]->GetEnd().y_),
					15, 15, 0.0f, RED, kFillModeWireFrame
				);
				Novice::DrawLine
				(
					static_cast<int>(bullet_[i]->GetEnd().x_ - 20),
					static_cast<int>(bullet_[i]->GetEnd().y_),
					static_cast<int>(bullet_[i]->GetEnd().x_ + 20),
					static_cast<int>(bullet_[i]->GetEnd().y_),
					RED
				);
				Novice::DrawLine
				(
					static_cast<int>(bullet_[i]->GetEnd().x_),
					static_cast<int>(bullet_[i]->GetEnd().y_ - 20),
					static_cast<int>(bullet_[i]->GetEnd().x_),
					static_cast<int>(bullet_[i]->GetEnd().y_ + 20),
					RED
				);
			}
		}

		//hp
		Novice::DrawBox
		(
			static_cast<int>(pos_.x_ - radius_ / 2.0f - 1.0f),
			static_cast<int>(pos_.y_ - radius_ - 11.0f),
			static_cast<int>(radius_ + 2.0f),
			static_cast<int>(7.0f),
			0.0f, WHITE, kFillModeSolid
		);
		if (hp_ > 0)
		{
			Novice::DrawBox
			(
				static_cast<int>(pos_.x_ - radius_ / 2.0f),
				static_cast<int>(pos_.y_ - radius_ - 10.0f),
				static_cast<int>(radius_ * static_cast<float>(hp_) / static_cast<float>(kMaxHp_)),
				static_cast<int>(5.0f),
				0.0f, RED, kFillModeSolid
			);
		}

		//enemy
		Novice::DrawEllipse
		(
			static_cast<int>(pos_.x_),
			static_cast<int>(pos_.y_),
			static_cast<int>(radius_),
			static_cast<int>(radius_),
			0.0f, RED, kFillModeSolid
		);
	}
}

//アクセッサ(Set)

void Enemy::SetBulletEnd(int i, Vector2 end)
{
	bullet_[i]->SetEnd(end);
}

void Enemy::SetBulletIsShot(int i, int isShot)
{
	bullet_[i]->SetIsShot(isShot);
}

void Enemy::SetBulletIsAlive(int i, int isAlive)
{
	bullet_[i]->SetIsAlive(isAlive);
}
