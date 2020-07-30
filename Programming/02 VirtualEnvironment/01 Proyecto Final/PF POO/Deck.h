#ifndef H_DECK
#define H_DECK

#include "Carta.h"

class Deck {
	
	Carta *Decksito;
	friend class GM;
	friend class Scene;
	friend class Jugador;

	public:

		Deck();
		~Deck();
		void ResetDeck();

};
#endif