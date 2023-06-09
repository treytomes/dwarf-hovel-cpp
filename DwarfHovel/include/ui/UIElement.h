#pragma once

#include <SDL.h>
#include <algorithm>
#include <vector>
#include "IRenderContext.h"
#include "math/math.h"

class UIElement {
public:
	inline UIElement(Rectangle _bounds) : parent_element(nullptr), bounds(_bounds), can_receive_mouse_hover(true), has_mouse_hover(false) {}
	~UIElement();

	void update(unsigned int delta_time_ms);
	void render(IRenderContext* context, unsigned int delta_time_ms);

	bool handle_event(SDL_KeyboardEvent* evt);
	bool handle_event(SDL_MouseMotionEvent* evt);
	bool handle_event(SDL_MouseButtonEvent* evt);
	bool handle_event(SDL_MouseWheelEvent* evt);

	UIElement* add_child(UIElement* child);

	inline static UIElement* get_root() { return root_element; }
	inline static UIElement* get_mouse_hover() { return mouse_hover_element; }
	inline static UIElement* get_mouse_focus() { return mouse_focus_element; }
	inline static UIElement* get_keyboard_focus() { return keyboard_focus_element; }

protected:
	inline void set_bounds(Rectangle _bounds) { bounds = _bounds; }
	inline void set_bounds(unsigned int x, unsigned int y, unsigned int w, unsigned int h) { set_bounds(Rectangle(x, y, w, h)); }
	inline Rectangle get_bounds() { return bounds; }
	bool can_receive_mouse_hover;
	bool has_mouse_hover;

	inline virtual bool inner_handle_event(SDL_KeyboardEvent* evt) { return false; }
	inline virtual bool inner_handle_event(SDL_MouseMotionEvent* evt) { return false; }
	inline virtual bool inner_handle_event(SDL_MouseButtonEvent* evt) { return false; }
	inline virtual bool inner_handle_event(SDL_MouseWheelEvent* evt) { return false; }

	inline virtual void inner_update(unsigned int delta_time_ms) {}
	inline virtual void inner_render(Rectangle bounds, IRenderContext* context, unsigned int delta_time_ms) {}

	inline bool has_child(UIElement* child) {
		return std::find(children.begin(), children.end(), child) != children.end();
	}

	void remove_child(UIElement* child);
	void push_to_back(UIElement* child);
	void pull_to_front(UIElement* child);
	inline bool has_keyboard_focus() { return keyboard_focus_element == this; }
	inline bool has_mouse_focus() { return mouse_focus_element == this; }
	inline bool is_root() { return parent_element == nullptr; }

	inline void acquire_mouse_hover() {
		mouse_hover_element = this;
	}
	
	inline void lose_mouse_hover() {
		if (mouse_hover_element == this) {
			mouse_hover_element = nullptr;
		}
	}
	
	inline void acquire_mouse_focus() {
		mouse_focus_element = this;
	}
	
	inline void lose_mouse_focus() {
		if (mouse_focus_element == this) {
			mouse_focus_element = nullptr;
		}
	}

	inline void acquire_keyboard_focus() {
		keyboard_focus_element = this;
	}
	
	inline void lose_keyboard_focus() {
		if (keyboard_focus_element == this) {
			keyboard_focus_element = nullptr;
		}
	}

private:
	Rectangle get_relative_bounds();

	static UIElement* root_element;
	static UIElement* mouse_hover_element;
	static UIElement* mouse_focus_element;
	static UIElement* keyboard_focus_element;

	UIElement* parent_element;
	std::vector<UIElement*> children;
	Rectangle bounds;
};
