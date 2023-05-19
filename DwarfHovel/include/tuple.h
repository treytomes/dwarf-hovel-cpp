#pragma once

template <typename TComponent>
class Tuple {
public:
	TComponent x;
	TComponent y;
	TComponent z;
	TComponent w;

	inline Tuple(TComponent _x, TComponent _y, TComponent _z, TComponent _w)
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

template <typename TComponent>
inline bool operator==(const Tuple<TComponent>& lhs, const Tuple<TComponent>& rhs) {
	return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z) && (lhs.w == rhs.w);
}

template <typename TComponent>
inline bool operator!=(const Tuple<TComponent>& lhs, const Tuple<TComponent>& rhs) {
	return (lhs.x != rhs.x) || (lhs.y != rhs.y) || (lhs.z != rhs.z) || (lhs.w != rhs.w);
}
