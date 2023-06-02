#pragma once

#include <cmath>
#include "Tuple.h"

class Vector2F : public Tuple<float> {
public:
	inline Vector2F(float _x = 0.0f, float _y = 0.0f)
		: Tuple(_x, _y, 0, 0) {
	}

	inline Vector2F(Tuple<float> t) : Vector2F(t.x, t.y) {}

	static inline Vector2F zero() { return Vector2F(0.0f, 0.0f); }
	static inline Vector2F unit_x() { return Vector2F(1.0f, 0.0f); }
	static inline Vector2F unit_y() { return Vector2F(0.0f, 1.0f); }

	static inline Vector2F north() { return -unit_y(); }
	static inline Vector2F south() { return unit_y(); }
	static inline Vector2F west() { return -unit_x(); }
	static inline Vector2F east() { return unit_x(); }

	inline float magnitude() {
		return sqrtf((float)(x * x + y * y));
	}
};
