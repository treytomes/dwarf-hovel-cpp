#pragma once

class Color {
public:
	float r;
	float g;
	float b;
	float a;

	Color(float _r, float _g, float _b, float _a = 1.0f);
	//inline Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255)
	//	: Color((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, (float)a / 255.0f) {}

	inline Color add(Color clr) {
		return Color(r + clr.r, g + clr.g, b + clr.b, a + clr.a);
	}

	inline Color subtract(Color clr) {
		return Color(r - clr.r, g - clr.g, b - clr.b, a - clr.a);
	}

	inline Color scale(float v) {
		return Color(v * r, v * g, v * b, a);
	}

	inline Color inverted() {
		return Color(1.0f - r, 1.0f - g, 1.0f - b, 1.0f);
	}

	inline Color desaturated() {
		return white().subtract(*this).scale(0.5f).add(*this).scale(0.5f);
	}

	inline Color lightest() {
		return white().subtract(*this).scale(0.75f).add(*this);
	}

	inline Color lighter() {
		return white().subtract(*this).scale(0.65f).add(*this);
	}

	inline Color light() {
		return white().subtract(*this).scale(0.45f).add(*this);
	}

	inline Color dark() {
		return scale(0.75f);
	}

	inline Color darker() {
		return scale(0.5f);
	}

	inline Color darkest() {
		return scale(0.25f);
	}

	inline Color& operator=(const Color& other) {
		r = other.r;
		g = other.g;
		b = other.b;
		a = other.a;
		return *this;
	}

	inline Color& operator+=(const Color& rhs) {
		return add(rhs);
	}

	inline Color operator+(const Color& rhs) {
		return add(rhs);
	}

	inline Color& operator-=(const Color& rhs) {
		return subtract(rhs);
	}

	inline Color operator-(const Color& rhs) {
		return subtract(rhs);
	}

	inline Color& operator*=(const float v) {
		return scale(v);
	}

	inline Color operator*(const float v) {
		return scale(v);
	}

	static inline Color red()         { return Color(1.00f, 0.00f, 0.00f); }
	static inline Color flame()       { return Color(1.00f, 0.25f, 0.00f); }
	static inline Color orange()      { return Color(1.00f, 0.50f, 0.00f); }
	static inline Color amber()       { return Color(1.00f, 0.75f, 0.00f); }
	static inline Color yellow()      { return Color(1.00f, 1.00f, 0.00f); }
	static inline Color lime()        { return Color(0.75f, 1.00f, 0.00f); }
	static inline Color chartreuse()  { return Color(0.50f, 1.00f, 0.00f); }
	static inline Color green()       { return Color(0.00f, 1.00f, 0.00f); }
	static inline Color sea()         { return Color(0.00f, 1.00f, 0.50f); }
	static inline Color turquoise()   { return Color(0.00f, 1.00f, 0.75f); }
	static inline Color cyan()        { return Color(0.00f, 1.00f, 1.00f); }
	static inline Color sky()         { return Color(0.00f, 0.75f, 1.00f); }
	static inline Color azure()       { return Color(0.00f, 0.50f, 1.00f); }
	static inline Color blue()        { return Color(0.00f, 0.00f, 1.00f); }
	static inline Color han()         { return Color(0.25f, 0.00f, 1.00f); }
	static inline Color violet()      { return Color(0.50f, 0.00f, 1.00f); }
	static inline Color purple()      { return Color(0.75f, 0.00f, 1.00f); }
	static inline Color fuchsia()     { return Color(1.00f, 0.00f, 1.00f); }
	static inline Color magenta()     { return Color(1.00f, 0.00f, 0.75f); }
	static inline Color pink()        { return Color(1.00f, 0.00f, 0.50f); }
	static inline Color crimson()     { return Color(1.00f, 0.00f, 0.25f); }
	static inline Color brass()       { return Color(0.75f, 0.59f, 0.38f); }
	static inline Color copper()      { return Color(0.75f, 0.53f, 0.49f); }
	static inline Color gold()        { return Color(0.90f, 0.75f, 0.00f); }
	static inline Color silver()      { return Color(0.80f, 0.80f, 0.80f); }
	static inline Color gray()        { return Color(0.50f, 0.50f, 0.50f); }
	static inline Color sepia()       { return Color(0.62f, 0.53f, 0.39f); }
	static inline Color transparent() { return Color(0.00f, 0.00f, 0.00f, 0.00f); }
	static inline Color black()       { return Color(0.00f, 0.00f, 0.00f); }
	static inline Color white()       { return Color(1.00f, 1.00f, 1.00f); }
	static inline Color maroon()      { return Color(0.50f, 0.00f, 0.00f); }
	static inline Color olive()       { return Color(0.50f, 0.50f, 0.00f); }
	static inline Color teal()        { return Color(0.00f, 0.50f, 0.50f); }
	static inline Color brown()       { return Color(0.60f, 0.40f, 0.20f); }
};

inline bool operator==(const Color& lhs, const Color& rhs) {
	return (lhs.r == rhs.r) && (lhs.g == rhs.g) && (lhs.b == rhs.b) && (lhs.a == rhs.a);
}

inline bool operator!=(const Color& lhs, const Color& rhs) {
	return (lhs.r != rhs.r) || (lhs.g != rhs.g) || (lhs.b != rhs.b) || (lhs.a != rhs.a);
}
