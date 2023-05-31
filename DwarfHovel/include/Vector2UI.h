#pragma once

#include <cmath>
#include "Tuple.h"

class Vector2UI : public Tuple<unsigned int> {
public:
	inline Vector2UI(unsigned int _x = 0.0f, unsigned int _y = 0.0f)
		: Tuple(_x, _y, 0, 0) {
	}

	inline Vector2UI(Tuple<unsigned int> t) : Vector2UI(t.x, t.y) {}

	static inline Vector2UI zero() { return Vector2UI(0u, 0u); }
	static inline Vector2UI unit_x() { return Vector2UI(1u, 0u); }
	static inline Vector2UI unit_y() { return Vector2UI(0u, 1u); }

	static inline Vector2UI north() { return -unit_y(); }
	static inline Vector2UI south() { return unit_y(); }
	static inline Vector2UI west() { return -unit_x(); }
	static inline Vector2UI east() { return unit_x(); }

	inline float magnitude() {
		return sqrtf((float)(x * x + y * y));
	}
};
