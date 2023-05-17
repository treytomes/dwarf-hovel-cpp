#pragma once

namespace math {
	template <typename T>
	inline void swap(T& v0, T& v1) {
		T tmp = v0;
		v0 = v1;
		v1 = tmp;
	}

	template <typename T>
	inline bool is_in_range(T value, T inclusive_min, T exclusive_max) {
		return (inclusive_min <= value) && (value < exclusive_max);
	}
}