#include "Cubetoooooooo.h"

Cubeta::Cubeta() {

	rot = 0;
	x = 7.8;
	y = 29.5;
	z = -32.4;
	Cubetin = new EDXFramework::Model("Modelos//Finales//OldBucket//OldBucket.obj", "Modelos//Finales//OldBucket//Inside_Specular.bmp.bmp", 1);

}

void Cubeta::Draw() {

		glPushMatrix();
			glTranslatef(x, y, z);
			glRotatef(rot, 0, 0, 1);
			glScalef(0.004, 0.004, 0.004);
			Cubetin->Draw();
		glPopMatrix();


}

void Cubeta::Amimación(bool cerca){

	if (cerca) {
		if (rot <= 84) {
			rot += 17;
		}
		
		if (y > 25.6) {
			if (x < 5.5) {
				y -= 0.78;
			}
		}
		if (x > 5.5) {
			x -= 1.5;
		}
	}
}

void Cubeta::aumentax(bool posneg) {

	if (posneg) {
		x += 0.1;
	}
	else {
		x -= 0.1;
	}

}
void Cubeta::aumentay(bool posneg) {

	if (posneg) {
		y += 0.1;
	}
	else {
		y -= 0.1;
	}

}
void Cubeta::aumentaz(bool posneg) {

	if (posneg) {
		z += 0.1;
	}
	else {
		z -= 0.1;
	}

}
void Cubeta::aumentarot(bool posneg) {

	if (posneg) {
		rot += 1;
	}
	else {
		rot -= 1;
	}

}