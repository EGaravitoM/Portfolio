#pragma once

#include "Model.h"

class Maleta {

	float rot, x, y, z;
	EDXFramework::Model *MaletaTop, *MaletaBot;

	public:

		Maleta();
		void Draw();
		void Amimaci�n(bool cercasssssssss);
		void aumentax(bool posneg);
		void aumentay(bool posneg);
		void aumentaz(bool posneg);

};