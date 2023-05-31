#pragma once

#include <cmath>
#include "Tuple.h"

class Vector2UI : public Tuple<unsigned int> {
public:
	Vector2UI(unsigned int _x = 0.0f, unsigned int _y = 0.0f)
		: Tuple(_x, _y, 0, 0) {
	}

	static inline Vector2UI zero() { return Vector2UI(0u, 0u); }

	inline float magnitude() {
		return sqrtf((float)(x * x + y * y));
	}
};
