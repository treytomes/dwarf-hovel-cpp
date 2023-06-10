#include <functional>
#include <map>

class MapTile;

namespace map_tiles {
	extern std::map<unsigned int, MapTile*> data;
	extern MapTile grass_floor;
	extern MapTile stone_wall;

	inline MapTile* get_by_id(unsigned int id) {
		if (data.count(id) < 1) {
			return nullptr;
		}
		return data[id];
	}

	void register_tile(MapTile* tile);
}
