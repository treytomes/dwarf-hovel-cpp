#pragma once

#include "math/Tuple.h"

class Vector2UI : public Tuple<unsigned int> {
public:
	inline Vector2UI(int _x = 0.0f, int _y = 0.0f)
		: Tuple(_x, _y, 0, 0) {
	}

	inline Vector2UI(Tuple<unsigned int> t) : Vector2UI(t.x, t.y) {}

	static inline Vector2UI zero() { return Vector2UI(0u, 0u); }
	static inline Vector2UI unit_x() { return Vector2UI(1u, 0u); }
	static inline Vector2UI unit_y() { return Vector2UI(0u, 1u); }

	inline float magnitude() {
		return sqrtf((float)(x * x + y * y));
	}
};
