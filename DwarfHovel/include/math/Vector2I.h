#pragma once

#include "math/Tuple.h"

class Vector2I : public Tuple<int> {
public:
	inline Vector2I(int _x = 0.0f, int _y = 0.0f)
		: Tuple(_x, _y, 0, 0) {
	}

	inline Vector2I(Tuple<int> t) : Vector2I(t.x, t.y) {}

	static inline Vector2I zero() { return Vector2I(0u, 0u); }
	static inline Vector2I unit_x() { return Vector2I(1u, 0u); }
	static inline Vector2I unit_y() { return Vector2I(0u, 1u); }

	static inline Vector2I north() { return -unit_y(); }
	static inline Vector2I south() { return unit_y(); }
	static inline Vector2I west() { return -unit_x(); }
	static inline Vector2I east() { return unit_x(); }

	inline float magnitude() {
		return sqrtf((float)(x * x + y * y));
	}
};
