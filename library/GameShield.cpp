#include "WProgram.h"
#include <GameShield.h>

GameShield& GameShield::getInstance() {
	static GameShield instance;
	return instance;
}

GameShield::GameShield() {
	m_bReqInit = true;
}