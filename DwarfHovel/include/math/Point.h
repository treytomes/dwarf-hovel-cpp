#pragma once

#include "math/Tuple.h"

template <typename TComponent>
class Point : public Tuple<TComponent> {
public:
	inline Point(TComponent _x = 0, TComponent _y = 0, TComponent _z = 0)
		: Tuple(_x, _y, _z, 1) {
	}
	
	template <typename TOther>
	inline Point(Tuple<TOther> t) : Point((TComponent)t.x, (TComponent)t.y, (TComponent)t.z) {}

	static inline Point zero() { return Point(0, 0, 0); }
	static inline Point unit_x() { return Point(1, 0, 0); }
	static inline Point unit_y() { return Point(0, 1, 0); }
	static inline Point unit_z() { return Point(0, 0, 1); }
};

typedef Point<float> PointF;
typedef Point<int> PointI;
typedef Point<unsigned int> PointUI;
