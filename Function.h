#pragma once
#include "Vector2.h"

float Length(const Vector2& v);

int IsCircleHit(Vector2 posA, float radiusA, Vector2 posB, float radiusB);

Vector2 Lerp(const Vector2& p0, const Vector2& p1, float t);

Vector2 Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, float t);
