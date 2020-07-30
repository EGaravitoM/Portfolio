#ifndef H_CARTA
#define H_CARTA

#include "Model.h"

class Carta {

	char Palo[11];
	short Valor;
	bool OnHand;
	float x, y, z;
	EDXFramework::Model *Cartitawe;
	friend class Deck;
	friend class Scene;
	friend class Jugador;
	friend class GM;

	public:

		Carta(char *palop, short valorp, string modelPath, string texturePath, bool mode);
		~Carta();
		void setLugar(float xP, float yP, float zP);
};
#endif