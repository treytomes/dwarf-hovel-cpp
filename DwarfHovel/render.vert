#version 330

in vec2 a_position;
out vec2 v_texcoord;
uniform ivec2 actual_screen_size;

#define SCREEN_WIDTH 256.0
#define SCREEN_HEIGHT 224.0 // SNES aspect ratio 8:7

void main() {
    float aspectRatio = SCREEN_WIDTH / SCREEN_HEIGHT;
    float heightFromWidth = actual_screen_size.x / aspectRatio;
    float widthFromHeight = actual_screen_size.y * aspectRatio;

    float tx = a_position.x;
    float ty = a_position.y;

	// This will maintain the desired aspect ratio, adding black bars to the top/bottom or left/right as needed.

    if (actual_screen_size.x > widthFromHeight) {
        if (tx > 0) {
            tx -= (actual_screen_size.x - widthFromHeight) / actual_screen_size.x;
        } else { 
            tx += (actual_screen_size.x - widthFromHeight) / actual_screen_size.x;
        }
    }
    if (actual_screen_size.y > heightFromWidth) {
        if (ty > 0) {
            ty -= (actual_screen_size.y - heightFromWidth) / actual_screen_size.y;
        } else { 
            ty += (actual_screen_size.y - heightFromWidth) / actual_screen_size.y;
        }
    }

    gl_Position = vec4(tx, ty, 0, 1);

    // This bit will flip the Y and put (0, 0) in the top-left corner.  Like old-school.
    v_texcoord = a_position.xy * vec2(0.5, -0.5) + 0.5; 
    //v_texcoord = a_position.xy;
}
