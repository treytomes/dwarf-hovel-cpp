#pragma once

#include "Color.h"
#include "IRenderContext.h"
#include "math/math.h"

class Particle {
public:
	inline Particle(Color _color, Point2F _position, Vector2F _speed, Vector2F _acceleration, unsigned int _life_span)
		: color(_color), position(_position), speed(_speed), acceleration(_acceleration), life_span(_life_span), total_elapsed_time(0u) {
	}

	inline ~Particle() {
	}

	inline void update(unsigned int delta_time_ms) {
		total_elapsed_time += delta_time_ms;
		position += speed * (float)delta_time_ms / 1000.0f;
		speed += acceleration * (float)delta_time_ms / 1000.0f;
	}

	inline void draw(IRenderContext* context, unsigned int delta_time_ms) {
		context->set_pixel((unsigned int)position.x, (unsigned int)position.y, color);
	}

	inline bool is_alive() { return total_elapsed_time < life_span; }
	inline bool is_dead() { return !is_alive(); }

private:
	Color color;
	Point2F position;

	// Speed is in pixels per second.
	Vector2F speed;

	Vector2F acceleration;

	unsigned int life_span;
	unsigned int total_elapsed_time;
};
