#pragma once

#include "math/math.h"

class Rectangle {
public:
	inline Rectangle(PointUI _point, VectorUI _size) : point(_point), size(_size) {}

	inline Rectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height) : Rectangle(PointUI(x, y), VectorUI(width, height)) {}

	inline PointUI get_position() { return point; }
	inline VectorUI get_size() { return size; }

	inline PointUI get_top_left() { return get_position(); }

	inline unsigned int get_x() { return point.x; }
	inline unsigned int get_y() { return point.y; }
	inline unsigned int get_width() { return size.x; }
	inline unsigned int get_height() { return size.y; }
	inline unsigned int get_left() { return get_x(); }
	inline unsigned int get_right() { return get_left() + get_width() - 1; }
	inline unsigned int get_top() { return get_y(); }
	inline unsigned int get_bottom() { return get_top() + get_height() - 1; }

	inline void set_position(PointUI value) { point = value; }
	inline void set_size(VectorUI value) { size = value; }

	inline void set_x(unsigned int value) { point.x = value; }
	inline void set_y(unsigned int value) { point.y = value; }
	inline void set_width(unsigned int value) { size.x = value; }
	inline void set_height(unsigned int value) { size.y = value; }

	inline void set_left(unsigned int value) { set_x(value); }
	inline void set_right(unsigned int value) { set_width(value - get_left() + 1); }
	inline void set_top(unsigned int value) { set_y(value); }
	inline void set_bottom(unsigned int value) { set_height(value - get_top() + 1); }

	inline bool contains(unsigned int x, unsigned int y) {
		return math::is_in_range(x, get_left(), get_right()) && math::is_in_range(y, get_top(), get_bottom());
	}

	inline bool contains(PointUI point) {
		return contains(point.x, point.y);
	}

	inline bool intersects(Rectangle rect) {
		return get_left() <= rect.get_right() && rect.get_left() <= get_right() && get_top() <= rect.get_bottom() && rect.get_top() <= get_bottom();
	}

	inline void offset(Tuple<unsigned int> delta) {
		point += delta;
	}

	inline Rectangle& operator=(const Rectangle& other) {
		point = PointUI(other.point.x, other.point.y);
		size = VectorUI(other.size.x, other.size.y);
		return *this;
	}

private:
	PointUI point;
	VectorUI size;
};
