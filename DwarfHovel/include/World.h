#pragma once

#include "Map.h"

// A world is a pseudo-infinitely large 3D array of Maps.
// Rather than holding the entire world in memory, first try loading a map from disk.
// If the map does not exist, create it and save it back to disk.
// Needs to track world time and game time.
class World {

};
