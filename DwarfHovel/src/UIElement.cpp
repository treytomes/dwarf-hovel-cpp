#include "UIElement.h"
#include "Logger.h"

UIElement* UIElement::mouse_hover_element = nullptr;
UIElement* UIElement::mouse_focus_element = nullptr;
UIElement* UIElement::keyboard_focus_element = nullptr;

UIElement::~UIElement() {
	while (!children.empty()) {
		UIElement* child = children.back();
		children.pop_back();
		delete child;
	}
}

void UIElement::update(unsigned int delta_time_ms) {
	inner_update(delta_time_ms);

	for (auto iter = children.begin(); iter != children.end(); iter++) {
		UIElement* child = *iter;
		child->update(delta_time_ms);
	}
}

void UIElement::render(IRenderContext* context, unsigned int delta_time_ms) {
	inner_render(context, delta_time_ms);
	
	for (auto iter = children.begin(); iter != children.end(); iter++) {
		UIElement* child = *iter;
		child->render(context, delta_time_ms);
	}
}

bool UIElement::handle_event(SDL_KeyboardEvent* evt) {
	if (!has_keyboard_focus()) {
		return false;
	}

	if (is_root()) {
		UIElement* focus = get_keyboard_focus();
		if (focus != nullptr) {
			bool result = focus->handle_event(evt);
			if (result) {
				return true;
			}
		}
	}
	
	for (auto iter = children.rbegin(); iter != children.rend(); iter++) {
		UIElement* child = *iter;
		bool result = child->handle_event(evt);
		if (result) { return true; }
	}

	return inner_handle_event(evt);
}

bool UIElement::handle_event(SDL_MouseMotionEvent* evt) {
	has_mouse_hover = bounds.contains(evt->x, evt->y);

	if (!has_mouse_focus() && !has_mouse_hover && !is_root()) {
		return false;
	}
	
	if (is_root()) {
		UIElement* focus = get_mouse_focus();
		if (focus != nullptr) {
			bool result = focus->handle_event(evt);
			if (result) {
				return true;
			}
		}
	}

	for (auto iter = children.rbegin(); iter != children.rend(); iter++) {
		UIElement* child = *iter;
		bool result = child->handle_event(evt);
		if (result) { return true; }
	}

	return inner_handle_event(evt);
}

bool UIElement::handle_event(SDL_MouseButtonEvent* evt) {
	has_mouse_hover = bounds.contains(evt->x, evt->y);

	if (!has_mouse_focus() && !has_mouse_hover && !is_root()) {
		return false;
	}
	
	if (is_root()) {
		UIElement* focus = get_mouse_focus();
		if (focus != nullptr) {
			bool result = focus->handle_event(evt);
			if (result) {
				return true;
			}
		}
	}
	
	for (auto iter = children.rbegin(); iter != children.rend(); iter++) {
		UIElement* child = *iter;
		bool result = child->handle_event(evt);
		if (result) { return true; }
	}

	return inner_handle_event(evt);
}

bool UIElement::handle_event(SDL_MouseWheelEvent* evt) {
	if (!has_mouse_focus() && !has_mouse_hover && !is_root()) {
		return false;
	}
	
	if (is_root()) {
		UIElement* focus = get_mouse_focus();
		if (focus != nullptr) {
			bool result = focus->handle_event(evt);
			if (result) {
				return true;
			}
		}
	}

	for (auto iter = children.rbegin(); iter != children.rend(); iter++) {
		UIElement* child = *iter;
		bool result = child->handle_event(evt);
		if (result) { return true; }
	}

	return inner_handle_event(evt);
}

void UIElement::add_child(UIElement* child) {
	if (has_child(child)) {
		return;
	}

	if (child->parent_element != nullptr) {
		child->parent_element->remove_child(child);
	}

	children.push_back(child);
	child->parent_element = this;
}

void UIElement::remove_child(UIElement* child) {
	if (!has_child(child)) {
		return;
	}

	children.erase(std::remove(children.begin(), children.end(), child));
	child->parent_element = nullptr;
	delete child;
}

void UIElement::push_to_back(UIElement* child) {
	if (!has_child(child)) {
		return;
	}

	children.erase(std::remove(children.begin(), children.end(), this));
	children.insert(children.begin(), this);
}

void UIElement::pull_to_front(UIElement* child) {
	if (!has_child(child)) {
		return;
	}

	children.erase(std::remove(children.begin(), children.end(), this));
	children.push_back(this);
}