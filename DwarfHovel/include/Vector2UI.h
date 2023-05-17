#pragma once

#include "Tuple.h"

class Vector2UI : public Tuple<unsigned int> {
public:
	Vector2UI(unsigned int _x, unsigned int _y)
	: Tuple(_x, _y, 0, 1) {
	}
};
