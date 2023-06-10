#include "bitmaps.h"
#include "bitmap_templates.h"

#define PLAYER_SKIN_COLOR Color::sepia()
#define PLAYER_EYE_COLOR Color::blue().dark()
#define PLAYER_MOUTH_COLOR Color::red().darkest()

ColoredBitmap bitmaps::mouse_cursor(&bitmap_templates::mouse_cursor, Color::transparent(), Color::black(), Color::white(), Color::transparent());

ColoredBitmap bitmaps::player_north(&bitmap_templates::person_north, Color::transparent(), PLAYER_SKIN_COLOR, PLAYER_MOUTH_COLOR, PLAYER_EYE_COLOR);
ColoredBitmap bitmaps::player_south(&bitmap_templates::person_south, Color::transparent(), PLAYER_SKIN_COLOR, PLAYER_MOUTH_COLOR, PLAYER_EYE_COLOR);
ColoredBitmap bitmaps::player_east(&bitmap_templates::person_east, Color::transparent(), PLAYER_SKIN_COLOR, PLAYER_MOUTH_COLOR, PLAYER_EYE_COLOR);
ColoredBitmap bitmaps::player_west(&bitmap_templates::person_west, Color::transparent(), PLAYER_SKIN_COLOR, PLAYER_MOUTH_COLOR, PLAYER_EYE_COLOR);

ColoredBitmap bitmaps::iron_sword(&bitmap_templates::sword, Color::transparent(), Color::white(), Color::gray().darker(), Color::gray().darkest());

ColoredBitmap bitmaps::bush(&bitmap_templates::asterisk, Color::transparent(), Color::green(), Color::green().darkest(), Color::transparent());
//ColoredBitmap bitmaps::bush(&bitmap_templates::dot, Color::green().darkest().darkest(), Color::green().darkest(), Color::green().darkest().dark(), Color::green().darkest().darker());

ColoredBitmap bitmaps::grass_floor(&bitmap_templates::dot, Color::green().desaturated().darkest(), Color::green().desaturated().darker(), Color::green().desaturated().darker(), Color::green().desaturated().darker().darkest());
ColoredBitmap bitmaps::stone_wall(&bitmap_templates::hashtag, Color::gray().desaturated().darker(), Color::gray().desaturated().darkest(), Color::gray().desaturated().darkest().dark(), Color::transparent());
