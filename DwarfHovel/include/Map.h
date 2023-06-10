#pragma once

#include "IRenderContext.h"
#include "MapTile.h"

#define MAP_WIDTH 256
#define MAP_HEIGHT 256
#define MAP_MIN_X 0
#define MAP_MAX_X (MAP_WIDTH - 1)
#define MAP_MIN_Y 0
#define MAP_MAX_Y (MAP_HEIGHT - 1)
#define MAP_TILE_WIDTH 8
#define MAP_TILE_HEIGHT 8

// A map is a single 2D slice of a 3D world.
// The map is potentially surrounded on all sides by 6 more maps.
// A map is composed of MapTiles.  It can also be filled with Entities and Portals.
// A Portal is an object that leads to a position on another map.  This is in addition to the maps located in each of the 6 cardinal directions.
// Let's implement a quadtree structure to help with collision detection.
// Needs to track the time a player left and reentered a map.
class Map {
public:
	Map();
	
	inline unsigned int get_tile_id(unsigned int map_tile_x, unsigned int map_tile_y) { return tile_ids[map_tile_y][map_tile_x]; }
	inline void set_tile_id(unsigned int map_tile_x, unsigned int map_tile_y, unsigned int tile_id) { tile_ids[map_tile_y][map_tile_x] = tile_id; }

	inline unsigned int get_metadata(unsigned int map_tile_x, unsigned int map_tile_y) { return metadata[map_tile_y][map_tile_x]; }
	inline void get_metadata(unsigned int map_tile_x, unsigned int map_tile_y, unsigned int value) { metadata[map_tile_y][map_tile_x] = value; }

	void draw(IRenderContext* context, PointUI camera_position);

private:
	unsigned int tile_ids[MAP_HEIGHT][MAP_WIDTH];
	unsigned int metadata[MAP_HEIGHT][MAP_WIDTH];
};
