#include "SoundFXGameState.h"

#include <string>
#include "Logger.h"
#include "OEM437.h"
#include "Point2UI.h"
#include "Settings.h"
#include "UIElement.h"
#include "UILabel.h"
#include "UIButton.h"
#include "Vector2UI.h"

#define IDB_BUTTON0 0
#define IDB_BUTTON1 1
#define IDB_BUTTON2 2
#define IDB_BUTTON3 3



#include <queue>

const int AMPLITUDE = 28000;
const int FREQUENCY = 44100;

struct BeepObject {
    double freq;
    int samplesLeft;
};

class Beeper {
private:
    double v;
    std::queue<BeepObject> beeps;
public:
    Beeper();
    ~Beeper();
    void beep(double freq, int duration);
    void generateSamples(Sint16 *stream, int length);
    void wait();
};

void audio_callback(void*, Uint8*, int);

Beeper::Beeper() {
    SDL_AudioSpec desiredSpec;

    desiredSpec.freq = FREQUENCY;
    desiredSpec.format = AUDIO_S16SYS;
    desiredSpec.channels = 1;
    desiredSpec.samples = 2048;
    desiredSpec.callback = audio_callback;
    desiredSpec.userdata = this;

    SDL_AudioSpec obtainedSpec;

    // you might want to look for errors here
    SDL_OpenAudio(&desiredSpec, &obtainedSpec);

    // start play audio
    SDL_PauseAudio(0);
}

Beeper::~Beeper() {
    SDL_CloseAudio();
}

void Beeper::generateSamples(Sint16 *stream, int length) {
    int i = 0;
    while (i < length) {

        if (beeps.empty()) {
            while (i < length) {
                stream[i] = 0;
                i++;
            }
            return;
        }
        BeepObject& bo = beeps.front();

        int samplesToDo = std::min(i + bo.samplesLeft, length);
        bo.samplesLeft -= samplesToDo - i;

        while (i < samplesToDo) {
            stream[i] = AMPLITUDE * std::sin(v * 2 * M_PI / FREQUENCY);
            i++;
            v += bo.freq;
        }

        if (bo.samplesLeft == 0) {
            beeps.pop();
        }
    }
}

void Beeper::beep(double freq, int duration) {
    BeepObject bo;
    bo.freq = freq;
    bo.samplesLeft = duration * FREQUENCY / 1000;

    SDL_LockAudio();
    beeps.push(bo);
    SDL_UnlockAudio();
}

void Beeper::wait() {
    unsigned int size;
    do {
        SDL_Delay(20);
        SDL_LockAudio();
        size = (unsigned int)beeps.size();
        SDL_UnlockAudio();
    } while (size > 0);

}

void audio_callback(void *_beeper, Uint8 *_stream, int _length) {
    Sint16 *stream = (Sint16*) _stream;
    int length = _length / 2;
    Beeper* beeper = (Beeper*) _beeper;

    beeper->generateSamples(stream, length);
}


////////////////////////////////////////

SoundFXGameState::SoundFXGameState()
	: GameState() {
	ui->add_child(make_button(IDB_BUTTON0, 0, 0, "#0"));
	ui->add_child(make_button(IDB_BUTTON1, 0, 2, "#1"));
	ui->add_child(make_button(IDB_BUTTON2, 0, 4, "#2"));
	ui->add_child(make_button(IDB_BUTTON3, 0, 6, "#3"));
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

void SoundFXGameState::handle_event(SDL_UserEvent* evt) {
	int duration;
	double Hz;
	Beeper b;

	switch (evt->code) {
		case IDB_BUTTON0:
		    duration = 1000;
			Hz = 440;
			b.beep(Hz, duration);
			b.wait();
			LOG_INFO("BEEP!");
			break;
		case IDB_BUTTON1:
			break;
		case IDB_BUTTON2:
			break;
		case IDB_BUTTON3:
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
