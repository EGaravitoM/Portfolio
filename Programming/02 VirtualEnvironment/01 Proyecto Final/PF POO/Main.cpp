#include<Windows.h>
#include <gl\glew.h>
#include <gl\GLU.h>
#include <gl\GL.h>
#include "Scene.h"
#include "Jugador.h"
#include <time.h>
#include "GamePadRR.h"
#include "Collision.h"
#pragma comment (lib, "glew32.lib") 
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib") 

#define Timer1 100
#define Timer2 101
#define DZ 11000

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void DefPixelFormat(HDC hDC);

UINT timer1, timer2;
HDC hContextoVentana;
Scene *scene;
GamePadRR *gamPad;
bool renderiza = false;
bool juego = false;
Jugador *Player1, *IA;
colición chocan;
char puntitos[2] = "", Puntaje[60] = "";

enum {
	Numpad = 0x60, Numpad1, Numpad2, Numpad3, Numpad4, Numpad5, Numpad6, Numpad7, Numpad8
};

void checacolisonesposibles();
void terminajuego();
void avisapuntaje(HWND hWnd);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hwndVentana;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX); //Tamaño en bytes de la estructura.
	wc.style = CS_HREDRAW | CS_VREDRAW; //Entero de 16 bits que codifica el estilo de la clase de ventana.
	wc.lpfnWndProc = WindowProc;//Apunta al procedimiento de ventana.
	wc.hInstance = hInstance;//Identifica la instancia de la ventana a la que esta clase pertenece.
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//Identificador del curso de la clase. Debe ser un manipulador de un recurso de tipo icono. Si es Null, la aplicación mostrará un icono cuando el usuario minice la ventana de la aplicación.
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW; //Identificador del pincel para la clase.
	wc.lpszClassName = "GaravitoW"; //Especifica el nombre de la clase ventana.
	RegisterClassEx(&wc);//Registra una clase de ventana para su uso subsecuente en llamadas a las funciones CreateWindow o CreateWindowEx
	RECT wr = { 0, 0, 1080, 720 };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);//Calcula el tamaño necesario del rectángulo de la ventana.

	//Se crea la ventana definida previamente.
	hwndVentana = CreateWindowEx(NULL,//estilo extendido de ventana
		"GaravitoW",//puntero al nombre de la clase registrada *visto arriba*
		"Netw's Little Secret",//puntero al nombre de la ventana
		WS_OVERLAPPEDWINDOW,//estilo de ventana
		150,//posición horizontal de la ventana
		8,//posición vertical de la ventana
		wr.right - wr.left,//ancho de la ventana
		wr.bottom - wr.top,//alto de la ventana
		NULL,//manejador de la ventana padre o propietaria
		NULL,//manejador del menu o identificador de ventana hija
		hInstance,//manejador de la instancia de la aplicación
		NULL);//puntero a los datos de creación de la ventana

	ShowWindow(hwndVentana, nCmdShow);//Muestra la ventana creada

	glewInit();//Inicializa glew

	//Instancia de la escena
	scene = new Scene(hwndVentana);

	gamPad = new GamePadRR(1);

	//Crear un timer con el valor especificado de time-out
	timer1 = SetTimer(hwndVentana,//Manejador de ventana que recibirá los mensajes del timer
		Timer1,//identificador del timer
		30,//valor de time-out
		NULL);//dirección del procedimiento de timer

	timer2 = SetTimer(hwndVentana, Timer2, 1000, NULL);

	MSG msg = { 0 };
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}
		else
		{
			if (renderiza)
			{
				scene->render(hContextoVentana);
				if (juego) {
					/*strcat(Puntaje, "Player1 Points: ");
					_itoa(Player1->getPuntaje(), puntitos, 10);
					strcat(Puntaje, puntitos);
					strcat(Puntaje, "                     ");
					strcat(Puntaje, "IA Points: ");
					_itoa(IA->getPuntaje(), puntitos, 10);
					strcat(Puntaje, puntitos);
					scene->aux = Puntaje;
					scene->drawpuntos();
					scene->aux = NULL;
					strcpy(Puntaje, "");*/
				}
				renderiza = false;

				if (gamPad->IsConnected())
				{
					if (gamPad->GetState().Gamepad.wButtons == XINPUT_GAMEPAD_A) {
						if (juego) {
							Player1->Robar(IA, Player1->tellmenum(), scene->Mazo, hwndVentana);
							scene->actualizaIA(IA);
							IA->Robar(Player1, IA->VerNull(), scene->Mazo, hwndVentana);
							scene->actualizaIA(IA);
						}
						else {
							MessageBox(hwndVentana, "A", "A Funciona", MB_OK);
						}
					}
					if (gamPad->GetState().Gamepad.wButtons == XINPUT_GAMEPAD_B) {
						if (juego) {
							Player1->Seleccionar_carta();
						}
						else {
							MessageBox(hwndVentana, "B", "B Funciona", MB_OK);
						}
					}
					if (gamPad->GetState().Gamepad.wButtons == XINPUT_GAMEPAD_X) {
						if (juego) {
							juego = false;
							scene->playing = false;
							delete Player1;
							scene->borraIA();
							scene->Mazo.ResetDeck();
						}
						else {
							Player1 = new Jugador(scene->Mazo, "Player1");
							IA = new Jugador(scene->Mazo, "IA");
							scene->actualizaIA(IA);
							juego = true;
							scene->playing = true;
							scene->camaraJuego();
						}
					}
					/*if (gamPad->GetState().Gamepad.wButtons == XINPUT_GAMEPAD_Y) {
						MessageBox(hwndVentana, "Y", "Y Funciona", MB_OK);
					}*/
					if (gamPad->GetState().Gamepad.sThumbLX > DZ) {
						if (!juego) {
							scene->turnRight();
						}
					}
					if (gamPad->GetState().Gamepad.sThumbLX < -DZ) {
						if (!juego) {
							scene->turnLeft();
						}
					}
					if (gamPad->GetState().Gamepad.sThumbLY > DZ) {
						if (!juego) {
							scene->turnUp();
						}
					}
					if (gamPad->GetState().Gamepad.sThumbLY < -DZ) {
						if (!juego) {
							scene->turnDown();
						}
					}
					if (gamPad->GetState().Gamepad.sThumbRX > DZ) {
						if (!juego) {
							checacolisonesposibles();
							scene->moveRight();
						}
					}
					if (gamPad->GetState().Gamepad.sThumbRX < -DZ) {
						if (!juego) {
							checacolisonesposibles();
							scene->moveLeft();
						}
					}
					if (gamPad->GetState().Gamepad.sThumbRY > DZ) {
						if (!juego) {
							checacolisonesposibles();
							scene->moveForward();
						}
					}
					if (gamPad->GetState().Gamepad.sThumbRY < -DZ) {
						if (!juego) {
							checacolisonesposibles();
							scene->moveBackward();
						}
					}

				}
				else
				{
					//MessageBox(hwndVentana, "funciono", "peromuere", MB_OK);
					//aqui ponemos un messgaebox para decir que se perdio la conexion con el gamepad
				}

			}
		}
	}

	return msg.wParam;

}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HGLRC hContextoGL;
	static HDC hContextoAux;
	int ancho, alto;
	char epx[6] = "";
	char epz[6] = "";
	char epy[6] = "";
	char edx[6] = "";
	char edz[6] = "";
	char edy[6] = "";
	char ec[80] = "";

	switch (message)
	{
	case WM_CREATE:
		hContextoAux = GetDC(hWnd);
		hContextoVentana = hContextoAux;
		DefPixelFormat(hContextoVentana);
		hContextoGL = wglCreateContext(hContextoVentana);
		wglMakeCurrent(hContextoVentana, hContextoGL);
		srand(time(NULL));

		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			MessageBox(hWnd, "Mensaje", "Titulo", MB_OK);
			return 0;
		case VK_UP:
			if (juego) {

			}
			else {
				scene->turnUp();
				renderiza = true;
			}
			return 0;
		case VK_DOWN:
			if (juego) {

			}
			else {
				scene->turnDown();
				renderiza = true;
			}
			return 0;
		case VK_LEFT:
			if (juego) {

			}
			else {
				scene->turnLeft();
				renderiza = true;
			}
			return 0;
		case VK_RIGHT:
			if (juego) {
				Player1->Seleccionar_carta();
			}
			else {
				scene->turnRight();
				renderiza = true;
			}
			return 0;
		case 0x44: //D
			if (juego) {

			}
			else {
				checacolisonesposibles();
				scene->moveRight();
				renderiza = true;
			}
			return 0;
		case 0x41: //A
			if (juego) {

			}
			else {
				checacolisonesposibles();
				scene->moveLeft();
				renderiza = true;
			}
			return 0;
		case 0x57: //W
			if (juego) {

			}
			else {
				checacolisonesposibles();
				scene->moveForward();
				renderiza = true;
			}
			return 0;
		case 0x53: //S
			if (juego) {

			}
			else {
				checacolisonesposibles();
				scene->moveBackward();
				renderiza = true;
			}
			return 0;
		case 0x4a: {
			if (juego) {
				terminajuego();
			}
			else {
				Player1 = new Jugador(scene->Mazo, "Player1");
				IA = new Jugador(scene->Mazo, "IA");
				scene->actualizaIA(IA);
				juego = true;
				scene->playing = true;
				scene->camaraJuego();

			}
		}
				   return 0;
		case 0x45: {
			if (juego) {
				Player1->calculaprob(Player1->tellmenum(), IA, scene->Mazo, hWnd);
				Player1->Robar(IA, Player1->tellmenum(), scene->Mazo, hWnd);
				if (juego) {
					scene->actualizaIA(IA);
					IA->Robar(Player1, IA->VerNull(), scene->Mazo, hWnd);
					if (juego) {
						scene->actualizaIA(IA);
						avisapuntaje(hWnd);
					}
				}
				/*	glutBitmapCharacter();*/
			}
			else {

			}
		}

				   return 0;
		case Numpad1: {
			scene->real->aumentax(0);
			//scene->Bucket->Amimación(chocan.Proximidad());
			
			//scene->Maletin->Amimación(1);
			//scene->maninx -= 0.1;//-12,-10.8,-9.7,-8.6,-7.5,-6.4,-5.3,-4.2,-3.1,-2.0,-.9,0.2, 1.3, 2.4, 3.5, 4.6,5.7. 6.8, 7.9, 9, 10.1,11.2,12.3,13.4,14.5;
		}
					  return 0;
		case Numpad2: {
			//scene->Bucket->aumentay(0);
			scene->real->aumentay(0);
			//scene->Maletin->Amimación(0);
			//scene->maniny -= 0.1;//9
		}
					  return 0;
		case Numpad3: {
			//scene->Bucket->aumentaz(0);
			scene->real->aumentaz(0);
			//scene->maninz -= 0.1;//-76
		}
					  return 0;
		case Numpad4: {
			//scene->Bucket->aumentax(1);
			scene->real->aumentax(1);
		}
					  return 0;
		case Numpad5: {
			//scene->Bucket->aumentay(1);
			scene->real->aumentay(1);
		}
					  return 0;
		case Numpad6: {
			//scene->Bucket->aumentaz(1);
			scene->real->aumentaz(1);
		}
					  return 0;
		case Numpad7: {
			//scene->Bucket->aumentarot(1);
			scene->real->aumentarot(0);
		}
					  return 0;
		case Numpad8: {
			//scene->real->aumentarot(1);
			scene->daynight();
			
		}
					  return 0;
		}
	case WM_TIMER: {
		switch (wParam)
		{
		case Timer1: {
			renderiza = true;
			scene->Maletin->Amimación(chocan.Proximidad((-5), (+5), (-15), (0), scene->px, scene->pz));
			scene->Bucket->Amimación(chocan.Proximidad((0), (12.8), (-39.4), (-27.4), scene->px, scene->pz));
			scene->Pez->anima();
			scene->pajarin->anima();
			scene->real->anima();
			scene->by -= 0.1;
		}
					 break;
		case Timer2: {
			scene->cta();
		}
					 break;
		default:
			break;
		}
		

	}
				   break;
	case WM_DESTROY:
	{
		KillTimer(hWnd, timer1);
		KillTimer(hWnd, timer2);
		delete scene->skyDay;
		delete scene->terrain;
		delete scene->banner_cloth;
		delete scene->banner_mastil;
		delete scene->bed_base;
		delete scene->bed_colchon;
		delete scene->books;
		delete scene->Carnita;
		delete scene->chest_madera;
		delete scene->chest_metal;
		delete scene->cotage;
		delete scene->Bucket;
		delete scene->cuchitril;
		delete scene->Desk_base;
		delete scene->Desk_cajones;
		delete scene->dresser_base;
		delete scene->dresser_cajones;
		delete scene->ladder;
		delete scene->lampara;
		delete scene->Maletin;
		delete scene->rack;
		delete scene->Thun_add;
		delete scene->Thun_body;
		delete scene->Thun_tail;
		delete scene->King;
		delete scene->pajarin;
		delete scene->Pez;
		delete scene->piedra1;
		delete scene->piedra2;
		delete scene->lago2;
		delete scene->lago3;
		delete scene->real;
		if (juego) {
			scene->borraIA();
			delete Player1;
		}
		wglMakeCurrent(hContextoVentana, NULL);
		wglDeleteContext(hContextoGL);
		PostQuitMessage(0);
		return 0;
	} break;

	case WM_SIZE:
	{
		alto = HIWORD(lParam);
		ancho = LOWORD(lParam);
		if (alto == 0)
			alto = 1;
		glViewport(0, 0, ancho, alto);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLfloat)ancho / (GLfloat)alto, 1.0f, 10000.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void DefPixelFormat(HDC hDC)
{
	int bestmatch;

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR), //tamaño de la estructura
		1, //numero de version
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //soporta la ventana, el opengl y manejara doble buffer
		PFD_TYPE_RGBA, //formato de 32 bits rgba
		32, //tamaño del color en 32 bits
		0, 0, 0, 0, 0, 0, //bits de color, no se usan
		0, //no hay buffer para el alfa
		0, //ignore el bit de corrimiento
		0, //no hay buffer de acumulacion
		0, 0, 0, 0, //no hay bits de acumulacion
		16, //tamaño del flotante para el buffer z
		0, //no hay buffers de stencil
		0, //no hay buffers auxiliares
		PFD_MAIN_PLANE, //plano principal para dibujo
		0, //reservado
		0, 0, 0 //mascaras de capas ignoradas
	};

	bestmatch = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, bestmatch, &pfd);
}


void terminajuego() {
	juego = false;
	scene->playing = false;
	delete Player1;
	scene->borraIA();
	scene->Mazo.ResetDeck();
}

void checacolisonesposibles() {

	chocan.ChecaCol(2, 100, 2, 16, scene->px, scene->pz);
	chocan.ChecaCol(-100, -3, 2, 14, scene->px, scene->pz);
	chocan.ChecaCol(7, 12, -46, 9, scene->px, scene->pz);
	chocan.ChecaCol(-10, -7, -46, 9, scene->px, scene->pz);
	chocan.ChecaCol(-12, -4, -46, -40, scene->px, scene->pz);
	chocan.ChecaCol(4, 12, -46, -40, scene->px, scene->pz);
	chocan.ChecaCol(-500, 500, -160, -152, scene->px, scene->pz);

}
void avisapuntaje(HWND hWnd) {

	strcat(Puntaje, "Player1 Points: ");
	_itoa(Player1->getPuntaje(), puntitos, 10);
	strcat(Puntaje, puntitos);
	strcat(Puntaje, "                     ");
	strcat(Puntaje, "IA Points: ");
	_itoa(IA->getPuntaje(), puntitos, 10);
	strcat(Puntaje, puntitos);
	MessageBox(hWnd, Puntaje, "Puntos", MB_OK);
	strcpy(Puntaje, "");

}