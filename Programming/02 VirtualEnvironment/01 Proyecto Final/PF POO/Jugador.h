#pragma once
#ifndef H_JUGADOR
#define H_JUGADOR

#include "Carta.h"
#include "Deck.h"
#include <time.h>

class Jugador {

	Carta *Mano[39];
	//Carta **Dedo;
	short puntos, CartaSec;
	bool Victoria;
	static bool Derrota;
	short valorsito;
	char Nombre[10];

public:

	Jugador(Deck &Mazo, char *Nombre);
	~Jugador();
	int tellmenum();
	void Pescar(Deck &Mazo, HWND hWnd);
	void Robar(Jugador *OtherP, short numP, Deck &Mazo, HWND hWnd);
	void Seleccionar_carta();
	void Robado(Jugador *OtherP, short numP);
	void SumarPuntos(short valP, HWND hWnd);
	void ChecaVictoria(HWND hWnd);
	void DefineGanador(HWND hWnd);
	int VerNull();
	void setHandPosition();
	int getStatus(Carta *Check);
	int getPuntaje();
	void calculaprob(short valP, Jugador *Other, Deck &Mazo, HWND hWnd);
	friend void terminajuego();
	void bajamano(short valP);
};

#endif // !H_JUGADOR
