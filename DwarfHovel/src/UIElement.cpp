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
	Rectangle b = get_relative_bounds();
	if (!is_root() && !parent_element->get_bounds().intersects(b)) {
		// The element isn't visible, so we're done.
		return;
	}
	inner_render(b, context, delta_time_ms);
	
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
	has_mouse_hover = can_receive_mouse_hover && bounds.contains(evt->x, evt->y);

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
	has_mouse_hover = can_receive_mouse_hover && bounds.contains(evt->x, evt->y);

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

UIElement* UIElement::add_child(UIElement* child) {
	if (has_child(child)) {
		return this;
	}

	if (child->parent_element != nullptr) {
		child->parent_element->remove_child(child);
	}

	children.push_back(child);
	child->parent_element = this;

	return this;
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

Rectangle UIElement::get_relative_bounds() {
	Rectangle my_bounds = get_bounds();
	if (is_root()) {
		return my_bounds;
	}

	Rectangle parent_bounds = parent_element->get_relative_bounds();
	my_bounds.offset(parent_bounds.get_position());

	if (my_bounds.get_right() > parent_bounds.get_right()) {
		my_bounds.set_width(parent_bounds.get_right() - my_bounds.get_left() + 1);
	}
	if (my_bounds.get_bottom() > parent_bounds.get_bottom()) {
		my_bounds.set_height(parent_bounds.get_bottom() - my_bounds.get_top() + 1);
	}
	return my_bounds;
}
