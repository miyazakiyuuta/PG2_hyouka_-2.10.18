#include <Novice.h>
#include "Player.h"
#include "PlayerBullet.h"
#include "Function.h"

Player::Player()
{
	pos_ = { 640.0f,650.0f };
	radius_ = 25.0f;
	move_ = {};
	speed_ = 5.0f;
	life_ = kMaxLife_;
	isAlive_ = true;
	invincibleTimer_ = 0;

	bulletCoolTimer_ = kBulletCoolTime_;
	for (int i = 0; i < kMaxBullet_; i++)
	{
		bullet_[i] = new PlayerBullet();
	}
}

Player::~Player()
{
	for (int i = 0; i < kMaxBullet_; i++)
	{
		delete bullet_[i];
	}
}

void Player::Update(char keys[])
{

	//自機の移動処理
	move_ = {};
	if (keys[DIK_W])
	{
		move_.y_--;
	}
	if (keys[DIK_S])
	{
		move_.y_++;
	}
	if (keys[DIK_A])
	{
		move_.x_--;
	}
	if (keys[DIK_D])
	{
		move_.x_++;
	}
	if (Length(move_) != 0.0f)
	{
		move_ = move_ / Length(move_);
	}
	pos_ = pos_ + move_ * speed_;

	if (invincibleTimer_ > 0)
	{
		invincibleTimer_--;
	}

	//弾の発射
	bulletCoolTimer_--;
	if (bulletCoolTimer_ <= 0)
	{
		if (keys[DIK_SPACE])
		{
			for (int i = 0; i < kMaxBullet_; i++)
			{
				if (!bullet_[i]->GetIsShot())
				{
					bulletCoolTimer_ = kBulletCoolTime_;
					bullet_[i]->SetPos(pos_);
					bullet_[i]->SetIsShot(true);
					break;
				}
			}
		}
	}

	//弾の更新処理
	for (int i = 0; i < kMaxBullet_; i++)
	{
		bullet_[i]->Update();
	}

}

void Player::Draw()
{
	//自機の弾
	for (int i = 0; i < kMaxBullet_; i++)
	{
		bullet_[i]->Draw();
	}

	//自機
	if (isAlive_ && invincibleTimer_ % 2 == 0)
	{
		Novice::DrawEllipse
		(
			static_cast<int>(pos_.x_),
			static_cast<int>(pos_.y_),
			static_cast<int>(radius_),
			static_cast<int>(radius_),
			0.0f, WHITE, kFillModeSolid
		);
	}

	//自機のライフの描画
	for (int i = 0; i < kMaxLife_; i++)
	{
		if (i < life_)
		{
			Novice::DrawEllipse
			(
				static_cast<int>(35.0f + 60.0f * i),
				720 - 35,
				25, 25, 0.0f, 0xff00ffff, kFillModeSolid
			);
		}
	}
}

int Player::IsHit(Vector2 pos, float radius)
{
	if (invincibleTimer_ <= 0)
	{
		if (IsCircleHit(pos_, radius_, pos, radius))
		{
			life_--;
			invincibleTimer_ = kInvincibleTime_;
			return true;
		}
	}
	return false;
}
