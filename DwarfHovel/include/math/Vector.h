#pragma once

#include "Tuple.h"

template <typename TComponent>
class Vector : public Tuple<TComponent> {
public:
	inline Vector(TComponent _x = 0, TComponent _y = 0, TComponent _z = 0)
		: Tuple(_x, _y, _z, 0) {
	}
	
	template <typename TOther>
	inline Vector(Tuple<TOther> t) : Vector((TComponent)t.x, (TComponent)t.y, (TComponent)t.z) {}

	static inline Vector zero() { return Vector(0, 0, 0); }
	static inline Vector unit_x() { return Vector(1, 0, 0); }
	static inline Vector unit_y() { return Vector(0, 1, 0); }
	static inline Vector unit_z() { return Vector(0, 0, 1); }

	static inline Vector north() { return -unit_y(); }
	static inline Vector south() { return unit_y(); }
	static inline Vector west() { return -unit_x(); }
	static inline Vector east() { return unit_x(); }

	inline float magnitude() {
		return sqrtf((float)(x * x + y * y));
	}
};

typedef Vector<float> VectorF;
typedef Vector<int> VectorI;
typedef Vector<unsigned int> VectorUI;
