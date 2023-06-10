#include "MapTile.h"

#include "bitmaps.h"
#include "bitmap_templates.h"
#include "Map.h"
#include "map_tiles.h"
#include <cstdlib>

MapTile::MapTile(const unsigned int _id)
	: id(_id) {
	map_tiles::register_tile(this);
}

void MapTile::draw(IRenderContext* context, PointUI pixel_position, Map* map, PointUI map_tile_position) {
	if (id == 1) {
		std::srand(map_tile_position.x * map_tile_position.y);
		if ((rand() % 20) < 3) {
			bitmaps::grass_floor.draw(context, pixel_position);
		} else {
			bitmap_templates::solid.draw(context, pixel_position, bitmaps::grass_floor.color0, bitmaps::grass_floor.color1, bitmaps::grass_floor.color2, bitmaps::grass_floor.color3);
		}
	} else if (id == 2) {
		bitmaps::stone_wall.draw(context, pixel_position);
	}
}
