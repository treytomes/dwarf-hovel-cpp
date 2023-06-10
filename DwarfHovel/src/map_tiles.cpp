#include "map_tiles.h"
#include "MapTile.h"

std::map<unsigned int, MapTile*> map_tiles::data;

MapTile map_tiles::grass_floor(1);
MapTile map_tiles::stone_wall(2);


void map_tiles::register_tile(MapTile* tile) {
	data[tile->id] = tile;
}