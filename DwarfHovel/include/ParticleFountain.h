#pragma once

#include <cstdlib>
#include <vector>
#include "ColoredBitmap.h"
#include "IRenderContext.h"
#include "Logger.h"
#include "Particle.h"
#include "math/math.h"

class ParticleFountain {
public:
	inline static ParticleFountain* from_bitmap(Point2F position, ColoredBitmap* bitmap) {
		ParticleFountain* fountain = new ParticleFountain();
		unsigned int base_life_span = 1000u;
		for (unsigned int y = 0u; y < bitmap->get_height(); y++) {
			for (unsigned int x = 0u; x < bitmap->get_width(); x++) {
				Vector2F speed = Vector2F(
						x - bitmap->get_width() / 2.0f,
						y - bitmap->get_height() / 2.0f) * (float)bitmap->get_height() // Outer particles fly away faster.
						- Vector2F::unit_y() * (float)(rand() % (bitmap->get_height() * 2)); // Add a random -y factor to the speed.  Makes it look more explosion-y.
				
				fountain->children.push_back(new Particle(
					bitmap->get_pixel(x, y),
					position + Point2F((float)x, (float)y),
					speed,
					Vector2F(0.0f, (float)bitmap->get_width() * bitmap->get_height()), // Gravity is +y.
					base_life_span - (unsigned int)(speed.magnitude() * bitmap->get_height()) // Slower particles live longer.
				));
			}
		}
		return fountain;
	}

	inline void update(unsigned int delta_time_ms) {
		std::vector<Particle*> dead_children;

		LOG_INFO("Size: %d", children.size());
		LOG_INFO("Delta time: %d", delta_time_ms);

		for (auto n = 0; n < children.size(); n++) {
			Particle* child = children[n];
			child->update(delta_time_ms);
			if (child->is_dead()) {
				LOG_INFO("dead!");
				dead_children.push_back(child);
				remove(child);
				n--;
			}
		}

		for (auto iter = dead_children.begin(); iter != dead_children.end(); iter++) {
			Particle* child = *iter;
			delete child;
		}
	}

	inline void draw(IRenderContext* context, unsigned int delta_time_ms) {
		for (auto iter = children.begin(); iter != children.end(); iter++) {
			Particle* child = *iter;
			child->draw(context, delta_time_ms);
		}
	}

	inline bool is_alive() { return children.size() > 0; }
	inline bool is_dead() { return !is_alive(); }

private:
	std::vector<Particle*> children;

	inline void remove(Particle* child) {
		children.erase(std::remove(children.begin(), children.end(), child));
	}
};