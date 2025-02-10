#include <math.h>
#include "Function.h"

float Length(const Vector2& v)
{
	return sqrtf(v.x_ * v.x_ + v.y_ * v.y_);
}

int IsCircleHit(Vector2 posA, float radiusA, Vector2 posB, float radiusB)
{
	Vector2 distance = posA - posB;
	if (Length(distance) < radiusA + radiusB)
	{
		return true;
	}
	return false;
}

Vector2 Lerp(const Vector2& p0, const Vector2& p1, float t)
{
	Vector2 result;
	result.x_ = (1.0f - t) * p0.x_ + t * p1.x_;
	result.y_ = (1.0f - t) * p0.y_ + t * p1.y_;
	return result;
}

//p0 start p2 end
Vector2 Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, float t)
{
	Vector2 p0p1 = Lerp(p0, p1, t);
	Vector2 p1p2 = Lerp(p1, p2, t);
	Vector2 p = Lerp(p0p1, p1p2, t);
	return p;
}
