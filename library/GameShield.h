#ifndef GAMESHIELD_H
#define GAMESHIELD_H

class GameShield {
	public:
		static GameShield& getInstance();
		void init();
		
	private:
		// Init required?
		bool m_bReqInit;
		
		// (Copy) constructor
		GameShield();
		GameShield(const GameShield&);
};

#endif /* GAMESHIELD_H */
