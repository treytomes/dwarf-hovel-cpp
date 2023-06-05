#pragma once

#define PI 3.14159265359f
#define DEGREE (PI / 180.0f)

namespace math {
	template <typename T>
	inline void swap(T& v0, T& v1) {
		T tmp = v0;
		v0 = v1;
		v1 = tmp;
	}

	template <typename T>
	inline bool is_in_range(T value, T inclusive_min, T inclusive_max) {
		return (inclusive_min <= value) && (value <= inclusive_max);
	}

	template <typename T>
	inline T clamp(T value, T inclusive_min, T inclusive_max) {
		if (value < inclusive_min) {
			return inclusive_min;
		} else if (value > inclusive_max) {
			return inclusive_max;
		} else {
			return value;
		}
	}

	template <typename T>
	inline T lerp(T a, T b, float t) {
		return (T)(a + (b - a) * t);
	}
}