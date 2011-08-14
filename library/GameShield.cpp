#include "GameShield.h"
#include "WProgram.h"

GameShield::GameShield() {
	m_bReqInit = true;
}

void GameShield::init() {
	m_bReqInit = false;
	m_oInput.init();
}

GameShieldInput GameShield::getInput() {
	if (m_bReqInit)
		init();
		
	return m_oInput;
}