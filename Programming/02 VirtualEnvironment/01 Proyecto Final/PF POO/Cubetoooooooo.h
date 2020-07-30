#pragma once

#include "Model.h"

class Cubeta {

	float rot, x, y, z;
	EDXFramework::Model *Cubetin;

public:

	Cubeta();
	void Draw();
	void Amimación(bool cerca);
	void aumentax(bool posneg);
	void aumentay(bool posneg);
	void aumentaz(bool posneg);
	void aumentarot(bool posneg);

};