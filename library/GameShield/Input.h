#ifndef INPUT_H
#define INPUT_H

#include "WProgram.h"

// Joystick Axis
#define PIN_JOYSTICK_X 1	// A1
#define PIN_JOYSTICK_Y 0	// A0

// Button Pins
#define PIN_BTN_START 	A2
#define PIN_BTN_SELECT	A3
#define PIN_BTN_UP 		3	// D3
#define PIN_BTN_DOWN 	A5
#define PIN_BTN_LEFT 	4	// D4
#define PIN_BTN_RIGHT 	2	// D2

// Button IDs
#define BUTTON_START 	0
#define BUTTON_SELECT 	1
#define BUTTON_UP 		2
#define BUTTON_DOWN 	3
#define BUTTON_LEFT 	4
#define BUTTON_RIGHT 	5

// Joystick calibration
#define JOYSTICK_X_MIN	0
#define JOYSTICK_X_MAX	1023
#define JOYSTICK_Y_MIN	70
#define JOYSTICK_Y_MAX	950	

class GameShieldInput {
	public:
		static GameShieldInput& getInstance();
		void init();
		void update();
		
		// Getter for button states
		bool isButtonPressed(int nButtonId);
		bool isButtonReleased(int nButtonId);
		bool wasButtonPressed(int nButtonId);
		bool wasButtonReleased(int nButtonId);
		
		// Getter for joystick values
		int getJoystickValueX();
		int getJoystickValueY();
		bool isJoystickLeft();
		bool isJoystickRight();
		bool isJoystickUp();
		bool isJoystickDown();
		bool wasJoystickMovedLeft();
		bool wasJoystickMovedRight();
		bool wasJoystickMovedUp();
		bool wasJoystickMovedDown();
		
	private:
		// Init required?
		bool m_bReqInit;
		
		// Button states
		bool m_bCurrentButtonStates[6];
		bool m_bLastButtonStates[6];
		
		// Joystick states
		int m_nCurrentJoystickValueX;
		int m_nCurrentJoystickValueY;
		int m_nLastJoystickValueX;
		int m_nLastJoystickValueY;	
		
		// (Copy) constructor
		GameShieldInput();
		GameShieldInput(const GameShieldInput&);
};

#endif /* INPUT_H */