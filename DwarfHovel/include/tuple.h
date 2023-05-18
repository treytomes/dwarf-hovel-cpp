#pragma once

template <typename TComponent>
class Tuple {
public:
	TComponent x;
	TComponent y;
	TComponent z;
	TComponent w;

	Tuple(TComponent _x, TComponent _y, TComponent _z, TComponent _w)
		: x(_x), y(_y), z(_z), w(_w) {
	}

	inline Tuple& operator=(const Tuple& other) {
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
		return *this;
	}
};
