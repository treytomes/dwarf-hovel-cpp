#pragma once

template <typename TComponent>
class Tuple {
public:
	const TComponent x;
	const TComponent y;
	const TComponent z;
	const TComponent w;

	Tuple(TComponent _x, TComponent _y, TComponent _z, TComponent _w)
		: x(_x), y(_y), z(_z), w(_w) {
	}
};
