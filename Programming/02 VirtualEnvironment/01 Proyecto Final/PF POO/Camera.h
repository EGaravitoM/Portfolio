#ifndef __Camera
#define __Camera

#include "VectorRR.h"
#include <math.h>


#define radio (15)
#define DEG2RAD (3.141592/180)


class Camera : public VectorRR
{
public:
	VectorRR posc, dirc;
	GLdouble px, py, pz, dx, dy, dz, ux, uy, uz;
	int camind = 0;
	float ang;

	Camera()
	{
	}

	/*void CamaraUpdate()
	{
		gluLookAt(posc.X, posc.Y + 10, posc.Z - 10,
			dirc.X, dirc.Y + 10, dirc.Z,
			0, 1, 0);
	}*/

	void cameraInitialize()
	{
		ang = -90;
		px = 0, py = 25, pz = 0, dy = 25;
		dx = px + cos(ang*DEG2RAD)*radio;
		dz = pz + sin(ang*DEG2RAD)*radio;
		ux = 0, uy = 1, uz = 0;
		gluLookAt(px, py, pz, dx, dy, dz, ux, uy, uz);
	}

	void camaraJuego() {

		px = 1.7646924413059484e-05;
		py = 29.200000762939453;
		pz = -53.999999999997115;
		dy = 28;
		dx = 2.2548847861131558e-05;
		dz = -68.999999999996319;
		ang = -90;


	}

	void cameraUpdate()
	{

		dx = px + cos(ang*DEG2RAD)*radio;
		dz = pz + sin(ang*DEG2RAD)*radio;
		

		gluLookAt(px, py, pz, dx, dy, dz, ux, uy, uz);
	}

	void moveLeft()
	{

		px = px + (2 * cos((ang - 90)*DEG2RAD));
		pz = pz + (2 * sin((ang - 90)*DEG2RAD));

	}

	void moveRight()
	{

		px = px - (2 * cos((ang - 90)*DEG2RAD));
		pz = pz - (2 * sin((ang - 90)*DEG2RAD));

	}

	void moveForward()
	{

		px = px + (2 * cos(ang*DEG2RAD));
		pz = pz + (2 * sin(ang*DEG2RAD));

	}

	void moveBackward()
	{

		px = px - (2 * cos(ang*DEG2RAD));
		pz = pz - (2 * sin(ang*DEG2RAD));
		
	}

	void turnRight()
	{
		ang += 5;

	}

	void turnLeft()
	{
		ang -= 5;

	}

	void turnUp()
	{
		if (dy < 50 + py)
		{
			dy += 1;
		}
	}

	void turnDown()
	{
		if (dy > -50 + py)
		{
			dy -= 1;
		}
	}


};
#endif