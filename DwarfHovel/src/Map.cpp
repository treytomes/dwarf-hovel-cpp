#include "Map.h"
#include "map_tiles.h"
#include "io/io.h"

class MapRenderContext {
public:
	MapRenderContext(Map* _map) : map(_map) {}

	inline void draw_filled_rect(unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2, unsigned int tile_id) {
		for (unsigned int tile_y = y1; tile_y <= y2; tile_y++) {
			for (unsigned int tile_x = x1; tile_x <= x2; tile_x++) {
				map->set_tile_id(tile_x, tile_y, tile_id);
			}
		}
	}

	inline void fill(unsigned int tile_id) {
		draw_filled_rect(MAP_MIN_X, MAP_MAX_X, MAP_MIN_Y, MAP_MAX_Y, tile_id);
	}

	inline void draw_v_line(unsigned int x, unsigned int y1, unsigned int y2, unsigned int tile_id) {
		for (unsigned int tile_y = y1; tile_y <= y2; tile_y++) {
			map->set_tile_id(x, tile_y, tile_id);
		}
	}

	inline void draw_h_line(unsigned int x1, unsigned int x2, unsigned int y, unsigned int tile_id) {
		for (unsigned int tile_x = x1; tile_x <= x2; tile_x++) {
			map->set_tile_id(tile_x, y, tile_id);
		}
	}

	inline void draw_filled_circle(unsigned int xc, unsigned int yc, unsigned int radius, unsigned int tile_id) {
		unsigned int min_tile_x = math::clamp<unsigned int>(xc - radius, MAP_MIN_X, xc);
		unsigned int max_tile_x = math::clamp<unsigned int>(xc + radius, xc, MAP_MAX_X);
		unsigned int min_tile_y = math::clamp<unsigned int>(yc - radius, MAP_MIN_Y, yc);
		unsigned int max_tile_y = math::clamp<unsigned int>(yc + radius, yc, MAP_MAX_Y);
		for (unsigned int tile_y = min_tile_y; tile_y <= max_tile_x; tile_y++) {
			for (unsigned int tile_x = min_tile_x; tile_x <= max_tile_x; tile_x++) {
				unsigned int delta_x = tile_x - xc;
				unsigned int delta_y = tile_y - yc;
				if ((delta_x * delta_x) + (delta_y * delta_y) <= radius * radius) {
					map->set_tile_id(tile_x, tile_y, 0);
				}
			}
		}
	}

private:
	Map* map;
};

Map::Map() {
	MapRenderContext context(this);
	context.fill(map_tiles::grass_floor.id);
	context.draw_v_line(MAP_MIN_X, MAP_MIN_Y, MAP_MAX_Y, map_tiles::stone_wall.id);
	context.draw_v_line(MAP_MAX_X, MAP_MIN_Y, MAP_MAX_Y, map_tiles::stone_wall.id);
	context.draw_h_line(MAP_MIN_X + 1, MAP_MAX_X - 1, MAP_MIN_Y, map_tiles::stone_wall.id);
	context.draw_h_line(MAP_MIN_X + 1, MAP_MAX_X - 1, MAP_MAX_Y, map_tiles::stone_wall.id);

	context.draw_filled_circle(15, 10, 5, 0);
}

void Map::draw(IRenderContext* context, PointI offset) {
	PointUI pixel_size = Settings::get_instance()->virtual_window_size;
	PointUI tile_size = PointUI(pixel_size.x / MAP_TILE_WIDTH, pixel_size.y / MAP_TILE_HEIGHT);

	int map_min_y = -offset.y / MAP_TILE_HEIGHT;
	int map_max_y = map_min_y + tile_size.y;
	int map_min_x = -offset.x / MAP_TILE_WIDTH;
	int map_max_x = map_min_x + tile_size.x;

	//LOG_INFO("map_min: (%u, %u)", map_min_x, map_min_y);

	for (int tile_y = map_min_y; tile_y <= map_max_y; tile_y++) {
		if (tile_y < MAP_MIN_Y) { continue; }
		if (tile_y > MAP_MAX_Y) { break; }

		for (int tile_x = map_min_x; tile_x <= map_max_x; tile_x++) {
			if (tile_x < MAP_MIN_X) { continue; }
			if (tile_x > MAP_MAX_X) { break; }

			unsigned int tile_id = get_tile_id(tile_x, tile_y);
			if (tile_id == 0) {
				continue;
			}

			MapTile* tile = map_tiles::get_by_id(tile_id);
			if (tile == nullptr) {
				continue;
			}

			tile->draw(context, PointUI(tile_x * MAP_TILE_WIDTH + offset.x, tile_y * MAP_TILE_WIDTH + offset.y), this, PointUI(tile_x, tile_y));
		}
	}
}
