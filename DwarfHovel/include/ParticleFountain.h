#pragma once

#include <vector>
#include "ColoredBitmap.h"
#include "IRenderContext.h"
#include "Logger.h"
#include "Particle.h"

class ParticleFountain {
public:
	inline static ParticleFountain* from_bitmap(Point2F position, ColoredBitmap* bitmap) {
		ParticleFountain* fountain = new ParticleFountain();

		unsigned int base_life_span = 1000u;
		for (unsigned int y = 0u; y < bitmap->get_height(); y++) {
			for (unsigned int x = 0u; x < bitmap->get_width(); x++) {
				Color color = bitmap->get_pixel(x, y);
				Point2F particle_position = position + Point2F((float)x, (float)y);
				
				// Outer particles fly away faster.
				Vector2F speed = Vector2F(x - bitmap->get_width() / 2.0f, y - bitmap->get_height() / 2.0f) * 8.0f;
				
				// Slower particles live longer.
				unsigned int life_span = base_life_span - (unsigned int)(speed.magnitude() * 8.0f);
				
				// Gravity is +y.
				Vector2F acceleration = Vector2F(0.0f, 64.0f);

				fountain->children.push_back(new Particle(color, particle_position, speed, acceleration, life_span));
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