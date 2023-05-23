#pragma once

#include "moremath.h"
#include "Point2UI.h"
#include "Vector2UI.h"

class Rectangle {
public:
	inline Rectangle(Point2UI _point, Vector2UI _size) : point(_point), size(_size) {}

	inline Rectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height) : Rectangle(Point2UI(x, y), Vector2UI(width, height)) {}

	inline Point2UI get_position() { return point; }
	inline Vector2UI get_size() { return size; }

	inline unsigned int get_x() { return point.x; }
	inline unsigned int get_y() { return point.y; }
	inline unsigned int get_width() { return size.x; }
	inline unsigned int get_height() { return size.y; }
	inline unsigned int get_left() { return get_x(); }
	inline unsigned int get_right() { return get_left() + get_width() - 1; }
	inline unsigned int get_top() { return get_y(); }
	inline unsigned int get_bottom() { return get_top() + get_height() - 1; }

	inline void set_position(Point2UI value) { point = value; }
	inline void set_size(Vector2UI value) { size = value; }

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

	inline bool contains(Point2UI point) {
		return contains(point.x, point.y);
	}

private:
	Point2UI point;
	Vector2UI size;
};
