#pragma once

#include "Tuple.h"

class Point2I : public Tuple<int> {
public:
	inline Point2I(int _x = 0.0f, int _y = 0.0f)
		: Tuple(_x, _y, 0, 1) {
	}

	inline Point2I(Tuple<unsigned int> t) : Point2I(t.x, t.y) {}
	inline Point2I(Tuple<int> t) : Point2I(t.x, t.y) {}

	static inline Point2I zero() { return Point2I(0u, 0u); }
	static inline Point2I unit_x() { return Point2I(1u, 0u); }
	static inline Point2I unit_y() { return Point2I(0u, 1u); }
};
