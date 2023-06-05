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

	inline Tuple& operator+=(const Tuple& rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}

	inline Tuple operator+(const Tuple& rhs) {
		return Tuple(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
	}

	inline Tuple& operator-=(const Tuple& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}

	inline Tuple operator*(const TComponent& value) {
		return Tuple(x * value, y * value, z * value, w * value);
	}

	inline Tuple& operator*=(const Tuple& rhs) {
		x *= value;
		y *= value;
		z *= value;
		w *= value;
		return *this;
	}

	inline Tuple operator/(const TComponent& value) {
		return Tuple(x / value, y / value, z / value, w / value);
	}

	inline Tuple& operator/=(const Tuple& rhs) {
		x /= value;
		y /= value;
		z /= value;
		w /= value;
		return *this;
	}

	inline Tuple operator-(const Tuple& rhs) {
		return Tuple(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
	}

	inline Tuple operator-() const {
		return Tuple(-x, -y, -z, -w);
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