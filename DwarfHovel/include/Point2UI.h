#pragma once

#include "Tuple.h"

class Point2UI : public Tuple<unsigned int> {
public:
	Point2UI(unsigned int _x = 0.0f, unsigned int _y = 0.0f)
		: Tuple(_x, _y, 0, 1) {
	}
};
