#pragma once

class Vector2
{
public:

	float x_;
	float y_;

	Vector2(float x = 0.0f, float y = 0.0f)
	{
		x_ = x;
		y_ = y;
	}

	/*Vector2型同士の演算*/

	Vector2 operator+(Vector2 obj)
	{
		Vector2 sc;
		sc.x_ = x_ + obj.x_;
		sc.y_ = y_ + obj.y_;
		return sc;
	}

	Vector2 operator-(Vector2 obj)
	{
		Vector2 sc;
		sc.x_ = x_ - obj.x_;
		sc.y_ = y_ - obj.y_;
		return sc;
	}
	
	Vector2 operator*(Vector2 obj)
	{
		Vector2 sc;
		sc.x_ = x_ * obj.x_;
		sc.y_ = y_ * obj.y_;
		return sc;
	}

	Vector2 operator/(Vector2 obj)
	{
		Vector2 sc;
		sc.x_ = x_ / obj.x_;
		sc.y_ = y_ / obj.y_;
		return sc;
	}

	/*Vector2型とfloat型の演算*/

	Vector2 operator*(float obj)
	{
		Vector2 sc;
		sc.x_ = x_ * obj;
		sc.y_ = y_ * obj;
		return sc;
	}

	Vector2 operator/(float obj)
	{
		Vector2 sc;
		sc.x_ = x_ / obj;
		sc.y_ = y_ / obj;
		return sc;
	}

};
