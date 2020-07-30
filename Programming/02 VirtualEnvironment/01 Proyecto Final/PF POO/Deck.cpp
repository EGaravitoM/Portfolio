#include "Deck.h"

Deck::Deck() {

	this->Decksito = new Carta[52]{
		Carta("Picas",0,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//1.bmp", 1),
		Carta("Picas",1,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//2.bmp", 1),
		Carta("Picas",2,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//3.bmp", 1),
		Carta("Picas",3,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//4.bmp", 1),
		Carta("Picas",4,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//5.bmp", 1),
		Carta("Picas",5,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//6.bmp", 1),
		Carta("Picas",6,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//7.bmp", 1),
		Carta("Picas",7,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//8.bmp", 1),
		Carta("Picas",8,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//9.bmp", 1),
		Carta("Picas",9,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//10.bmp", 1),
		Carta("Picas",10,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//11.bmp", 1),
		Carta("Picas",11,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//12.bmp", 1),
		Carta("Picas",12,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//13.bmp", 1),
		Carta("Corazones",0,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//1.bmp", 1),
		Carta("Corazones",1,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//2.bmp", 1),
		Carta("Corazones",2,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//3.bmp", 1),
		Carta("Corazones",3,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//4.bmp", 1),
		Carta("Corazones",4,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//5.bmp", 1),
		Carta("Corazones",5,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//6.bmp", 1),
		Carta("Corazones",6,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//7.bmp", 1),
		Carta("Corazones",7,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//8.bmp", 1),
		Carta("Corazones",8,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//9.bmp", 1),
		Carta("Corazones",9,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//10.bmp", 1),
		Carta("Corazones",10,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//11.bmp", 1),
		Carta("Corazones",11,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//12.bmp", 1),
		Carta("Corazones",12,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//13.bmp", 1),
		Carta("Treboles",0,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//1.bmp", 1),
		Carta("Treboles",1,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//2.bmp", 1),
		Carta("Treboles",2,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//3.bmp", 1),
		Carta("Treboles",3,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//4.bmp", 1),
		Carta("Treboles",4,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//5.bmp", 1),
		Carta("Treboles",5,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//6.bmp", 1),
		Carta("Treboles",6,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//7.bmp", 1),
		Carta("Treboles",7,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//8.bmp", 1),
		Carta("Treboles",8,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//9.bmp", 1),
		Carta("Treboles",9,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//10.bmp", 1),
		Carta("Treboles",10,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//11.bmp", 1),
		Carta("Treboles",11,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//12.bmp", 1),
		Carta("Treboles",12,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//13.bmp", 1),
		Carta("Diamantes",0,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//1.bmp", 1),
		Carta("Diamantes",1,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//2.bmp", 1),
		Carta("Diamantes",2,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//3.bmp", 1),
		Carta("Diamantes",3,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//4.bmp", 1),
		Carta("Diamantes",4,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//5.bmp", 1),
		Carta("Diamantes",5,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//6.bmp", 1),
		Carta("Diamantes",6,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//7.bmp", 1),
		Carta("Diamantes",7,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//8.bmp", 1),
		Carta("Diamantes",8,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//9.bmp", 1),
		Carta("Diamantes",9,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//10.bmp", 1),
		Carta("Diamantes",10,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//11.bmp", 1),
		Carta("Diamantes",11,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//12.bmp", 1),
		Carta("Diamantes",12,"Modelos//Finales//Cardmodel//Card//Card2.obj","Modelos//Finales//Cardmodel//Card//Texturas//13.bmp", 1)
	};
}
Deck::~Deck() {

	delete[] this->Decksito;

}
void Deck::ResetDeck() {

	for (short i = 0; i < 52; i++) {
		Decksito[i].OnHand = false;
		Decksito[i].x = -4;
		Decksito[i].y = 17;
		Decksito[i].z = -80;
	}

}