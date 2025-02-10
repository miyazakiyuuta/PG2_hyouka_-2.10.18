#include <Novice.h>
#include "PlayerBullet.h"
#include "Function.h"


PlayerBullet::PlayerBullet()
{
	pos_ = {};
	radius_ = 5.0f;
	speed_ = 10.0f;
	isShot_ = false;
}

void PlayerBullet::Update()
{
	if (isShot_)
	{
		pos_.y_ -= speed_;
		if (pos_.y_ + radius_ <= 0.0f)
		{
			isShot_ = false;
		}
	}
}

void PlayerBullet::Draw()
{
	if (isShot_)
	{
		Novice::DrawEllipse
		(
			static_cast<int>(pos_.x_),
			static_cast<int>(pos_.y_),
			static_cast<int>(radius_),
			static_cast<int>(radius_),
			0.0f, 0xffff00ff, kFillModeSolid
		);
		Novice::DrawBox
		(
			static_cast<int>(pos_.x_ - radius_),
			static_cast<int>(pos_.y_),
			static_cast<int>(radius_ * 2.0f),
			static_cast<int>(radius_ * 1.5f),
			0.0f, 0xffff00ff, kFillModeSolid
		);
	}
}

int PlayerBullet::IsHit(Vector2 pos, float radius)
{
	if (isShot_)
	{
		if (IsCircleHit(pos_, radius_, pos, radius))
		{
			isShot_ = false;
			return true;
		}
	}
	return false;
}
