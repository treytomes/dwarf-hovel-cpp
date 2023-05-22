#pragma once

#include "Tuple.h"

class Vector2UI : public Tuple<unsigned int> {
public:
	Vector2UI(unsigned int _x = 0.0f, unsigned int _y = 0.0f)
		: Tuple(_x, _y, 0, 0) {
	}
};
