#pragma once

#include "math/Tuple.h"

class Point2F : public Tuple<float> {
public:
	inline Point2F(float _x = 0.0f, float _y = 0.0f)
		: Tuple(_x, _y, 0, 1) {
	}

	inline Point2F(Tuple<float> t) : Point2F(t.x, t.y) {}
	inline Point2F(Tuple<unsigned int> t) : Point2F((float)t.x, (float)t.y) {}
	inline Point2F(Tuple<int> t) : Point2F((float)t.x, (float)t.y) {}

	static inline Point2F zero() { return Point2F(0.0f, 0.0f); }
	static inline Point2F unit_x() { return Point2F(1.0f, 0.0f); }
	static inline Point2F unit_y() { return Point2F(0.0f, 1.0f); }
};
