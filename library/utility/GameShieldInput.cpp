#include "WProgram.h"
#include "GameShieldInput.h"

GameShieldInput::GameShieldInput() {
	m_bReqInit = true;
	
	// Joystick states
	m_nCurrentJoystickValueX = 0;
	m_nCurrentJoystickValueY = 0;
	m_nLastJoystickValueX = 0;
	m_nLastJoystickValueY = 0;
	
	// Button states
	bool bButtonInit[6] = {false, false, false, false, false, false};
	memcpy(m_bCurrentButtonStates, bButtonInit, sizeof(bButtonInit));
	memcpy(m_bLastButtonStates, bButtonInit, sizeof(bButtonInit));
}

void GameShieldInput::init() {
	m_bReqInit = false;
	
	// Set pins to INPUT mode
	pinMode(PIN_BTN_START, 	INPUT);
	pinMode(PIN_BTN_SELECT, INPUT);	
	pinMode(PIN_BTN_UP, 	INPUT);
	pinMode(PIN_BTN_DOWN, 	INPUT);
	pinMode(PIN_BTN_LEFT, 	INPUT);
	pinMode(PIN_BTN_RIGHT, 	INPUT);
	
	// Set pull-up resistors
	digitalWrite(PIN_BTN_START, 	HIGH);
	digitalWrite(PIN_BTN_SELECT, 	HIGH);
	digitalWrite(PIN_BTN_UP, 		HIGH);
	digitalWrite(PIN_BTN_DOWN, 		HIGH);
	digitalWrite(PIN_BTN_LEFT, 		HIGH);
	digitalWrite(PIN_BTN_RIGHT, 	HIGH);
}

void GameShieldInput::update() {
	if (m_bReqInit)
		init();
	
	// Copy current values to old values
	memcpy(m_bLastButtonStates, m_bCurrentButtonStates, sizeof(m_bCurrentButtonStates));
	m_nLastJoystickValueX = m_nCurrentJoystickValueX;
	m_nLastJoystickValueY = m_nCurrentJoystickValueY;
	
	// Read buttons
	m_bCurrentButtonStates[BUTTON_START] = (digitalRead(PIN_BTN_START) == LOW);
	m_bCurrentButtonStates[BUTTON_SELECT] = (digitalRead(PIN_BTN_SELECT) == LOW);
	m_bCurrentButtonStates[BUTTON_UP] = (digitalRead(PIN_BTN_UP) == LOW);
	m_bCurrentButtonStates[BUTTON_DOWN] = (digitalRead(PIN_BTN_DOWN) == LOW);
	m_bCurrentButtonStates[BUTTON_LEFT] = (digitalRead(PIN_BTN_LEFT) == LOW);
	m_bCurrentButtonStates[BUTTON_RIGHT] = (digitalRead(PIN_BTN_RIGHT) == LOW);
	
	// Read joystick
	long nJoystickX = analogRead(PIN_JOYSTICK_X);
	long nJoystickY = analogRead(PIN_JOYSTICK_Y);
	
	// Calculating Joystick value between -127 and 128
	m_nCurrentJoystickValueX = (255 * ((100 * (nJoystickX - JOYSTICK_X_MIN)) / (JOYSTICK_X_MAX - JOYSTICK_X_MIN))) / 100 - 128;
	m_nCurrentJoystickValueY = (255 * ((100 * (nJoystickY - JOYSTICK_Y_MIN)) / (JOYSTICK_Y_MAX - JOYSTICK_Y_MIN))) / 100 - 128;
}

bool GameShieldInput::isButtonPressed(int nButtonId) {
	return m_bCurrentButtonStates[nButtonId];
}

bool GameShieldInput::isButtonReleased(int nButtonId) {
	return !m_bCurrentButtonStates[nButtonId];
}

bool GameShieldInput::wasButtonPressed(int nButtonId) {
	return (m_bCurrentButtonStates[nButtonId] && !m_bLastButtonStates[nButtonId]);
}

bool GameShieldInput::wasButtonReleased(int nButtonId) {
	return (!m_bCurrentButtonStates[nButtonId] && m_bLastButtonStates[nButtonId]);
}

int GameShieldInput::getJoystickValueX() {
	return m_nCurrentJoystickValueX;
}

int GameShieldInput::getJoystickValueY() {
	return m_nCurrentJoystickValueY;
}

bool GameShieldInput::isJoystickLeft() {
	return (m_nCurrentJoystickValueX <= -64);
}

bool GameShieldInput::isJoystickRight() {
	return (m_nCurrentJoystickValueX >= 64);
}

bool GameShieldInput::isJoystickUp() {
	return (m_nCurrentJoystickValueY >= 64);
}

bool GameShieldInput::isJoystickDown() {
	return (m_nCurrentJoystickValueY <= -64);
}

bool GameShieldInput::wasJoystickMovedLeft() {
	return (m_nCurrentJoystickValueX < m_nLastJoystickValueX);
}

bool GameShieldInput::wasJoystickMovedRight() {
	return (m_nCurrentJoystickValueX > m_nLastJoystickValueX);
}

bool GameShieldInput::wasJoystickMovedUp() {
	return (m_nCurrentJoystickValueY > m_nLastJoystickValueY);
}

bool GameShieldInput::wasJoystickMovedDown() {
	return (m_nCurrentJoystickValueY < m_nLastJoystickValueY);
}