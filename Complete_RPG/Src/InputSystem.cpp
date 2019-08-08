#include "InputSystem.h"
#include <cstring>

bool KeyboardState::GetKeyValue(SDL_Scancode keycode) const {
	return m_currState[keycode] == 1;
}

ButtonState KeyboardState::GetKeyState(SDL_Scancode keycode) const {
	if (m_prevState[keycode] == 0) {
		if (m_currState[keycode] == 0) {
			return ENone;
		}
		else {
			return EPressed;
		}
	}
	else {
		if (m_currState[keycode] == 0) {
			return EReleased;
		}
		else {
			return EHeld;
		}
	}
}

InputSystem::InputSystem() {
	// a
	m_state.Keyboard.m_currState = SDL_GetKeyboardState(NULL);

	memset(m_state.Keyboard.m_prevState, 0, SDL_NUM_SCANCODES);
}

void InputSystem::PrepareForUpdate() {
	memcpy(m_state.Keyboard.m_prevState,
		m_state.Keyboard.m_currState, SDL_NUM_SCANCODES);
}
