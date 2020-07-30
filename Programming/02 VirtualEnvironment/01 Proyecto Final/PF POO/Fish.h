#pragma once

#include "Model.h"

class fish {

	EDXFramework::Model *pescado;
	float x, y, z, x2, y2, z2, rot, rot2;
	bool right1, up;

	public:

		fish();
		void Draw();
		void anima();
		void aumentax(bool posneg);
		void aumentay(bool posneg);
		void aumentaz(bool posneg);
		void aumentarot(bool posneg);
};