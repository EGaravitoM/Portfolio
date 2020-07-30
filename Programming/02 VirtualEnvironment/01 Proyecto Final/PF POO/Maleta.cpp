#include "Maleta.h"

Maleta::Maleta() {

	rot = 0;
	x = 1.49011614e-09;
	y = 37.7;
	z = -10.6;
	MaletaBot = new EDXFramework::Model("Modelos//Finales//SuitCase//Maleta_bot1.obj", "Modelos//Finales//SuitCase//Texture//7.bmp", 1);
	MaletaTop = new EDXFramework::Model("Modelos//Finales//SuitCase//Maleta_top1.obj", "Modelos//Finales//SuitCase//Texture//7.bmp", 1);

}

void Maleta::Draw() {
	glPushMatrix();

	glPushMatrix();
		glTranslatef(0, 37, -10);
		glScalef(0.004, 0.004, 0.004);
		MaletaBot->Draw();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(rot, 1, 0, 0);
		glScalef(0.004, 0.004, 0.004);
		MaletaTop->Draw();
	glPopMatrix();

	glPopMatrix();

}

void Maleta::Amimación(bool cercasssssssss) {

	if (cercasssssssss) {
		if (rot > 0) {
			rot -= 10;
		}
	}
	else {
		if (rot < 120) {
			rot += 10;
		}
	}

}

void Maleta::aumentax(bool posneg) {

	if (posneg) {
		x += 0.1;
	}
	else {
		x -= 0.1;
	}

}
void Maleta::aumentay(bool posneg) {

	if (posneg) {
		y += 0.1;
	}
	else {
		y -= 0.1;
	}

}
void Maleta::aumentaz(bool posneg) {

	if (posneg) {
		z += 0.1;
	}
	else {
		z -= 0.1;
	}

}