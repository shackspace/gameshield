#ifndef GAMESHIELD_H
#define GAMESHIELD_H

#include "utility/GameShieldInput.h"

class GameShield {
	public:
		GameShield();
		void init();
		GameShieldInput getInput();
		
	private:
		// Init required?
		bool m_bReqInit;
		
		// Input
		GameShieldInput m_oInput;
};

#endif /* GAMESHIELD_H */
