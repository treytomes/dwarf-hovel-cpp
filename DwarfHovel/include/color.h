#pragma once

class Color {
public:
	const float red;
	const float green;
	const float blue;
	const float alpha;

	Color(float r, float g, float b, float a = 1.0f);

};

inline bool operator==(const Color& lhs, const Color& rhs) {
	return (lhs.red == rhs.red) && (lhs.green == rhs.green) && (lhs.blue == rhs.blue) && (lhs.alpha == rhs.alpha);
}

inline bool operator!=(const Color& lhs, const Color& rhs) {
	return (lhs.red != rhs.red) || (lhs.green != rhs.green) || (lhs.blue != rhs.blue) || (lhs.alpha != rhs.alpha);
}
