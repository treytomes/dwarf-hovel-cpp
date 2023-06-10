#pragma once

#include <functional>
#include "IRenderContext.h"
#include "math/math.h"

class Map;

// Part of a parent Map object.  Able to look at adjacent map tiles to help determine what it should render.
// Also needs some type of metadata that will allow the tile to adjust, e.g. when the grass grows.
class MapTile {
public:
	const unsigned int id;

	MapTile(const unsigned int _id);

	// The pixel position is relative to the screen in pixels.
	// The map position is the index into the map structure.
	virtual void draw(IRenderContext* context, PointUI pixel_position, Map* map, PointUI map_tile_position);
};
