#pragma once

#include "math/Tuple.h"

class Point2UI : public Tuple<unsigned int> {
public:
	inline Point2UI(unsigned int _x = 0.0f, unsigned int _y = 0.0f)
		: Tuple(_x, _y, 0, 1) {
	}

	inline Point2UI(Tuple<unsigned int> t) : Point2UI(t.x, t.y) {}

	inline Point2UI(Tuple<int> t) : Point2UI(t.x, t.y) {}

	static inline Point2UI zero() { return Point2UI(0u, 0u); }
	static inline Point2UI unit_x() { return Point2UI(1u, 0u); }
	static inline Point2UI unit_y() { return Point2UI(0u, 1u); }
};
