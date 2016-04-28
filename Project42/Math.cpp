#include "Math.h"

bool Proj42::rectsIntersect(const Vector4 & a, const Vector4 & b)
{
	Vector2 amin = Vector2(a.x, a.y);
	Vector2 amax = Vector2(a.x + a.z, a.y + a.w);
	Vector2 bmin = Vector2(b.x, b.y);
	Vector2 bmax = Vector2(b.x + b.z, b.y + b.w);

	float d1x = bmin.x - amax.x;
	float d1y = bmin.y - amax.y;
	float d2x = amin.x - bmax.x;
	float d2y = amin.y - bmax.y;

	if (d1x > 0.0f || d1y > 0.0f)
		return false;

	if (d2x > 0.0f || d2y > 0.0f)
		return false;

	return true;
}

bool Proj42::circlesIntersect(const Circle & a, const Circle & b)
{
	float x = a.position.x - b.position.x;
	float y = a.position.y - b.position.y;
	float centerDistanceSq = x * x + y * y;
	float radius = a.radius + b.radius;
	float radiusSq = radius * radius;
	return centerDistanceSq <= radiusSq;
}

void Proj42::resolveCollision(Vector4 * a, Vector4 * b)
{

}
