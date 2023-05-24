#pragma once

#include <SDL.h>
#include "IRenderContext.h"
#include "Settings.h"
#include "UIElement.h"

class GameStateManager;

class GameState {
public:
	inline GameState()
		: ui(new UIElement(Rectangle(Point2UI::zero(), Settings::get_instance()->virtual_window_size))) {
	}

	inline ~GameState() {
		parent = nullptr;
		if (ui != nullptr) {
			delete ui;
		}
	}
		
	virtual inline void update(unsigned int delta_time_ms) { ui->update(delta_time_ms); }
	virtual inline void render(IRenderContext* context, unsigned int delta_time_ms) { ui->render(context, delta_time_ms); }
	void enter(GameState* state);
	void leave();
	inline void set_parent(GameStateManager* _parent) { parent = _parent; }

	inline virtual void handle_event(SDL_WindowEvent* evt) {}
	inline virtual void handle_event(SDL_KeyboardEvent* evt) { ui->handle_event(evt); }
	inline virtual void handle_event(SDL_MouseMotionEvent* evt) { ui->handle_event(evt); }
	inline virtual void handle_event(SDL_MouseButtonEvent* evt) { ui->handle_event(evt); }
	inline virtual void handle_event(SDL_MouseWheelEvent* evt) { ui->handle_event(evt); }
	inline virtual void handle_event(SDL_UserEvent* evt) {}

protected:
	GameStateManager* parent;
	UIElement* ui;
};


