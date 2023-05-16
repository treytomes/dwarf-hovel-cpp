#version 330

// SNES aspect ratio 8:7
#define SCREEN_WIDTH 256.0
#define SCREEN_HEIGHT 224.0

#define SCREEN_SIZE vec2(SCREEN_WIDTH, SCREEN_HEIGHT)
#define SCREEN_MAX_X (SCREEN_WIDTH - 1.0)
#define SCREEN_MAX_Y (SCREEN_HEIGHT - 1.0)
#define SCREEN_MIN_X 0
#define SCREEN_MIN_Y 0

layout(location = 0) out vec4 color;
in vec2 v_texcoord;
uniform ivec2 actual_screen_size;
uniform sampler2D render_texture;
uniform int time;

vec2 get_scale() {
	return vec2(1,1); //actual_screen_size / SCREEN_SIZE;
}

vec4 get_color(vec2 pos) {
	return texture(render_texture, pos);
}

vec4 get_color(float x, float y) {
	return get_color(vec2(x, y));
}

vec4 bloom(vec2 pos, vec4 color) {
	#define GLOW_FACTOR 0.9
	#define ORIGIN_WEIGHT 0.1

	float dx = 1.0 / SCREEN_WIDTH / 2.0;
	float dy = 1.0 / SCREEN_HEIGHT / 2.0;
	vec4 color0 = get_color(pos.x +0.0, pos.y +0.0);
	vec4 color1 = get_color(pos.x - dx, pos.y - dy);
	vec4 color2 = get_color(pos.x +0.0, pos.y - dy);
	vec4 color3 = get_color(pos.x + dx, pos.y - dy);
	vec4 color4 = get_color(pos.x - dx, pos.y +0.0);
	vec4 color5 = get_color(pos.x + dx, pos.y +0.0);
	vec4 color6 = get_color(pos.x - dx, pos.y + dy);
	vec4 color7 = get_color(pos.x +0.0, pos.y + dy);
	vec4 color8 = get_color(pos.x + dx, pos.y + dy);

	color = (color + color0 + color1 + color2 + color3 + color4 + color5 + color6 + color7 + color8) / 9.0 * (1.0 - ORIGIN_WEIGHT) + color * (ORIGIN_WEIGHT + GLOW_FACTOR);
	return color;
}

vec4 vignette_intensity(vec2 pos) {
	#define VIGNETTE_OPACITY 0.6
	#define VIGNETTE_ROUNDNESS 2.0

	pos *= get_scale();

	float intensity = pos.x * pos.y * (1.0 - pos.x) * (1.0 - pos.y);
	return vec4(vec3(clamp(pow((actual_screen_size.x / VIGNETTE_ROUNDNESS) * intensity, VIGNETTE_OPACITY), 0.0, 1.0)), 1.0);
}

/**
 * Returns accurate MOD when arguments are approximate integers.
 */
float mod_i(float a, float b) {
	float m = a - floor((a + 0.5) / b) * b;
	return floor(m + 0.5);
}

vec4 scanlines(vec2 pos, vec4 color) {
	// Static lines.
	#define SPEED 1024.0
	//#define SPEED 4096.0
	float seconds = time / SPEED;
	float y = (pos.y + seconds) * SCREEN_HEIGHT;

	color *= (mod_i(y, 2.0) < 0.001) ? 0.75 : 1.0;

	color.a = 1.0;

	return color;
}

/**
 * Vignette inspired by: https://babylonjs.medium.com/retro-crt-shader-a-post-processing-effect-study-1cb3f783afbc
 */
vec2 curve_remap_uv(vec2 pos) {
	#define CURVATURE vec2(4.0, 4.0)

    // As we near the edge of our screen apply greater distortion using a cubic function.
    pos = pos * 2.0 - 1.0;
    vec2 offset = abs(pos.yx) / vec2(CURVATURE.x, CURVATURE.y);
    pos = pos + pos * offset * offset;
    pos = pos * 0.5 + 0.5;
    return pos;
}

void main() {
	vec2 pos = v_texcoord;
	
	pos = curve_remap_uv(pos);

	if (pos.x < 0 || pos.x > 1.0 || pos.y < 0 || pos.y > 1) {
		color = vec4(0, 0, 0, 1);
		return;
	}

	pos /= get_scale();

    color = get_color(pos);
	color = scanlines(pos, color);
	color = bloom(pos, color);
	color *= vignette_intensity(pos);
}
