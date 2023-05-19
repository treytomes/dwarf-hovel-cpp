#pragma once

class Color {
public:
	float red;
	float green;
	float blue;
	float alpha;

	Color(float r, float g, float b, float a = 1.0f);


	inline Color& operator=(const Color& other) {
		red = other.red;
		green = other.green;
		blue = other.blue;
		alpha = other.alpha;
		return *this;
	}
};

inline bool operator==(const Color& lhs, const Color& rhs) {
	return (lhs.red == rhs.red) && (lhs.green == rhs.green) && (lhs.blue == rhs.blue) && (lhs.alpha == rhs.alpha);
}

inline bool operator!=(const Color& lhs, const Color& rhs) {
	return (lhs.red != rhs.red) || (lhs.green != rhs.green) || (lhs.blue != rhs.blue) || (lhs.alpha != rhs.alpha);
}
