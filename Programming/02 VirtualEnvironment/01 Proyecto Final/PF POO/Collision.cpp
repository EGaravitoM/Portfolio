#include "Collision.h"

void colición::ChecaCol(float pox, float pox2, float poz, float poz2, double &pcx, double &pcz) {

	if (pox < pcx && pcx < pox2) {
		if (pcz < poz2 && pcz > poz) {
			if (pcz < (poz + poz2) / 2) {
				pcz -= 2;
			}
			if (pcz > (poz + poz2) / 2) {
				pcz += 2;
			}
		}
	}	

	if (poz < pcz && pcz < poz2) {
		if (pcx < pox2 && pcx > pox) {
			if (pcx < (pox + pox2) / 2) {
				pcx -= 2;
			}
			if (pcx > (pox + pox2) / 2) {
				pcx += 2;
			}
		}
	}
	
}
int colición::Proximidad(float pox, float pox2, float poz, float poz2, double &pcx, double &pcz) {

	if (pox < pcx && pcx < pox2) {
		if (pcz < poz2 && pcz > poz) {
			if (pcz < (poz + poz2) / 2) {
				return 1;
			}
			if (pcz >(poz + poz2) / 2) {
				return 1;
			}
		}
	}

	if (poz < pcz && pcz < poz2) {
		if (pcx < pox2 && pcx > pox) {
			if (pcx < (pox + pox2) / 2) {
				return 1;
			}
			if (pcx >(pox + pox2) / 2) {
				return 1;
			}
		}
	}

	return 0;

}