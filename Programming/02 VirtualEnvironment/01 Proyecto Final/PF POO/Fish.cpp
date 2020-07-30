#include "Fish.h"

fish::fish(){

	x = 5.6;
	y = 10;
	z = -190;
	x2 = 0;
	y2 = 0;
	z2=10;
	right1 = true;
	up = false;
	rot = 0;
	rot2 = 0;
	pescado = new EDXFramework::Model("Modelos//Finales//pez//fish.obj","Modelos//Finales//pez//fish_texture.bmp",1 );

}

void fish::Draw() {

	glPushMatrix();
	glTranslatef(x,y,z);
	glRotatef(rot,0,1,0);
	glTranslatef(x2, y2, z2);
	glRotatef(rot2, 0, 1, 0);
	pescado->Draw();
	glPopMatrix();

}

void fish::anima() {

	if (x2 > 20) {
		right1 = false;
	}
	if (0 > x2) {
		right1 = true;
	}

	if (right1) {
		x2 += 0.1;
	}
	else {
		x2 -= 0.1;
	}
	if (x2 > 17) {
		up = true;
	}
	if (3 > x2) {
		up = false;
	}

	if (up) {
		z2 += 0.1;
		rot2 = -45;
	}
	else {
		z2 -= 0.1;
		rot2 = 140;

	}

}

void fish::aumentax(bool posneg) {

	if (posneg) {
		x2 += 10;
	}
	else {
		x2 -= 10;
	}

}
void fish::aumentay(bool posneg) {

	if (posneg) {
		y2 += 10;
	}
	else {
		y2 -= 10;
	}

}
void fish::aumentaz(bool posneg) {

	if (posneg) {
		z2 += 10;
	}
	else {
		z2 -= 10;
	}

}
void fish::aumentarot(bool posneg) {

	if (posneg) {
		rot += 1;
	}
	else {
		rot -= 1;
	}

}