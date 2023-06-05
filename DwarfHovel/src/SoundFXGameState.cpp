#include "SoundFXGameState.h"

#include <string>
#include "Logger.h"
#include "OEM437.h"
#include "math/math.h"
#include "Settings.h"
#include "ui/ui.h"

#define IDB_BUTTON0 0
#define IDB_BUTTON1 1
#define IDB_BUTTON2 2
#define IDB_BUTTON3 3
#define IDB_BUTTON4 4



#include <queue>

const int AMPLITUDE = 28000;
const int FREQUENCY = 4194; // 44100;


#define SAMPLE_RATE 44100

bool lock_samples = false;
void audio_callback(void* userdata, Uint8* stream, int len) {
	auto samples = reinterpret_cast<std::vector<float>*>(userdata);
	if (samples->empty()) {
		SDL_memset(stream, 0, len);
		return;
	}

    auto num_samples = len / sizeof(float);
	auto audio_stream = reinterpret_cast<float*>(stream);

	auto index = 0;
	lock_samples = true;
	while (index < num_samples && !samples->empty()) {
		if (!samples->empty()) {
			auto sample = samples->front();
			samples->erase(samples->begin());
			audio_stream[index] = sample;
		} else {
			audio_stream[index] = 0;
		}
		index++;
	}
	lock_samples = false;
}

SoundFXGameState::SoundFXGameState()
	: GameState() {
	ui->add_child(make_button(IDB_BUTTON0, 0, 0, "#0"));
	ui->add_child(make_button(IDB_BUTTON1, 0, 2, "#1"));
	ui->add_child(make_button(IDB_BUTTON2, 0, 4, "#2"));
	ui->add_child(make_button(IDB_BUTTON3, 0, 6, "#3"));
	ui->add_child(make_button(IDB_BUTTON4, 0, 8, "#4"));

	SDL_AudioSpec desired_spec;
    desired_spec.freq = SAMPLE_RATE; // Sample rate
    desired_spec.format = AUDIO_F32; // Sample format (signed 16-bit)
    desired_spec.channels = 1; // Mono sound
    desired_spec.samples = 2048; // Buffer size (number of samples)
    desired_spec.callback = audio_callback;
	desired_spec.userdata = &samples;

    audio_device = SDL_OpenAudioDevice(nullptr, 0, &desired_spec, nullptr, 0);
    SDL_PauseAudioDevice(audio_device, 0);
}

SoundFXGameState::~SoundFXGameState() {
	LOG_INFO("Closing audio device.");
	SDL_PauseAudioDevice(audio_device, 1);
	SDL_CloseAudioDevice(audio_device);
}

void SoundFXGameState::update(unsigned int delta_time_ms) {
	GameState::update(delta_time_ms);
}

void SoundFXGameState::render(IRenderContext* context, unsigned int delta_time_ms) {
	context->clear(Color(0.1f, 0.1f, 0.3f));

	GameState::render(context, delta_time_ms);
}

void SoundFXGameState::handle_event(SDL_MouseMotionEvent* evt) {
	GameState::handle_event(evt);
}

void SoundFXGameState::handle_event(SDL_KeyboardEvent* evt) {
	if (evt->state == SDL_PRESSED) {
		if (evt->keysym.sym == SDLK_ESCAPE) {
			leave();
		}
	}
	
	GameState::handle_event(evt);
}

float get_decay(float current_time, float total_duration, float decay_duration) {
    float decay_start = total_duration - decay_duration;
    //float decay_factor = (current_time >= decay_start) ? (1.0f - (current_time - decay_start) / decay_duration) : 1.0f;
	//float decay_factor = (current_time >= decay_start) ? std::exp(-(current_time - decay_start) / decay_duration) : 1.0f;
	//float decay_factor = (current_time >= decay_start) ? std::pow(2.0f, -(current_time - decay_start) / decay_duration) : 1.0f;
	float decay_factor = (current_time < decay_start) ? 1.0f : math::lerp(1.0f, 0.0f, (current_time - decay_start) / decay_duration);

	//LOG_INFO("decay_factor: %f", decay_factor);
    return decay_factor;
}

void SoundFXGameState::sine(float volume) {
	const float duration = 1.0f; // Duration of the beep sound in seconds
	const int frequency = 440; // Frequency of the beep sound in Hz

	// Generate the audio buffer for the beep sound
	const int buffer_size = (int)(duration * SAMPLE_RATE);
	float* audio_buffer = new float[buffer_size];
	double angular_frequency = 2.0 * M_PI * frequency; // / SAMPLE_RATE;
	for (int i = 0; i < buffer_size; ++i) {
		float time = (float)i / (float)SAMPLE_RATE;
		float sample = (float)std::sin(angular_frequency * time);
		sample *= volume;
		sample = sample * get_decay(time, duration, 0.5f);
		push_sample(sample);
	}
}

void SoundFXGameState::square(float volume) {
    const float duration = 1; // Duration of the sound in seconds
    const float frequency = 440; // Frequency of the sound in Hz

    // Generate the audio buffer for the sawtooth wave sound.
    const int buffer_size = (int)(duration * SAMPLE_RATE);
	const auto samples_per_cycle = (int)(SAMPLE_RATE / frequency);

    for (int i = 0; i < buffer_size; ++i) {
		float time = (float)i / SAMPLE_RATE;
        bool is_high = (i % samples_per_cycle) < (samples_per_cycle / 2);
		float sample = is_high ? volume : -volume;
		sample = sample * get_decay(time, duration, 0.5f);
        push_sample(sample);
	}
}

void SoundFXGameState::sawtooth(float volume) {
    const int duration = 1; // Duration of the sound in seconds
    const int frequency = 440; // Frequency of the sound in Hz

    const int buffer_size = duration * SAMPLE_RATE;
	const auto samples_per_cycle = SAMPLE_RATE / frequency;

	float current_position = 0.0f;
    for (int i = 0; i < buffer_size; ++i) {
        if (current_position >= samples_per_cycle) {
            current_position = 0.0f;
        }

        float position_in_half_cycle = current_position / samples_per_cycle;
        float amplitude;

		amplitude = math::lerp(-1.0f, 1.0f, (float)current_position / (float)samples_per_cycle);
		amplitude = volume * amplitude;
		push_sample(amplitude);

        current_position += 1.0;
    }
}

void SoundFXGameState::triangle(float volume) {
    const int duration = 1; // Duration of the sound in seconds
    const int frequency = 440; // Frequency of the sound in Hz

    // Generate the audio buffer for the sawtooth wave sound.
    const int buffer_size = duration * SAMPLE_RATE;
	const auto samples_per_half_cycle = SAMPLE_RATE / (2 * frequency);

	bool is_rising = true;
	float current_position = 0.0f;
    for (int i = 0; i < buffer_size; ++i) {
        if (current_position >= samples_per_half_cycle) {
            current_position = 0.0f;
            is_rising = !is_rising;
        }

        float position_in_half_cycle = current_position / samples_per_half_cycle;
        float amplitude;

        if (is_rising) {
            amplitude = math::lerp(-1.0f, 1.0f, (float)current_position / (float)samples_per_half_cycle);
        } else {
            amplitude = math::lerp(1.0f, -1.0f, (float)current_position / (float)samples_per_half_cycle);
        }
		amplitude = volume * amplitude;
		push_sample(amplitude);

        current_position += 1.0;
	}
}

void SoundFXGameState::whitenoise(float volume) {
    const int duration = 1;
    const int buffer_size = duration * SAMPLE_RATE;
    std::random_device rd;
    std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    for (int i = 0; i < buffer_size; ++i) {
		push_sample(volume * dist(gen));
    }
}

void SoundFXGameState::handle_event(SDL_UserEvent* evt) {
	float volume = 0.5f;

	switch (evt->code) {
		case IDB_BUTTON0:
			sine(volume);
			break;
		case IDB_BUTTON1:
			square(volume);
			break;
		case IDB_BUTTON2:
			sawtooth(volume);
			break;
		case IDB_BUTTON3:
			triangle(volume);
			break;
		case IDB_BUTTON4:
			whitenoise(volume);
			break;
	}
}

UIButton* SoundFXGameState::make_button(unsigned int id, unsigned int row, unsigned int column, std::string text) {
	unsigned int padding = 2;
	unsigned int x = (OEM437::CHAR_WIDTH + padding) * column;
	unsigned int y = (OEM437::CHAR_HEIGHT + padding) * row;

	UILabel* lbl = new UILabel(Point2UI(padding, padding), text);
	UIButton* btn = new UIButton(id, Rectangle(Point2UI(x, y), Vector2UI((unsigned int)text.size() * OEM437::CHAR_WIDTH + padding * 2, OEM437::CHAR_HEIGHT + padding * 2)));
	btn->add_child(lbl);
	return btn;
}

void SoundFXGameState::push_sample(float sample) {
	while (lock_samples) ;
	samples.push_back(sample);
}
