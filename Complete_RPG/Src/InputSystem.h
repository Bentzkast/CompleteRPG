#pragma once
#include <SDL.h>

enum ButtonState {
	ENone,
	EPressed,
	EReleased,
	EHeld
};

class KeyboardState {
public:
	friend class InputSystem;
	// is it down?
	bool GetKeyValue(SDL_Scancode keycode) const;
	// state of the current key based on prev frame
	ButtonState GetKeyState(SDL_Scancode keycode) const;
private:
	const Uint8* m_currState;
	Uint8 m_prevState[SDL_NUM_SCANCODES];
};

struct InputState {
	KeyboardState Keyboard;
};

class InputSystem{
public:
	
	InputSystem();
	void PrepareForUpdate();

	const InputState& GetState() const { return m_state; }

private:
	InputState m_state;

};