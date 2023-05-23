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

	static inline Color red() { return Color(255, 0, 0); }
	static inline Color flame() { return Color(255, 63, 0); }
	static inline Color orange() { return Color(255, 127, 0); }
	static inline Color amber() { return Color(255, 191, 0); }
	static inline Color yellow() { return Color(255, 255, 0); }
	static inline Color lime() { return Color(191, 255, 0); }
	static inline Color chartreuse() { return Color(127, 255, 0); }
	static inline Color green() { return Color(0, 255, 0); }
	static inline Color sea() { return Color(0, 255, 127); }
	static inline Color turquoise() { return Color(0, 255, 191); }
	static inline Color cyan() { return Color(0, 255, 255); }
	static inline Color sky() { return Color(0, 191, 255); }
	static inline Color azure() { return Color(0, 127, 255); }
	static inline Color blue() { return Color(0, 0, 255); }
	static inline Color han() { return Color(63, 0, 255); }
	static inline Color violet() { return Color(127, 0, 255); }
	static inline Color purple() { return Color(191, 0, 255); }
	static inline Color fuchsia() { return Color(255, 0, 255); }
	static inline Color magenta() { return Color(255, 0, 191); }
	static inline Color pink() { return Color(255, 0, 127); }
	static inline Color crimson() { return Color(255, 0, 63); }
	static inline Color brass() { return Color(191, 151, 96); }
	static inline Color copper() { return Color(191, 136, 124); }
	static inline Color gold() { return Color(229, 191, 0); }
	static inline Color silver() { return Color(203, 203, 203); }
	static inline Color gray() { return Color(127, 127, 127); }
	static inline Color sepia() { return Color(158, 134, 100); }
	static inline Color transparent() { return Color(0, 0, 0, 0); }
	static inline Color black() { return Color(0, 0, 0); }
	static inline Color white() { return Color(255, 255, 255); }
	static inline Color maroon() { return Color(127, 0, 0); }
	static inline Color olive() { return Color(127, 127, 0); }
	static inline Color teal() { return Color(0, 127, 127); }
	static inline Color brown() { return Color(153, 102, 51); }

};

inline bool operator==(const Color& lhs, const Color& rhs) {
	return (lhs.red == rhs.red) && (lhs.green == rhs.green) && (lhs.blue == rhs.blue) && (lhs.alpha == rhs.alpha);
}

inline bool operator!=(const Color& lhs, const Color& rhs) {
	return (lhs.red != rhs.red) || (lhs.green != rhs.green) || (lhs.blue != rhs.blue) || (lhs.alpha != rhs.alpha);
}
