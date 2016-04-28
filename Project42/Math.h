#pragma once

#include <glm/glm.hpp>

namespace Proj42 {

	typedef glm::vec2 Vector2;
	typedef glm::vec4 Vector4;

	struct Circle {
		Vector2 position;
		float radius;

		Circle() {}
		Circle(Vector2 pos, float r) : position(pos), radius(r) {}
	};

	struct CollisionInfo {
		float xdepth;
		float ydepth;
	};

	extern bool rectsIntersect(const Vector4 &a, const Vector4 &b);

	extern bool circlesIntersect(const Circle &a, const Circle &b);

	extern void resolveCollision(Vector4* a, Vector4* b);

}
