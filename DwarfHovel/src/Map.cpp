#include "Map.h"
#include "map_tiles.h"
#include "io/io.h"

Map::Map() {
	for (unsigned int tile_y = MAP_MIN_Y; tile_y <= MAP_MAX_Y; tile_y++) {
		for (unsigned int tile_x = MAP_MIN_X; tile_x <= MAP_MAX_X; tile_x++) {
			set_tile_id(tile_x, tile_y, map_tiles::grass_floor.id);
		}
	}
	for (unsigned int tile_y = MAP_MIN_Y; tile_y <= MAP_MAX_Y; tile_y++) {
		set_tile_id(MAP_MIN_X, tile_y, map_tiles::stone_wall.id);
		set_tile_id(MAP_MAX_X, tile_y, map_tiles::stone_wall.id);
	}
	for (unsigned int tile_x = MAP_MIN_X; tile_x <= MAP_MAX_X; tile_x++) {
		set_tile_id(tile_x, MAP_MIN_Y, map_tiles::stone_wall.id);
		set_tile_id(tile_x, MAP_MAX_Y, map_tiles::stone_wall.id);
	}

	unsigned int center_x = 15;
	unsigned int center_y = 10;
	unsigned int radius = 5;

	unsigned int min_tile_x = math::clamp<unsigned int>(center_x - radius, MAP_MIN_X, center_x);
	unsigned int max_tile_x = math::clamp<unsigned int>(center_x + radius, center_x, MAP_MAX_X);
	unsigned int min_tile_y = math::clamp<unsigned int>(center_y - radius, MAP_MIN_Y, center_y);
	unsigned int max_tile_y = math::clamp<unsigned int>(center_y + radius, center_y, MAP_MAX_Y);
	for (unsigned int tile_y = min_tile_y; tile_y <= max_tile_x; tile_y++) {
		for (unsigned int tile_x = min_tile_x; tile_x <= max_tile_x; tile_x++) {
			unsigned int delta_x = tile_x - center_x;
			unsigned int delta_y = tile_y - center_y;
			if ((delta_x * delta_x) + (delta_y * delta_y) <= radius * radius) {
				set_tile_id(tile_x, tile_y, 0);
			}
		}
	}
}

void Map::draw(IRenderContext* context, PointUI camera_position) {
	PointUI pixel_size = Settings::get_instance()->virtual_window_size;
	PointUI tile_size = PointUI(pixel_size.x / MAP_TILE_WIDTH, pixel_size.y / MAP_TILE_HEIGHT);

	unsigned int map_min_y = MAP_MIN_Y;
	unsigned int map_max_y = map_min_y + tile_size.y - 1;
	unsigned int map_min_x = MAP_MIN_X;
	unsigned int map_max_x = map_min_x + tile_size.x - 1;

	for (unsigned int tile_y = map_min_y; tile_y <= map_max_y; tile_y++) {
		if (tile_y < MAP_MIN_Y) { continue; }
		if (tile_y > MAP_MAX_Y) { break; }

		for (unsigned int tile_x = map_min_x; tile_x <= map_max_x; tile_x++) {
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

			tile->draw(context, camera_position + PointUI(tile_x * MAP_TILE_WIDTH, tile_y * MAP_TILE_WIDTH), this, PointUI(tile_x, tile_y));
		}
	}
}
