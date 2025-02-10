#include "EnemyBullet.h"
#include <Novice.h>
#include <math.h>
#include "Function.h"

EnemyBullet::EnemyBullet()
{
	pos_ = {};
	start_ = {};
	auxiliary_ = {};
	end_ = {};
	radius_ = 15.0f;
	isAlive_ = false;
	isShot_ = false; 
	t_ = 0.0f;
	easedT_ = 0.0f;
}

void EnemyBullet::Update()
{
	if(isAlive_)
	{
		if (isShot_)
		{
			t_ += 1.0f / 60.0f;
			easedT_ = t_ * t_ * t_ * t_;
			pos_ = Bezier(start_, auxiliary_, end_, easedT_);
			if (t_ >= 1.0f)
			{
				t_ = 0.0f;
				isShot_ = false;
				isAlive_ = false;
			}
		}
	}
	if (!isAlive_ || !isShot_)
	{
		t_ = 0.0f;
	}
}

void EnemyBullet::Draw()
{
	if (isAlive_)
	{
		Novice::DrawEllipse
		(
			static_cast<int>(pos_.x_),
			static_cast<int>(pos_.y_),
			static_cast<int>(radius_),
			static_cast<int>(radius_),
			0.0f, 0x00bfffff, kFillModeSolid
		);
	}
}
