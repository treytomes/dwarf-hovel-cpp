#pragma once

#include <string>
#include <vector>
#include <SDL.h>
#include "GameState.h"
#include "IRenderContext.h"
#include "UIButton.h"

class SoundFXGameState : public GameState {
public:
	SoundFXGameState();
	~SoundFXGameState();

	void update(unsigned int delta_time_ms);
	void render(IRenderContext* context, unsigned int delta_time_ms);
	void handle_event(SDL_KeyboardEvent* evt);
	void handle_event(SDL_MouseMotionEvent* evt);
	void handle_event(SDL_UserEvent* evt);

private:
	SDL_AudioDeviceID audio_device;
	std::vector<Sint16> samples;

	UIButton* make_button(unsigned int id, unsigned int row, unsigned int column, std::string text);
	void sine(float volume);
	void square(float volume);
	void triangle(float volume);
	void sawtooth(float volume);
	void whitenoise(float volume);
	void push_sample(Sint16 sample);
};
