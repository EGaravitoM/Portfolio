#include "Carta.h"

Carta::Carta(char *palop, short valorp, string modelPath, string texturePath, bool mode) {
	
	strcpy_s(this->Palo, palop);
	this->Valor = valorp;
	this->OnHand = false;
	this->Cartitawe = new EDXFramework::Model(modelPath, texturePath, mode);
	this->x = -11;
	this->y = 17;
	this->z = -80;

	}
Carta::~Carta() {
	delete this->Cartitawe;
	}

void Carta::setLugar(float xP, float yP, float zP) {

	this->x = xP;
	this->y = yP;
	this->z = zP;

}