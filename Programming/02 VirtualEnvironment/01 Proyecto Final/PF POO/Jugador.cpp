#include "Jugador.h"

bool Jugador::Derrota = true;

Jugador::Jugador(Deck &Mazo, char *Nombre) {

	puntos = 0;
	CartaSec = 0;
	Victoria = false;
	strcpy_s(this->Nombre, Nombre);
	for (short i = 0; i < 39; i++) {
		Mano[i] = NULL;
	}

	for (short i = 0; i < 5; i++) {
		bool continua = true;
		while (continua) {
			srand(time(NULL));
			valorsito = rand() % 52;
			if (!Mazo.Decksito[valorsito].OnHand) {
				Mano[i] = &Mazo.Decksito[valorsito];
				Mazo.Decksito[valorsito].OnHand = true;
				continua = false;
			}
		}
	}
	setHandPosition();

}
Jugador::~Jugador() {


}
void Jugador::Pescar(Deck &Mazo, HWND hWnd) {

	bool continua = true;
	while (continua) {
		srand(time(NULL));
		valorsito = rand() % 52;
		if (!Mazo.Decksito[valorsito].OnHand) {
			for (short i = 0; i < 39; i++) {
				if (Mano[i] == NULL) {
					Mano[i] = &Mazo.Decksito[valorsito];
					Mazo.Decksito[valorsito].OnHand = true;
					continua = false;
					break;
				}
			}
		}
	}

	setHandPosition();
}
void Jugador::Robar(Jugador *OtherP, short valP, Deck &Mazo, HWND hWnd) {
	bool stealme = false;

	for (short i = 0; i < 39; i++) {
		if (OtherP->Mano[i] != NULL) {
			if (OtherP->Mano[i]->Valor == valP) {
				for (short j = 0; j < 39; j++) {
					if (Mano[j] == NULL) {
						Mano[j] = OtherP->Mano[i];
						stealme = true;
						break;
					}
				}
			}
		}
	}
	if (stealme) {
		Victoria = false;
		char message[50] = "";
		strcat(message, this->Nombre);
		strcat(message, " ha robado una carta!!!");
		MessageBox(hWnd, message, "Aviso", MB_OK);
		Robado(OtherP, valP);
		setHandPosition();
		SumarPuntos(valP, hWnd);
	}
	else {
		Victoria = false;
		char message[50] = "";
		strcat(message, this->Nombre);
		strcat(message, " ha pescado una carta!!!");
		MessageBox(hWnd, message, "Aviso", MB_OK);
		Pescar(Mazo, hWnd);
		setHandPosition();
		SumarPuntos(Mazo.Decksito[valorsito].Valor, hWnd);
		
	}


	
	
	
}
void Jugador::Seleccionar_carta() {

	if (Mano[CartaSec] != NULL) {
		Mano[CartaSec]->y -= 2;
	}

	if (CartaSec < 39) {
		CartaSec += 1;
		if (Mano[CartaSec] == NULL) {
			while (Mano[CartaSec] == NULL)
			{
				if (CartaSec < 39) {
					CartaSec += 1;
				}
				else {
					CartaSec = 0;
				}
			}
		}
	}
	else {
		CartaSec = 0;
	}
	if (CartaSec >= 39) {
		CartaSec = 0;
		while (Mano[CartaSec] == NULL) {
			CartaSec += 1;
		}
	}
	Mano[CartaSec]->y += 2;
	//Dedo = &Mano[CartaSec];

}
void Jugador::Robado(Jugador *OtherP, short valP) {

	for (short i = 0; i < 39; i++) {
		if (OtherP->Mano[i] != NULL) {
			if (OtherP->Mano[i]->Valor == valP) {
				OtherP->Mano[i] = NULL;
			}
		}
	}

}
void Jugador::SumarPuntos(short valP, HWND hWnd) {

	short counter = 0;
	for (short i = 0; i < 39; i++) {
		if (Mano[i] != NULL) {
			if (Mano[i]->Valor == valP) {
				counter += 1;
			}
		}
	}

	if (counter == 4) {
		puntos += 1;
		bajamano(valP);
		ChecaVictoria(hWnd);
	}

}

void Jugador::ChecaVictoria(HWND hWnd) {
	if (puntos >= 2) {
		Victoria = true;
		DefineGanador(hWnd);
	}
}

void Jugador::DefineGanador(HWND hWnd) {

	if (Victoria) {

		Victoria = false;
		char vicrotymessage[50] = "";
		strcat(vicrotymessage, this->Nombre);
		strcat(vicrotymessage, " es el ganador!!!");
		MessageBox(hWnd, vicrotymessage, "Aviso", MB_OK);
		terminajuego();
	}
}
int Jugador::tellmenum() {
	return this->Mano[CartaSec]->Valor;
}
int Jugador::VerNull() {

	bool encontrada = false;
	while (!encontrada) {
		srand(time(NULL));
		valorsito = rand() % 39;
		if (Mano[valorsito] != NULL) {
			encontrada = true;
			return Mano[valorsito]->Valor;
		}
	}
}
void Jugador::setHandPosition() {
	for (short i = 0; i < 39; i++) {
		if (strcmp(this->Nombre, "Player1") == 0) {
			if (Mano[i] != NULL) {
				switch (i) {
				case 0:
					Mano[i]->setLugar(1.3, 9, -76);
					break;
				case 1:
					Mano[i]->setLugar(2.4, 9, -76);
					break;
				case 2:
					Mano[i]->setLugar(0.2, 9, -76);
					break;
				case 3:
					Mano[i]->setLugar(3.5, 9, -76);
					break;
				case 4:
					Mano[i]->setLugar(-.9, 9, -76);
					break;
				case 5:
					Mano[i]->setLugar(4.6, 9, -76);
					break;
				case 6:
					Mano[i]->setLugar(-2.0, 9, -76);
					break;
				case 7:
					Mano[i]->setLugar(5.7, 9, -76);
					break;
				case 8:
					Mano[i]->setLugar(-3.1, 9, -76);
					break;
				case 9:
					Mano[i]->setLugar(6.8, 9, -76);
					break;
				case 10:
					Mano[i]->setLugar(-4.2, 9, -76);
					break;
				case 11:
					Mano[i]->setLugar(7.9, 9, -76);
					break;
				case 12:
					Mano[i]->setLugar(-5.3, 9, -76);
					break;
				case 13:
					Mano[i]->setLugar(9, 9, -76);
					break;
				case 14:
					Mano[i]->setLugar(-6.4, 9, -76);
					break;
				case 15:
					Mano[i]->setLugar(10.1, 9, -76);
					break;
				case 16:
					Mano[i]->setLugar(-7.5, 9, -76);
					break;
				case 17:
					Mano[i]->setLugar(11.2, 9, -76);
					break;
				case 18:
					Mano[i]->setLugar(-8.6, 9, -76);
					break;
				case 19:
					Mano[i]->setLugar(12.3, 9, -76);
					break;
				case 20:
					Mano[i]->setLugar(-9.7, 9, -76);
					break;
				case 21:
					Mano[i]->setLugar(13.4, 9, -76);
					break;
				case 22:
					Mano[i]->setLugar(-10.8, 9, -76);
					break;
				case 23:
					Mano[i]->setLugar(14.5, 9, -76);
					break;
				case 24:
					Mano[i]->setLugar(-12, 9, -76);
					break;

				}
			}
		}
		else {
			if (Mano[i] != NULL) {
				switch (i) {
				case 0:
					Mano[i]->setLugar(1.3, 9, -76);
					break;
				case 1:
					Mano[i]->setLugar(2.4, 9, -76);
					break;
				case 2:
					Mano[i]->setLugar(0.2, 9, -76);
					break;
				case 3:
					Mano[i]->setLugar(3.5, 9, -76);
					break;
				case 4:
					Mano[i]->setLugar(-.9, 9, -76);
					break;
				case 5:
					Mano[i]->setLugar(4.6, 9, -76);
					break;
				case 6:
					Mano[i]->setLugar(-2.0, 9, -76);
					break;
				case 7:
					Mano[i]->setLugar(5.7, 9, -76);
					break;
				case 8:
					Mano[i]->setLugar(-3.1, 9, -76);
					break;
				case 9:
					Mano[i]->setLugar(6.8, 9, -76);
					break;
				case 10:
					Mano[i]->setLugar(-4.2, 9, -76);
					break;
				case 11:
					Mano[i]->setLugar(7.9, 9, -76);
					break;
				case 12:
					Mano[i]->setLugar(-5.3, 9, -76);
					break;
				case 13:
					Mano[i]->setLugar(9, 9, -76);
					break;
				case 14:
					Mano[i]->setLugar(-6.4, 9, -76);
					break;
				case 15:
					Mano[i]->setLugar(10.1, 9, -76);
					break;
				case 16:
					Mano[i]->setLugar(-7.5, 9, -76);
					break;
				case 17:
					Mano[i]->setLugar(11.2, 9, -76);
					break;
				case 18:
					Mano[i]->setLugar(-8.6, 9, -76);
					break;
				case 19:
					Mano[i]->setLugar(12.3, 9, -76);
					break;
				case 20:
					Mano[i]->setLugar(-9.7, 9, -76);
					break;
				case 21:
					Mano[i]->setLugar(13.4, 9, -76);
					break;
				case 22:
					Mano[i]->setLugar(-10.8, 9, -76);
					break;
				case 23:
					Mano[i]->setLugar(14.5, 9, -76);
					break;
				case 24:
					Mano[i]->setLugar(-12, 9, -76);
					break;

				}
			}
		}
	}
	Mano[CartaSec]->y += 2;
}
int Jugador::getStatus(Carta *check) {

	for (short i = 0; i < 39; i++) {
		if (Mano[i] == check) {
			return 1;
		}
	}

	return 0;
}

void Jugador::calculaprob(short valP, Jugador *Other, Deck &Mazo, HWND hWnd) {

	float cp = 0, cmia = 0, ccd = 0;

	for (short x = 0; x < 39; x++) {
		if (Mano[x] != NULL) {
			if (Mano[x]->Valor == valP) {
				cp += 1;
			}
		}
	}

	for (short y = 0; y < 39; y++) {
		if (Other->Mano[y] != NULL) {
			cmia += 1;
		}
	}

	for (short z = 0; z < 39; z++) {
		if (Mazo.Decksito[z].OnHand == false) {
			ccd += 1;
		}
	}

	float numcar = 4 - cp;
	char probita[10] = "";
	float prob = 0.0;
	float prob1 = (numcar / cmia);
	float prob2 = (numcar / ccd);
	prob = (prob1*prob2) * 100;
	char message[100] = "";
	strcat(message, "La probabilidad de que obtengas esta carta es del ");
	_itoa(prob, probita, 10);
	strcat(message, probita);
	strcat(message, " porciento");
	MessageBox(hWnd, message, "Aviso", MB_OK);

}

int Jugador::getPuntaje() {
	return puntos;
}
void Jugador::bajamano(short valP) {

	for (short i = 0; i < 39; i++) {
		if (Mano[i] != NULL) {
			if (Mano[i]->Valor == valP) {
				Mano[i]->setLugar(16, 19,-80);
				this->Mano[i]=NULL;
			}
		}
	}

}