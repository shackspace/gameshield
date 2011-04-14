#include "WProgram.h"
#include <GameShield/Input.h>

GameShieldInput& GameShieldInput::getInstance() {
	static GameShieldInput instance;
	return instance;
}

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
	int nJoystickX = analogRead(PIN_JOYSTICK_X);
	int nJoystickY = analogRead(PIN_JOYSTICK_Y);
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