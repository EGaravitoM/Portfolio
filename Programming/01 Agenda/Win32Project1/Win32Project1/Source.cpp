#include <Windows.h>
#include "resource.h"
#include <fstream>
#include <CommDlg.h>
#include <mmsystem.h>
#include "commctrl.h"
#include <string>
#include <ctime>

using namespace std;
#pragma comment(lib, "winmm.lib")


HWND ghDlg = 0;
HWND Contactos, Calendario_M, Calendario_S, Citas;
HINSTANCE hInst;
int show, salidaextrema, numerito, alarma, borradorcito;
int ddg, aag, mmg, hourg, minuteg;
char Bienvenidoacasa[MAX_PATH] = "";
char Def1[MAX_PATH] = "";
char Def2[MAX_PATH] = "";

//TIEMPO
long long control_totalnum, control_totalqui, dianum, mesnum, añonum, diaqui, mesqui, añoqui;
int horanum, minutonum, horaqui, minutoqui;

#define ID_5SECONDS 100
UINT Timeralarma = 0;

struct fotos {
	fotos *ant;
	char foto[MAX_PATH];
	fotos *sig;
};

struct Contacto {
	char nombre[30];
	fotos *imagenes;
	char cancion[MAX_PATH];
	char categoria[20];
	bool genero; // True = Women
	char celular[30];
	char telefono[30];
	char direccion[50];
	char correo[30];
	short numfot;

	Contacto*sig;
};
Contacto*Inicio = 0, *indice = 0;

struct citas {
	citas *sig;
	citas *ant;
	bool avisado;
	char NombreC[30];
	char Motivo[30];
	char Personas[30];
	char Lugra[30];
	char alarma[MAX_PATH];
	char Hora[30];
	char Fecha[30];
	short dian;
	short dia;
	short mes;
	short año;
	short hora;
	short minuto;
};
citas *inicioC = 0, *indiceC = 0;

BOOL CALLBACK venta1(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Conta(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Calen_M(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Calen_S(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK dates(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
void ElegirArchivo(HWND Ventana, HWND Cajita, int filtro);
void JalaarchiUSU();
void MetearchiUSU();
void JalaarchiCATE(HWND hCatego);
void JalaarchiCitas();
void MetearchiCitas();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR cmdLine, int showCmd)
{
	hInst = hInstance;
	show = showCmd;
	GetCurrentDirectory(MAX_PATH, Bienvenidoacasa);
	JalaarchiUSU();
	JalaarchiCitas();
	


	ghDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MENU), 0, venta1);
	ShowWindow(ghDlg, showCmd);

	Timeralarma = SetTimer(ghDlg, ID_5SECONDS, 2000, NULL);

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (GetMessage(&msg, 0, 0, 0)) {
		if (ghDlg == 0 || !IsDialogMessage(ghDlg, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	MetearchiCitas();
	MetearchiUSU();
	return (int)msg.wParam;
}

BOOL CALLBACK venta1(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg)
	{
	case WM_INITDIALOG:

		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_CONTACTOS:
			Contactos = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONTACTOS), hDlg, Conta);
			ShowWindow(Contactos, show);
			return true;
		case IDC_CALENDARIO:
			Calendario_M = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CALENDARIO_M), hDlg, Calen_M);
			ShowWindow(Calendario_M, show);
			return true;
		case IDC_CITAS:
			Citas = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CITAS), hDlg, dates);
			ShowWindow(Citas, show);
			return true;
		case IDC_SALIR:
			DestroyWindow(hDlg);
			return true;

		case ID_ARCHIVO_SALIR:
			DestroyWindow(hDlg);
			return true;

		}
		return true;

	case WM_TIMER: {
		if (inicioC != NULL) {
			char comando[MAX_PATH] = "";
			time_t actualTime;
			struct tm *timeinfo;
			time(&actualTime);
			timeinfo = localtime(&actualTime);
			ddg = timeinfo->tm_mday;
			mmg = timeinfo->tm_mon + 1;
			aag = timeinfo->tm_year + 1900;
			hourg = timeinfo->tm_hour;
			minuteg = timeinfo->tm_min;

			indiceC = inicioC;
			do {
				añonum = indiceC->año * 10000000000;
				mesnum = indiceC->mes * 1000000;
				dianum = indiceC->dia * 10000;
				horanum = indiceC->hora * 100;
				minutonum = indiceC->minuto;
				control_totalnum = añonum + mesnum + dianum + horanum + minutonum;
				añoqui = aag * 10000000000;
				mesqui = mmg * 1000000;
				diaqui = ddg * 10000;
				horaqui = hourg * 100;
				minutoqui = minuteg;
				control_totalqui = añoqui + mesqui + diaqui + horaqui + minutoqui;

				if (control_totalnum <= control_totalqui && indiceC->avisado == false) {
					indiceC->avisado = true;
					strcat(comando, "open \"");
					strcat(comando, indiceC->alarma);
					strcat(comando, "\" alias MP3");
					mciSendString(comando, NULL, 0, 0);
					mciSendString("play mp3", NULL, 0, 0);
					char mensagito[50] = "";
					strcat(mensagito, "Es hora de su cita llamada: ");
					strcat(mensagito, indiceC->NombreC);
					alarma = MessageBox(hDlg, mensagito, "Alarma de Citas", MB_OK | MB_ICONEXCLAMATION);
					if (alarma == IDOK) {
						mciSendString("stop mp3", NULL, 0, 0);
						mciSendString("close mp3", NULL, 0, 0);
						borradorcito = MessageBox(hDlg, "Desea borrar esta cita que ya ha pasado?", "Alarma de Citas", MB_YESNOCANCEL | MB_ICONEXCLAMATION);
						if (borradorcito == IDYES) {
							if (indiceC == inicioC) {
								if (indiceC != indiceC->sig) {
									inicioC = indiceC->sig;
									indiceC->ant->sig = indiceC->sig;
									indiceC->sig->ant = indiceC->ant;
								}
								else {
									inicioC = NULL;
								}
							}
							else {
								indiceC->ant->sig = indiceC->sig;
								indiceC->sig->ant = indiceC->ant;
							}

							delete indiceC;
						}
					}
					break;
				}

				indiceC = indiceC->sig;


			} while (indiceC != inicioC);
		}
	}
				   return true;

	case WM_CLOSE:
		DestroyWindow(hDlg);
		return true;
	case WM_DESTROY:
		PostQuitMessage(0);
		return true;
	}

	return false;
}
BOOL CALLBACK Conta(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {

	static HWND hCatego = 0, hImagen = 0, hMP3 = 0, hNombre = 0, hCelular = 0, hTelefono = 0, hDireccion = 0, hCorreo = 0, hCC = 0, hIBT = 0;
	char imagen[MAX_PATH] = "";
	char musica[MAX_PATH] = "", comando[MAX_PATH] = "";
	static HBITMAP bmp1, bmp2;
	int index = 0;
	static fotos *auxito, *iniciof = NULL, *indicef;


	switch (msg)
	{
	case WM_INITDIALOG:
		hCC = GetDlgItem(hDlg, IDC_COMBOCONTACTOS);
		hCatego = GetDlgItem(hDlg, IDC_CATEGORIA);
		hImagen = GetDlgItem(hDlg, IDC_FOTO);
		hMP3 = GetDlgItem(hDlg, IDC_CANCION);
		hNombre = GetDlgItem(hDlg, IDC_NOMBRE);
		hCelular = GetDlgItem(hDlg, IDC_CELULAR);
		hTelefono = GetDlgItem(hDlg, IDC_TELEFONO);
		hDireccion = GetDlgItem(hDlg, IDC_DIRECCION);
		hCorreo = GetDlgItem(hDlg, IDC_CORREO);
		hIBT = GetDlgItem(hDlg, IDC_IBT);

		CheckRadioButton(hDlg, IDC_MUJER, IDC_HOMBRE, IDC_HOMBRE);
		CheckDlgButton(hDlg, IDC_HOMBRE, BST_CHECKED);

		indice = Inicio;
		if (Inicio != NULL) {
			while (indice != NULL)
			{
				SendMessage(hCC, CB_INSERTSTRING, 0, (LPARAM)indice->nombre);
				indice = indice->sig;
			}
		}
		JalaarchiCATE(hCatego);
		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_MUJER:
		case IDC_HOMBRE:
			if (IsDlgButtonChecked(hDlg, IDC_HOMBRE) == BST_CHECKED)
				CheckDlgButton(hDlg, IDC_HOMBRE, BST_CHECKED);
			else
				CheckDlgButton(hDlg, IDC_HOMBRE, BST_UNCHECKED);

		case IDC_PLAY:
			GetWindowText(hMP3, musica, MAX_PATH);
			strcat(comando, "open \"");
			strcat(comando, musica);
			strcat(comando, "\" alias MP3");
			mciSendString(comando, NULL, 0, 0);
			mciSendString("play mp3", NULL, 0, 0);
			return true;
		case IDC_PAUSA:
			mciSendString("pause mp3", NULL, 0, 0);
			return true;
		case IDC_STOP:
			mciSendString("stop mp3", NULL, 0, 0);
			mciSendString("close mp3", NULL, 0, 0);
			return true;

		case ID_CONTACTOS_AGREGARIMAGEN:
			numerito = 0;
			ElegirArchivo(hDlg, hIBT, 1);
			GetWindowText(hIBT, imagen, MAX_PATH);
			if (strcmp(imagen, "") != 0)
			{
				bmp1 = (HBITMAP)SendDlgItemMessage(hDlg, IDC_FOTO, STM_GETIMAGE, IMAGE_BITMAP, 0);
				bmp2 = (HBITMAP)LoadImage(NULL, imagen, IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);

				SendDlgItemMessage(hDlg, IDC_FOTO, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2);
				auxito = new fotos;
				strcpy(auxito->foto, imagen);
				auxito->sig = NULL;
				auxito->ant = NULL;
				if (iniciof == NULL) {
					iniciof = auxito;
					auxito->ant = iniciof;
					auxito->sig = iniciof;
					numerito += 1;
				}
				else
				{
					indicef = iniciof->ant;
					indicef->sig = auxito;
					auxito->sig = iniciof;
					auxito->ant = indicef;
					iniciof->ant = auxito;
					numerito += 1;
				}
			}
			return true;

		case ID_CONTACTOS_AGREGARCANCI40015:
			ElegirArchivo(hDlg, hMP3, 2);
			return true;

		case IDC_AC:
		case ID_CONTACTOS_AGREGAR: {
			int usaaqui;
			char aiuda[MAX_PATH];
			char fotito[MAX_PATH];
			fotos *indfot, *auxito;
			Contacto paso;
			GetWindowText(hNombre, paso.nombre, 30);
			GetWindowText(hMP3, paso.cancion, MAX_PATH);
			GetWindowText(hCelular, paso.celular, 30);
			GetWindowText(hTelefono, paso.telefono, 30);
			GetWindowText(hCorreo, paso.correo, 30);
			GetWindowText(hDireccion, paso.direccion, 50);
			GetWindowText(hIBT, aiuda, MAX_PATH);
			paso.sig = NULL;
			usaaqui = SendMessage(hCatego, CB_GETCURSEL, 0, 0);
			SendMessage(hCatego, CB_GETLBTEXT, (WPARAM)usaaqui, (LPARAM)paso.categoria);
			paso.genero = true;
			if (IsDlgButtonChecked(hDlg, IDC_HOMBRE) == BST_CHECKED)
				paso.genero = false;
			if (Inicio != NULL) {
				indice = Inicio;
				while (indice != NULL)
				{
					if (strcmp(paso.nombre, "") == 0 || strcmp(paso.nombre, indice->nombre) == 0) {
						MessageBox(hDlg, "Debe poner un Nombre, este debe ser Unico y no repetirse", "Checa por nombre", MB_OK | MB_ICONINFORMATION);
						goto NADA;
					}
					indice = indice->sig;
				}
			}
			Contacto *Nuevo = new Contacto;
			indice = Nuevo;
			strcpy(Nuevo->cancion, paso.cancion);
			strcpy(Nuevo->nombre, paso.nombre);
			strcpy(Nuevo->celular, paso.celular);
			strcpy(Nuevo->direccion, paso.direccion);
			strcpy(Nuevo->telefono, paso.telefono);
			strcpy(Nuevo->correo, paso.correo);
			strcpy(Nuevo->categoria, paso.categoria);
			Nuevo->genero = paso.genero;
			Nuevo->numfot = 0;
			Nuevo->sig = 0;
			if (iniciof == NULL) {
				if (strcmp(aiuda, "") == 0) {
					sprintf(fotito, "%s\\duckguy.bmp", Bienvenidoacasa);
					auxito = new fotos;
					strcpy(auxito->foto, fotito);
					auxito->sig = NULL;
					auxito->ant = NULL;
					iniciof = auxito;
					auxito->ant = iniciof;
					auxito->sig = iniciof;
					numerito += 1;
				}
			}
			else {
				auxito = new fotos;
				indfot = iniciof->ant;
				indfot->sig = auxito;
				auxito->sig = iniciof;
				auxito->ant = indicef;
				iniciof->ant = auxito;
				numerito += 1;

			}
			Nuevo->imagenes = iniciof;
			Nuevo->numfot += numerito;
			iniciof = 0;

			if (Inicio == NULL)
				Inicio = Nuevo;
			else
			{
				indice = Inicio;
				while (indice->sig != NULL) {
					indice = indice->sig;
				}

				indice->sig = Nuevo;
			}
			SendMessage(hCatego, CB_INSERTSTRING, 0, (LPARAM)paso.nombre);
			SendMessage(hCC, CB_INSERTSTRING, 0, (LPARAM)paso.nombre);
			MessageBox(hDlg, "El contacto ha sido agregado exitosamente", "Contactos", MB_OK | MB_ICONINFORMATION);
			SetWindowText(hNombre, "");
			SetWindowText(hImagen, "");
			SetWindowText(hMP3, "");
			SetWindowText(hCelular, "");
			SetWindowText(hTelefono, "");
			SetWindowText(hCorreo, "");
			SetWindowText(hDireccion, "");
			SetWindowText(hCatego, "");
			SetWindowText(hIBT, "");
			SendDlgItemMessage(hDlg, IDC_FOTO, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)"");
			CheckDlgButton(hDlg, IDC_HOMBRE, BST_CHECKED);
			CheckDlgButton(hDlg, IDC_MUJER, BST_UNCHECKED);
		NADA:
			int a = 0;
		}
								   return true;
		case IDC_MC:
		case ID_CONTACTOS_GUARDAR: {
			int usaaqui;
			fotos *auxito;
			auxito = new fotos;
			bool nuevito = false;
			if (Inicio == NULL) {
				MessageBox(hDlg, "Primero debe Agregar un Contacto antes de Modificar", "Contactos", MB_OK | MB_ICONINFORMATION);
			}
			else {
				indice = Inicio;
				bool encontrado = false;
				Contacto paso;
				index = SendMessage(hCC, CB_GETCURSEL, 0, 0);
				SendMessage(hCC, CB_GETLBTEXT, (WPARAM)index, (LPARAM)paso.nombre);
				while (indice != NULL)
				{
					if (strcmp(indice->nombre, paso.nombre) == 0 || strcmp(indice->correo, paso.correo) == 0 || strcmp(indice->direccion, paso.direccion) == 0) {
						encontrado = true;
						usaaqui = SendMessage(hCC, CB_FINDSTRING, -1, (LPARAM)indice->nombre);
						SendMessage(hCC, CB_DELETESTRING, (WPARAM)usaaqui, 0);
						GetWindowText(hNombre, indice->nombre, 30);
						GetWindowText(hImagen, auxito->foto, MAX_PATH);
						GetWindowText(hMP3, indice->cancion, MAX_PATH);
						GetWindowText(hCelular, indice->celular, 30);
						GetWindowText(hTelefono, indice->telefono, 30);
						GetWindowText(hCorreo, indice->correo, 30);
						GetWindowText(hDireccion, indice->direccion, 50);
						usaaqui = SendMessage(hCatego, CB_GETCURSEL, 0, 0);
						SendMessage(hCatego, CB_GETLBTEXT, (WPARAM)usaaqui, (LPARAM)indice->categoria);
						SendMessage(hCC, CB_INSERTSTRING, 0, (LPARAM)indice->nombre);
						indice->numfot += numerito;
						indice->genero = true;
						if (IsDlgButtonChecked(hDlg, IDC_HOMBRE) == BST_CHECKED) {
							indice->genero = false;
						}
						auxito->sig = NULL;
						auxito->ant = NULL;
						indicef = indice->imagenes;
						while (indice->imagenes != NULL) {
							if (strcmp(indicef->foto, auxito->foto) == 0) {
								indicef = indicef->sig;
							}
							else {
								nuevito = true;
								break;
							}
							if (nuevito) {
								if (indice->imagenes == NULL) {
									indice->imagenes = auxito;
									auxito->ant = indice->imagenes;
								}
								else
								{
									indicef = indice->imagenes;
									while (indicef->sig != NULL) {
										indicef = indicef->sig;
									}
									indicef->sig = auxito;
									auxito->ant = indicef;
								}
							}
							indice = indice->sig;
						}

					}
					indice = indice->sig;
				}
				if (encontrado == true) {
					MessageBox(hDlg, "El contacto ha sido guardado exitosamente", "Contactos", MB_OK | MB_ICONINFORMATION);
					SetWindowText(hNombre, "");
					SetWindowText(hImagen, "");
					SetWindowText(hMP3, "");
					SetWindowText(hCelular, "");
					SetWindowText(hTelefono, "");
					SetWindowText(hCorreo, "");
					SetWindowText(hDireccion, "");
					SetWindowText(hIBT, "");
					SetWindowText(hCatego, "");
					SendDlgItemMessage(hDlg, IDC_FOTO, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)"");
					CheckDlgButton(hDlg, IDC_HOMBRE, BST_CHECKED);
					CheckDlgButton(hDlg, IDC_MUJER, BST_UNCHECKED);
				}

				else {
					MessageBox(hDlg, "El contacto NO!!! ha sido guardado exitosamente", "Contactos", MB_OK | MB_ICONEXCLAMATION);
				}
			}

		}
								   return true;
		case IDC_COMBOCONTACTOS: {
			bool encontrado = false;
			int usaaqui;
			indice = Inicio;
			char nombresitowey[30] = "";
			usaaqui = SendMessage(hCC, CB_GETCURSEL, 0, 0);
			if (usaaqui > -1) {
				SendMessage(hCC, CB_GETLBTEXT, (WPARAM)usaaqui, (LPARAM)nombresitowey);
				while (indice != NULL) {
					if (strcmp(indice->nombre, nombresitowey)) {
						indice = indice->sig;
					}
					else {
						encontrado = true;
						SetWindowText(hNombre, indice->nombre);
						SetWindowText(hMP3, indice->cancion);
						SetWindowText(hCelular, indice->celular);
						SetWindowText(hTelefono, indice->telefono);
						SetWindowText(hCorreo, indice->correo);
						SetWindowText(hDireccion, indice->direccion);
						SetWindowText(hCatego, indice->categoria);
						if (indice->imagenes != 0) {
							SetWindowText(hIBT, indice->imagenes->foto);
						}
						bmp1 = (HBITMAP)SendDlgItemMessage(hDlg, IDC_FOTO, STM_GETIMAGE, IMAGE_BITMAP, 0);
						bmp2 = (HBITMAP)LoadImage(NULL, indice->imagenes->foto, IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
						SendDlgItemMessage(hDlg, IDC_FOTO, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2);
						if (indice->genero) {
							CheckDlgButton(hDlg, IDC_MUJER, BST_CHECKED);
							CheckDlgButton(hDlg, IDC_HOMBRE, BST_UNCHECKED);
						}
						else {
							CheckDlgButton(hDlg, IDC_HOMBRE, BST_CHECKED);
							CheckDlgButton(hDlg, IDC_MUJER, BST_UNCHECKED);
						}
						indice = Inicio;

						break;
					}

				}
				if (encontrado == false) {
					MessageBox(hDlg, "No es Posible Encontrar este Contacto", "Contactos", MB_OK | MB_ICONINFORMATION);
					encontrado = false;

				}

			}
		}
								 SendMessage(hCC, CBN_KILLFOCUS, 0, 0);
								 return true;
		case IDC_EC:
		case ID_CONTACTOS_ELIMINAR: {
			fotos *aiuda;
			int usaaqui;
			char nombresitowey[30];
			GetWindowText(hNombre, nombresitowey, 30);
			if (strcmp(nombresitowey, "") == 0) {
				MessageBox(hDlg, "Debe seleccionar un contacto para eliminarlo", "Contactos", MB_OK | MB_ICONINFORMATION);
			}
			else {
				indice = Inicio;
				if (strcmp(Inicio->nombre, nombresitowey)) {
					while (Inicio != 0) {
						if (strcmp(indice->sig->nombre, nombresitowey)) {
							indice = indice->sig;
						}
						else {
							Contacto *aux = indice->sig;
							indice->sig = aux->sig;
							if (aux->imagenes != 0) {
								indicef = aux->imagenes;
								do {
									aiuda = indicef;
									indicef = indicef->sig;
									delete aiuda;
								} while (indicef != aux->imagenes);
								aux->imagenes = NULL;
							}
							delete aux;
							usaaqui = SendMessage(hCC, CB_FINDSTRING, -1, (LPARAM)nombresitowey);
							SendMessage(hCC, CB_DELETESTRING, (WPARAM)usaaqui, 0);
							SetWindowText(hCC, "");
							MessageBox(hDlg, "Contacto eliminado exitosamente", "Contactos", MB_OK | MB_ICONINFORMATION);
							SetWindowText(hNombre, "");
							SetWindowText(hImagen, "");
							SetWindowText(hMP3, "");
							SetWindowText(hCelular, "");
							SetWindowText(hTelefono, "");
							SetWindowText(hCorreo, "");
							SetWindowText(hDireccion, "");
							SetWindowText(hIBT, "");
							SetWindowText(hCatego, "");
							SendDlgItemMessage(hDlg, IDC_FOTO, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)"");
							CheckDlgButton(hDlg, IDC_HOMBRE, BST_CHECKED);
							CheckDlgButton(hDlg, IDC_MUJER, BST_UNCHECKED);
							break;
						}
					}
				}
				else {
					Inicio = indice->sig;
					if (indice->imagenes != 0) {
						indicef = indice->imagenes;
						do {
							aiuda = indicef;
							indicef = indicef->sig;
							delete aiuda;
						} while (indicef != indice->imagenes);
						indice->imagenes = NULL;
					}
					delete indice;
					usaaqui = SendMessage(hCC, CB_FINDSTRING, -1, (LPARAM)nombresitowey);
					SendMessage(hCC, CB_DELETESTRING, (WPARAM)usaaqui, 0);
					MessageBox(hDlg, "Contacto eliminado exitosamente", "Contactos", MB_OK | MB_ICONINFORMATION);
					SetWindowText(hNombre, "");
					SetWindowText(hImagen, "");
					SetWindowText(hMP3, "");
					SetWindowText(hCelular, "");
					SetWindowText(hTelefono, "");
					SetWindowText(hCorreo, "");
					SetWindowText(hDireccion, "");
					SetWindowText(hIBT, "");
					SetWindowText(hCatego, "");
					SendDlgItemMessage(hDlg, IDC_FOTO, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)"");
					CheckDlgButton(hDlg, IDC_HOMBRE, BST_CHECKED);
					CheckDlgButton(hDlg, IDC_MUJER, BST_UNCHECKED);
					break;
				}

			}
		}
									return true;

		case IDC_VOLVER:
			EndDialog(hDlg, 0);
			return true;

		case IDC_CFA: {
			indice = Inicio;
			char nombresitowey[30];
			GetWindowText(hNombre, nombresitowey, 30);
			while (indice != NULL)
			{
				if (strcmp(indice->nombre, nombresitowey) == 0) {
					indice->imagenes = indice->imagenes->ant;
					bmp1 = (HBITMAP)SendDlgItemMessage(hDlg, IDC_FOTO, STM_GETIMAGE, IMAGE_BITMAP, 0);
					bmp2 = (HBITMAP)LoadImage(NULL, indice->imagenes->foto, IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
					SendDlgItemMessage(hDlg, IDC_FOTO, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2);
					SetWindowText(hIBT, indice->imagenes->foto);
					break;
				}
				else {
					indice = indice->sig;
				}
			}

		}
					  return true;

		case IDC_CFS: {
			indice = Inicio;
			char nombresitowey[30];
			GetWindowText(hNombre, nombresitowey, 30);
			while (indice != NULL)
			{
				if (strcmp(indice->nombre, nombresitowey) == 0) {
					indice->imagenes = indice->imagenes->sig;
					bmp1 = (HBITMAP)SendDlgItemMessage(hDlg, IDC_FOTO, STM_GETIMAGE, IMAGE_BITMAP, 0);
					bmp2 = (HBITMAP)LoadImage(NULL, indice->imagenes->foto, IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
					SendDlgItemMessage(hDlg, IDC_FOTO, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2);
					SetWindowText(hIBT, indice->imagenes->foto);
					break;
				}
				else {
					indice = indice->sig;
				}
			}

		}
					  return true;
		}
		return true;



	case WM_CLOSE:
		salidaextrema = MessageBox(hDlg, "¿Estas seguro que deseas salir sin guardar correctamente?", "CUIDAAAAAAAAO!!!!!", MB_YESNOCANCEL | MB_ICONEXCLAMATION);
		if (salidaextrema == IDYES) {
			PostQuitMessage(0);
		}
		return true;
	case WM_DESTROY:
		EndDialog(hDlg, 0);
		return true;
	}

	return false;
}
BOOL CALLBACK Calen_M(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {

	static HWND hNombreCM = 0, hMotivoCM = 0, hPersonaCM = 0, hLugarCM = 0, hHoraCM = 0, hFechaCM = 0, hAlarmaCM = 0, hComboCM = 0, hDateTime = 0;
	static HWND diasmios[31];


	switch (msg)
	{
	case WM_INITDIALOG:
		hNombreCM = GetDlgItem(hDlg, IDC_NOMBRECM);
		hMotivoCM = GetDlgItem(hDlg, IDC_MOTIVOCM);
		hPersonaCM = GetDlgItem(hDlg, IDC_PERSONASCM);
		hLugarCM = GetDlgItem(hDlg, IDC_LUGARCM);
		hHoraCM = GetDlgItem(hDlg, IDC_HORACM);
		hFechaCM = GetDlgItem(hDlg, IDC_FECHACM);
		hAlarmaCM = GetDlgItem(hDlg, IDC_ALARMACM);
		hComboCM = GetDlgItem(hDlg, IDC_COMBOCPM);
		hDateTime = GetDlgItem(hDlg, IDC_DATETIMEPICKERM);


		diasmios[0] = GetDlgItem(hDlg, IDC_DIA1);
		diasmios[1] = GetDlgItem(hDlg, IDC_DIA2);
		diasmios[2] = GetDlgItem(hDlg, IDC_DIA3);
		diasmios[3] = GetDlgItem(hDlg, IDC_DIA4);
		diasmios[4] = GetDlgItem(hDlg, IDC_DIA5);
		diasmios[5] = GetDlgItem(hDlg, IDC_DIA6);
		diasmios[6] = GetDlgItem(hDlg, IDC_DIA7);
		diasmios[7] = GetDlgItem(hDlg, IDC_DIA8);
		diasmios[8] = GetDlgItem(hDlg, IDC_DIA9);
		diasmios[9] = GetDlgItem(hDlg, IDC_DIA10);
		diasmios[10] = GetDlgItem(hDlg, IDC_DIA11);
		diasmios[11] = GetDlgItem(hDlg, IDC_DIA12);
		diasmios[12] = GetDlgItem(hDlg, IDC_DIA13);
		diasmios[13] = GetDlgItem(hDlg, IDC_DIA14);
		diasmios[14] = GetDlgItem(hDlg, IDC_DIA15);
		diasmios[15] = GetDlgItem(hDlg, IDC_DIA16);
		diasmios[16] = GetDlgItem(hDlg, IDC_DIA17);
		diasmios[17] = GetDlgItem(hDlg, IDC_DIA18);
		diasmios[18] = GetDlgItem(hDlg, IDC_DIA19);
		diasmios[19] = GetDlgItem(hDlg, IDC_DIA20);
		diasmios[20] = GetDlgItem(hDlg, IDC_DIA21);
		diasmios[21] = GetDlgItem(hDlg, IDC_DIA22);
		diasmios[22] = GetDlgItem(hDlg, IDC_DIA23);
		diasmios[23] = GetDlgItem(hDlg, IDC_DIA24);
		diasmios[24] = GetDlgItem(hDlg, IDC_DIA25);
		diasmios[25] = GetDlgItem(hDlg, IDC_DIA26);
		diasmios[26] = GetDlgItem(hDlg, IDC_DIA27);
		diasmios[27] = GetDlgItem(hDlg, IDC_DIA28);
		diasmios[28] = GetDlgItem(hDlg, IDC_DIA29);
		diasmios[29] = GetDlgItem(hDlg, IDC_DIA30);
		diasmios[30] = GetDlgItem(hDlg, IDC_DIA31);



		indiceC = inicioC;
		if (inicioC != NULL) {
			do
			{
				SendMessage(hComboCM, CB_INSERTSTRING, 0, (LPARAM)indiceC->NombreC);
				indiceC = indiceC->sig;
			} while (indiceC != inicioC);
		}
		return true;


		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_MDM:
			EndDialog(hDlg, 0);
			return true;

		case IDC_COMBOCPM: {
			bool encontrado = false;
			int usaaqui;
			indiceC = inicioC;
			char nombresitoweyy[30] = "";
			usaaqui = SendMessage(hComboCM, CB_GETCURSEL, 0, 0);
			if (usaaqui > -1) {
				SendMessage(hComboCM, CB_GETLBTEXT, (WPARAM)usaaqui, (LPARAM)nombresitoweyy);
				do
				{
					if (strcmp(indiceC->NombreC, nombresitoweyy) == 0) {
						encontrado = true;
						SetWindowText(hNombreCM, indiceC->NombreC);
						SetWindowText(hMotivoCM, indiceC->Motivo);
						SetWindowText(hPersonaCM, indiceC->Personas);
						SetWindowText(hLugarCM, indiceC->Lugra);
						SetWindowText(hHoraCM, indiceC->Hora);
						SetWindowText(hFechaCM, indiceC->Fecha);
						SetWindowText(hAlarmaCM, indiceC->alarma);
						indiceC = inicioC;
						break;
					}
					indiceC = indiceC->sig;

				} while (indiceC != inicioC);

				if (encontrado == false) {
					MessageBox(hDlg, "No es Posible Encontrar esta Cita", "Citas", MB_OK | MB_ICONINFORMATION);
					encontrado = false;
				}
			}
		}
						   SendMessage(hComboCM, CBN_KILLFOCUS, 0, 0);
						   return true;
		case IDC_VMS:
		case IDC_DATETIMEPICKERM: {

			for (short i = 0; i < 31; i++) {
				SetWindowText(diasmios[i], "");
			}

			char Fechita[30] = "";
			short añito;
			short mesesito;
			short diita;
			short diitan;
			short varsitoito;
			char Infosita[MAX_PATH] = "";
			GetWindowText(hDateTime, Fechita, 30);
			string cutMonth(Fechita);
			string Daynombre = cutMonth.substr(0, cutMonth.find_first_of(","));
			if (Daynombre == "Monday")
				diitan = 1;
			if (Daynombre == "Tuesday")
				diitan = 2;
			if (Daynombre == "Wednesday")
				diitan = 3;
			if (Daynombre == "Thursday")
				diitan = 4;
			if (Daynombre == "Friday")
				diitan = 5;
			if (Daynombre == "Saturday")
				diitan = 6;
			if (Daynombre == "Sunday")
				diitan = 7;
			string Daynumero = cutMonth.substr(cutMonth.find_last_of(",") - 2, 2);
			diita = atoi(Daynumero.c_str());
			if (diita > 10) {
				varsitoito = 3;
			}
			else {
				varsitoito = 2;
			}
			string Month = cutMonth.substr(cutMonth.find_first_of(" ") + 1, ((cutMonth.find_last_of(" ") - (1 + varsitoito)) - ((cutMonth.find_first_of(" ") + 1))));
			if (Month == "January")
				mesesito = 1;
			if (Month == "February")
				mesesito = 2;
			if (Month == "March")
				mesesito = 3;
			if (Month == "April")
				mesesito = 4;
			if (Month == "May")
				mesesito = 5;
			if (Month == "June")
				mesesito = 6;
			if (Month == "July")
				mesesito = 7;
			if (Month == "August")
				mesesito = 8;
			if (Month == "September")
				mesesito = 9;
			if (Month == "October")
				mesesito = 10;
			if (Month == "November")
				mesesito = 11;
			if (Month == "December")
				mesesito = 12;
			string Year = cutMonth.substr(cutMonth.find_last_of(" ") + 1, 4);
			añito = atoi(Year.c_str());

			do {
				if (indiceC->año == añito && indiceC->mes == mesesito)
				{
					char diadecita[15] = "";
					switch (indiceC->dian)
					{
					case 1:
						strcpy(diadecita, "Monday");
						break;
					case 2:
						strcpy(diadecita, "Tuesday");
						break;
					case 3:
						strcpy(diadecita, "Wednesday");
						break;
					case 4:
						strcpy(diadecita, "Thursday");
						break;
					case 5:
						strcpy(diadecita, "Friday");
						break;
					case 6:
						strcpy(diadecita, "Saturday");
						break;
					case 7:
						strcpy(diadecita, "Sunday");
						break;
					default:
						break;
					}
					strcat(Infosita, indiceC->NombreC);
					strcat(Infosita, "-");
					strcat(Infosita, diadecita);
					strcat(Infosita, "-");
					strcat(Infosita, indiceC->Hora);
					int control = indiceC->dia - 1;
					SetWindowText(diasmios[control], Infosita);
					strcpy(Infosita, "");
				}
				indiceC = indiceC->sig;
			} while (indiceC != inicioC);

		}
								  return true;

		case IDC_VS:
			Calendario_S = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CALENDARIO_S), hDlg, Calen_S);
			ShowWindow(Calendario_S, show);
			EndDialog(hDlg, 0);
		}
		return true;
	case WM_CLOSE:
		salidaextrema = MessageBox(hDlg, "¿Estas seguro que deseas salir sin guardar correctamente?", "CUIDAAAAAAAAO!!!!!", MB_YESNOCANCEL | MB_ICONEXCLAMATION);
		if (salidaextrema == IDYES) {
			PostQuitMessage(0);
		}
		return true;
	case WM_DESTROY:
		EndDialog(hDlg, 0);
		return true;
	}

	return false;
}
BOOL CALLBACK Calen_S(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {

	static HWND hNombreCS = 0, hMotivoCS = 0, hPersonaCS = 0, hLugarCS = 0, hHoraCS = 0, hFechaCS = 0, hAlarmaCS = 0, hComboCS = 0, hDateTimeS = 0;
	static HWND diasmios[7];

	switch (msg)
	{
	case WM_INITDIALOG:

		hNombreCS = GetDlgItem(hDlg, IDC_NOMBRECS);
		hMotivoCS = GetDlgItem(hDlg, IDC_MOTIVOCS);
		hPersonaCS = GetDlgItem(hDlg, IDC_PERSONASCS);
		hLugarCS = GetDlgItem(hDlg, IDC_LUGARCS);
		hHoraCS = GetDlgItem(hDlg, IDC_HORACS);
		hFechaCS = GetDlgItem(hDlg, IDC_FECHACS);
		hAlarmaCS = GetDlgItem(hDlg, IDC_ALARMACS);
		hComboCS = GetDlgItem(hDlg, IDC_COMBOCPS);
		hDateTimeS = GetDlgItem(hDlg, IDC_DATETIMEPICKERS);

		diasmios[0] = GetDlgItem(hDlg, IDC_CLUNES);
		diasmios[2] = GetDlgItem(hDlg, IDC_CMARTES);
		diasmios[3] = GetDlgItem(hDlg, IDC_CMIERCOLES);
		diasmios[4] = GetDlgItem(hDlg, IDC_CJUEVES);
		diasmios[5] = GetDlgItem(hDlg, IDC_CVIERNES);
		diasmios[6] = GetDlgItem(hDlg, IDC_CSABADO);
		diasmios[7] = GetDlgItem(hDlg, IDC_CDOMINGO);

		indiceC = inicioC;
		if (inicioC != NULL) {
			do
			{
				SendMessage(hComboCS, CB_INSERTSTRING, 0, (LPARAM)indiceC->NombreC);
				indiceC = indiceC->sig;
			} while (indiceC != inicioC);
		}

		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_MDS:
			EndDialog(hDlg, 0);
			return true;

		case IDC_COMBOCPS: {
			bool encontrado = false;
			int usaaqui;
			indiceC = inicioC;
			char nombresitoweyy[30] = "";
			usaaqui = SendMessage(hComboCS, CB_GETCURSEL, 0, 0);
			if (usaaqui > -1) {
				SendMessage(hComboCS, CB_GETLBTEXT, (WPARAM)usaaqui, (LPARAM)nombresitoweyy);
				do
				{
					if (strcmp(indiceC->NombreC, nombresitoweyy) == 0) {
						encontrado = true;
						SetWindowText(hNombreCS, indiceC->NombreC);
						SetWindowText(hMotivoCS, indiceC->Motivo);
						SetWindowText(hPersonaCS, indiceC->Personas);
						SetWindowText(hLugarCS, indiceC->Lugra);
						SetWindowText(hHoraCS, indiceC->Hora);
						SetWindowText(hFechaCS, indiceC->Fecha);
						SetWindowText(hAlarmaCS, indiceC->alarma);
						indiceC = inicioC;
						break;
					}
					indiceC = indiceC->sig;

				} while (indiceC != inicioC);

				if (encontrado == false) {
					MessageBox(hDlg, "No es Posible Encontrar esta Cita", "Citas", MB_OK | MB_ICONINFORMATION);
					encontrado = false;
				}
			}
		}
						   SendMessage(hComboCS, CBN_KILLFOCUS, 0, 0);
						   return true;

		case IDC_VSS:
		case IDC_DATETIMEPICKERM: {

			for (short i = 0; i < 7; i++) {
				SetWindowText(diasmios[i], "");
			}

			char Fechita[30] = "";
			short añito;
			short mesesito;
			short diita;
			short diitan;
			short varsitoito;
			char Infosita[MAX_PATH] = "";
			GetWindowText(hDateTimeS, Fechita, 30);
			string cutMonth(Fechita);
			string Daynombre = cutMonth.substr(0, cutMonth.find_first_of(","));
			if (Daynombre == "Monday")
				diitan = 1;
			if (Daynombre == "Tuesday")
				diitan = 2;
			if (Daynombre == "Wednesday")
				diitan = 3;
			if (Daynombre == "Thursday")
				diitan = 4;
			if (Daynombre == "Friday")
				diitan = 5;
			if (Daynombre == "Saturday")
				diitan = 6;
			if (Daynombre == "Sunday")
				diitan = 7;
			string Daynumero = cutMonth.substr(cutMonth.find_last_of(",") - 2, 2);
			diita = atoi(Daynumero.c_str());
			if (diita > 10) {
				varsitoito = 3;
			}
			else {
				varsitoito = 2;
			}
			string Month = cutMonth.substr(cutMonth.find_first_of(" ") + 1, ((cutMonth.find_last_of(" ") - (1 + varsitoito)) - ((cutMonth.find_first_of(" ") + 1))));
			if (Month == "January")
				mesesito = 1;
			if (Month == "February")
				mesesito = 2;
			if (Month == "March")
				mesesito = 3;
			if (Month == "April")
				mesesito = 4;
			if (Month == "May")
				mesesito = 5;
			if (Month == "June")
				mesesito = 6;
			if (Month == "July")
				mesesito = 7;
			if (Month == "August")
				mesesito = 8;
			if (Month == "September")
				mesesito = 9;
			if (Month == "October")
				mesesito = 10;
			if (Month == "November")
				mesesito = 11;
			if (Month == "December")
				mesesito = 12;
			string Year = cutMonth.substr(cutMonth.find_last_of(" ") + 1, 4);
			añito = atoi(Year.c_str());

			do {
				if (indiceC->año == añito && indiceC->mes == mesesito)
				{
					char diadecita[15] = "";
					switch (indiceC->dian)
					{
					case 1:
						strcpy(diadecita, "Monday");
						break;
					case 2:
						strcpy(diadecita, "Tuesday");
						break;
					case 3:
						strcpy(diadecita, "Wednesday");
						break;
					case 4:
						strcpy(diadecita, "Thursday");
						break;
					case 5:
						strcpy(diadecita, "Friday");
						break;
					case 6:
						strcpy(diadecita, "Saturday");
						break;
					case 7:
						strcpy(diadecita, "Sunday");
						break;
					default:
						break;
					}
					strcat(Infosita, indiceC->NombreC);
					strcat(Infosita, "-");
					strcat(Infosita, diadecita);
					strcat(Infosita, "-");
					strcat(Infosita, indiceC->Hora);
					int ControlI = diita - diitan;
					for (short i = 0; i < 7; i++) {
						if (indiceC->dia == (ControlI + i)) {
							SetWindowText(diasmios[i], Infosita);
						}
					}
					strcpy(Infosita, "");

				}
				indiceC = indiceC->sig;
			} while (indiceC != inicioC);

		}
								  return true;

		case IDC_VM:
			ShowWindow(Calendario_M, show);
			EndDialog(hDlg, 0);
		}
		return true;
	case WM_CLOSE:
		salidaextrema = MessageBox(hDlg, "¿Estas seguro que deseas salir sin guardar correctamente?", "CUIDAAAAAAAAO!!!!!", MB_YESNOCANCEL | MB_ICONEXCLAMATION);
		if (salidaextrema == IDYES) {
			PostQuitMessage(0);
		}
		return true;
	case WM_DESTROY:
		EndDialog(hDlg, 0);
		return true;
	}


	return false;
}
BOOL CALLBACK dates(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {

	static HWND hNombreC = 0, hMotivo = 0, hPersona = 0, hLugar = 0, hHora = 0, hFecha = 0, hAlarma = 0, hComboC = 0;
	
	switch (msg)
	{
	case WM_INITDIALOG: {
		

		hNombreC = GetDlgItem(hDlg, IDC_NOMBREC);
		hMotivo = GetDlgItem(hDlg, IDC_MOTIVOC);
		hPersona = GetDlgItem(hDlg, IDC_PERSO);
		hLugar = GetDlgItem(hDlg, IDC_LUGAR);
		hHora = GetDlgItem(hDlg, IDC_DATECH);
		hFecha = GetDlgItem(hDlg, IDC_DATECF);
		hAlarma = GetDlgItem(hDlg, IDC_ALARMITA);
		hComboC = GetDlgItem(hDlg, IDC_COMBOC);


		strcat(Def1, Bienvenidoacasa);
		strcat(Def1, "\\Dive.mp3");

		strcat(Def2, Bienvenidoacasa);
		strcat(Def2, "\\sorrow.mp3");

		indiceC = inicioC;
		if (inicioC != NULL) {
			do
			{
				SendMessage(hComboC, CB_INSERTSTRING, 0, (LPARAM)indiceC->NombreC);
				indiceC = indiceC->sig;
			} while (indiceC != inicioC);
		}
	}
		return true;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_MDC:
			EndDialog(hDlg, 0);
			return true;

		case IDC_EA:
		case ID_CITAS_ELEGIRALARMA:
			ElegirArchivo(hDlg, hAlarma, 2);
			CheckDlgButton(hDlg, IDC_ECDURB, BST_CHECKED);
			CheckDlgButton(hDlg, IDC_AD1, BST_UNCHECKED);
			CheckDlgButton(hDlg, IDC_ADCU, BST_UNCHECKED);
			return true;

		case ID_CITAS_AGREGAR:
		case IDC_AGC: {
			bool exito = false;
			int varsito = 0;
			citas paso;
			indiceC = new citas;
			GetWindowText(hNombreC, paso.NombreC, 30);
			GetWindowText(hMotivo, paso.Motivo, 30);
			GetWindowText(hPersona, paso.Personas, 30);
			GetWindowText(hLugar, paso.Lugra, 30);
			GetWindowText(hHora, paso.Hora, 30);
			GetWindowText(hFecha, paso.Fecha, 30);
			GetWindowText(hAlarma, paso.alarma, MAX_PATH);
			strcpy(indiceC->NombreC, paso.NombreC);
			strcpy(indiceC->Motivo, paso.Motivo);
			strcpy(indiceC->Personas, paso.Personas);
			indiceC->avisado = false;
			strcpy(indiceC->Lugra, paso.Lugra);
			strcpy(indiceC->alarma, paso.alarma);
			if (strcmp(indiceC->alarma, "") == 0) {
				CheckDlgButton(hDlg, IDC_ECDURB, BST_CHECKED);
			}
			if (IsDlgButtonChecked(hDlg, IDC_AD1) == BST_CHECKED || strcmp(indiceC->alarma, "") == 0) {
				strcpy(indiceC->alarma, Def1);
				goto yo;
			}
			if (IsDlgButtonChecked(hDlg, IDC_ADCU) == BST_CHECKED && strcmp(indiceC->alarma, "") == 0) {
				strcpy(indiceC->alarma, Def2);
			}
			yo:
			strcpy(indiceC->Hora, paso.Hora);
			strcpy(indiceC->Fecha, paso.Fecha);
			string cutMonth(indiceC->Fecha);
			string Daynombre = cutMonth.substr(0, cutMonth.find_first_of(","));
			if (Daynombre == "Monday")
				indiceC->dian = 1;
			if (Daynombre == "Tuesday")
				indiceC->dian = 2;
			if (Daynombre == "Wednesday")
				indiceC->dian = 3;
			if (Daynombre == "Thursday")
				indiceC->dian = 4;
			if (Daynombre == "Friday")
				indiceC->dian = 5;
			if (Daynombre == "Saturday")
				indiceC->dian = 6;
			if (Daynombre == "Sunday")
				indiceC->dian = 7;
			string Daynumero = cutMonth.substr(cutMonth.find_last_of(",") - 2, 2);
			indiceC->dia = atoi(Daynumero.c_str());
			if (indiceC->dia > 10) {
				varsito = 3;
			}
			else {
				varsito = 2;
			}
			string Month = cutMonth.substr(cutMonth.find_first_of(" ") + 1, ((cutMonth.find_last_of(" ") - (1 + varsito)) - ((cutMonth.find_first_of(" ") + 1))));
			if (Month == "January")
				indiceC->mes = 1;
			if (Month == "February")
				indiceC->mes = 2;
			if (Month == "March")
				indiceC->mes = 3;
			if (Month == "April")
				indiceC->mes = 4;
			if (Month == "May")
				indiceC->mes = 5;
			if (Month == "June")
				indiceC->mes = 6;
			if (Month == "July")
				indiceC->mes = 7;
			if (Month == "August")
				indiceC->mes = 8;
			if (Month == "September")
				indiceC->mes = 9;
			if (Month == "October")
				indiceC->mes = 10;
			if (Month == "November")
				indiceC->mes = 11;
			if (Month == "December")
				indiceC->mes = 12;
			string Year = cutMonth.substr(cutMonth.find_last_of(" ") + 1, 4);
			indiceC->año = atoi(Year.c_str());
			string cutHour(indiceC->Hora);
			string hora = cutHour.substr(0, cutHour.find_first_of(":"));
			string minuto = cutHour.substr(cutHour.find_first_of(":") + 1, 2);
			string ap = cutHour.substr(cutHour.find_first_of("AP"), 1);
			indiceC->hora = atoi(hora.c_str());
			if (ap == "P")
				indiceC->hora += 12;
			if (ap == "A" && indiceC->hora == 12) {
				indiceC->hora -= 12;
			}
			indiceC->minuto = atoi(minuto.c_str());
			if (inicioC == NULL) {
				exito = true;
				inicioC = indiceC;
				indiceC->ant = inicioC;
				indiceC->sig = inicioC;
			}
			else {
				exito = true;
				indiceC->sig = inicioC;
				indiceC->ant = inicioC->ant;
				inicioC->ant->sig = indiceC;
				inicioC->ant = inicioC->ant->sig;
			}
			if (exito) {
				SetWindowText(hNombreC, "");
				SetWindowText(hMotivo, "");
				SetWindowText(hPersona, "");
				SetWindowText(hLugar, "");
				SetWindowText(hHora, "");
				SetWindowText(hFecha, "");
				SetWindowText(hAlarma, "");
				CheckDlgButton(hDlg, IDC_AD1, BST_CHECKED);
				CheckDlgButton(hDlg, IDC_ADCU, BST_UNCHECKED);
				CheckDlgButton(hDlg, IDC_ECDURB, BST_UNCHECKED);
				SendMessage(hComboC, CB_INSERTSTRING, 0, (LPARAM)paso.NombreC);
				MessageBox(hDlg, "La Cita ha sido agregado exitosamente", "Citas", MB_OK | MB_ICONINFORMATION);
			}
			else {
				MessageBox(hDlg, "La Cita NO!!!!!!!!!!! ha sido agregado exitosamente", "Citas", MB_OK | MB_ICONINFORMATION);
			}
		}
					  return true;

		case ID_CITAS_GUARDAR:
		case IDC_MOC: {
			citas paso;
			bool encontrado = false;
			int usaaqui;
			if (inicioC == NULL) {
				MessageBox(hDlg, "Debe agregar citas a su lista para modificarlas", "Citas", MB_OK | MB_ICONINFORMATION);
			}
			else {
				indiceC = inicioC;
				usaaqui = SendMessage(hComboC, CB_GETCURSEL, 0, 0);
				SendMessage(hComboC, CB_GETLBTEXT, (WPARAM)usaaqui, (LPARAM)paso.NombreC);
				do
				{
					if (strcmp(indiceC->NombreC, paso.NombreC) == 0 || strcmp(indiceC->Motivo, paso.Motivo) == 0 || strcmp(indiceC->Personas, paso.Personas) == 0) {
						encontrado = true;
						GetWindowText(hNombreC, indiceC->NombreC, 30);
						GetWindowText(hMotivo, indiceC->Motivo, 30);
						GetWindowText(hPersona, indiceC->Personas, 30);
						GetWindowText(hLugar, indiceC->Lugra, 30);
						GetWindowText(hHora, indiceC->Hora, 30);
						GetWindowText(hFecha, indiceC->Fecha, 30);
						GetWindowText(hAlarma, indiceC->alarma, MAX_PATH);
						if (IsDlgButtonChecked(hDlg, IDC_AD1) == BST_CHECKED || strcmp(indiceC->alarma, "") == 0) {
							strcpy(indiceC->alarma, Def1);
							goto ya;
						}
						if (IsDlgButtonChecked(hDlg, IDC_ADCU) == BST_CHECKED) {
							strcpy(indiceC->alarma, Def2);
						}
						ya:
						break;
					}
					else {
						indiceC = indiceC->sig;
					}
				} while (indiceC != inicioC);
			}
			if (encontrado) {
				SetWindowText(hNombreC, "");
				SetWindowText(hMotivo, "");
				SetWindowText(hPersona, "");
				SetWindowText(hLugar, "");
				SetWindowText(hHora, "");
				SetWindowText(hFecha, "");
				SetWindowText(hAlarma, "");
				CheckDlgButton(hDlg, IDC_AD1, BST_CHECKED);
				CheckDlgButton(hDlg, IDC_ADCU, BST_UNCHECKED);
				CheckDlgButton(hDlg, IDC_ECDURB, BST_UNCHECKED);
				usaaqui = SendMessage(hComboC, CB_FINDSTRING, -1, (LPARAM)paso.NombreC);
				SendMessage(hComboC, CB_DELETESTRING, (WPARAM)usaaqui, 0);
				SendMessage(hComboC, CB_INSERTSTRING, 0, (LPARAM)indiceC->NombreC);
				SetWindowText(hComboC, "");
				MessageBox(hDlg, "La Cita ha sido guardada exitosamente", "Citas", MB_OK | MB_ICONINFORMATION);
			}
			else {
				MessageBox(hDlg, "La Cita NO pudo ser encontrada", "Citas", MB_OK | MB_ICONINFORMATION);
			}
		}
					  return true;

		case ID_CITAS_ELIMINAR:
		case IDC_ELC: {
			char nombresitowey[30];
			bool encontrado = false;
			int usaaqui;
			if (inicioC == NULL) {
				MessageBox(hDlg, "Debe agregar citas a su lista para eliminarlas", "Citas", MB_OK | MB_ICONINFORMATION);
			}
			else {
				indiceC = inicioC;
				usaaqui = SendMessage(hComboC, CB_GETCURSEL, 0, 0);
				SendMessage(hComboC, CB_GETLBTEXT, (WPARAM)usaaqui, (LPARAM)nombresitowey);
				do
				{
					if (strcmp(indiceC->NombreC, nombresitowey) == 0) {
						encontrado = true;
						if (indiceC == inicioC) {
							if (indiceC != indiceC->sig) {
								inicioC = indiceC->sig;
								indiceC->ant->sig = indiceC->sig;
								indiceC->sig->ant = indiceC->ant;
							}
							else {
								inicioC = NULL;
							}
						}
						else {
							indiceC->ant->sig = indiceC->sig;
							indiceC->sig->ant = indiceC->ant;
						}

						delete indiceC;
						break;
					}
					else {
						indiceC = indiceC->sig;
					}
				} while (indiceC != inicioC);
			}
			if (encontrado) {
				SetWindowText(hNombreC, "");
				SetWindowText(hMotivo, "");
				SetWindowText(hPersona, "");
				SetWindowText(hLugar, "");
				SetWindowText(hHora, "");
				SetWindowText(hFecha, "");
				SetWindowText(hAlarma, "");
				CheckDlgButton(hDlg, IDC_AD1, BST_CHECKED);
				CheckDlgButton(hDlg, IDC_ADCU, BST_UNCHECKED);
				CheckDlgButton(hDlg, IDC_ECDURB, BST_UNCHECKED);
				usaaqui = SendMessage(hComboC, CB_FINDSTRING, -1, (LPARAM)nombresitowey);
				SendMessage(hComboC, CB_DELETESTRING, (WPARAM)usaaqui, 0);
				SetWindowText(hComboC, "");
				MessageBox(hDlg, "La Cita ha sido borrada exitosamente", "Citas", MB_OK | MB_ICONINFORMATION);
			}
			else {
				MessageBox(hDlg, "La Cita NO pudo ser encontrada", "Citas", MB_OK | MB_ICONINFORMATION);
			}
		}
					  return true;

		case IDC_COMBOC: {
			bool encontrado = false;
			int usaaqui;
			indiceC = inicioC;
			char nombresitoweyy[30] = "";
			usaaqui = SendMessage(hComboC, CB_GETCURSEL, 0, 0);
			if (usaaqui > -1) {
				SendMessage(hComboC, CB_GETLBTEXT, (WPARAM)usaaqui, (LPARAM)nombresitoweyy);
				do
				{
					if (strcmp(indiceC->NombreC, nombresitoweyy) == 0) {
						encontrado = true;
						SetWindowText(hNombreC, indiceC->NombreC);
						SetWindowText(hMotivo, indiceC->Motivo);
						SetWindowText(hPersona, indiceC->Personas);
						SetWindowText(hLugar, indiceC->Lugra);
						SetWindowText(hHora, indiceC->Hora);
						SetWindowText(hFecha, indiceC->Fecha);
						SetWindowText(hAlarma, indiceC->alarma);
						if (strcmp(indiceC->alarma, Def1) == 0) {
							CheckDlgButton(hDlg, IDC_AD1, BST_CHECKED);
							CheckDlgButton(hDlg, IDC_ADCU, BST_UNCHECKED);
							CheckDlgButton(hDlg, IDC_ECDURB, BST_UNCHECKED);
							goto yaesta;
						}
						if (strcmp(indiceC->alarma, Def2) == 0) {
							CheckDlgButton(hDlg, IDC_AD1, BST_UNCHECKED);
							CheckDlgButton(hDlg, IDC_ADCU, BST_CHECKED);
							CheckDlgButton(hDlg, IDC_ECDURB, BST_UNCHECKED);
							goto yaesta;
						}
							CheckDlgButton(hDlg, IDC_AD1, BST_UNCHECKED);
							CheckDlgButton(hDlg, IDC_ADCU, BST_UNCHECKED);
							CheckDlgButton(hDlg, IDC_ECDURB, BST_CHECKED);

						yaesta:
						indiceC = inicioC;
						break;
					}
					else {
						indiceC = indiceC->sig;
					}
				} while (indiceC != inicioC);

				if (encontrado == false) {
					MessageBox(hDlg, "No es Posible Encontrar esta Cita", "Citas", MB_OK | MB_ICONINFORMATION);
					encontrado = false;
				}
			}
		}
						 SendMessage(hComboC, CBN_KILLFOCUS, 0, 0);
						 return true;

		}
		return true;



	case WM_CLOSE:
		salidaextrema = MessageBox(hDlg, "¿Estas seguro que deseas salir sin guardar correctamente?", "CUIDAAAAAAAAO!!!!!", MB_YESNOCANCEL | MB_ICONEXCLAMATION);
		if (salidaextrema == IDYES) {
			PostQuitMessage(0);
		}
		return true;

	case WM_DESTROY:
		EndDialog(hDlg, 0);
		return true;
	}


	return false;
}
void ElegirArchivo(HWND Ventana, HWND Cajita, int filtro)
{
	char szFile[MAX_PATH];

	OPENFILENAME ofn;
	HANDLE hArchivo;

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = Ventana;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	if (filtro == 1)
		ofn.lpstrFilter = "Todos\0*.*\0Mapas de Bits\0*.BMP\0";
	else if (filtro == 2)
		ofn.lpstrFilter = "Todos\0*.*\0Sonidos MP3\0*.MP3\0";
	ofn.nFilterIndex = 2;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&ofn) == TRUE)
	{
		SetWindowText(Cajita, ofn.lpstrFile);
	}
	else
		MessageBox(0, "No eligió archivo", "Aviso", MB_OK | MB_ICONINFORMATION);


};
void JalaarchiUSU() {
	fotos *indfot = NULL;
	short coso;
	char aux = 0;
	char casita[MAX_PATH] = "";
	sprintf(casita, "%s\\ListaUsu.bin", Bienvenidoacasa);
	ifstream jiu;
	jiu.open(casita, ios::binary);
	jiu.close();
	jiu.open(casita, ios::binary);
	if (jiu.is_open()) {
		Contacto *jala;
		jiu.read((char*)&aux, sizeof(char));
		while (!jiu.eof()) {
			jiu.seekg(-1, ios::cur);
			jala = new Contacto;
			jiu.read((char*)jala->nombre, sizeof(jala->nombre));
			jiu.read((char*)jala->correo, sizeof(jala->correo));
			jiu.read((char*)jala->telefono, sizeof(jala->telefono));
			jiu.read((char*)jala->celular, sizeof(jala->celular));
			jiu.read((char*)jala->direccion, sizeof(jala->direccion));
			jiu.read((char*)jala->categoria, sizeof(jala->categoria));
			jiu.read((char*)jala->cancion, sizeof(jala->cancion));
			jiu.read((char*)&jala->numfot, sizeof(jala->numfot));
			jiu.read((char*)&jala->genero, sizeof(jala->genero));
			jala->imagenes = NULL;
			coso = jala->numfot;
			for (int i = 0; i < jala->numfot; i++) {
				indfot = new fotos;
				jiu.read((char*)indfot->foto, sizeof(indfot->foto));
				if (jala->imagenes == NULL) {
					jala->imagenes = indfot;
					indfot->ant = jala->imagenes;
					indfot->sig = jala->imagenes;
				}
				else
				{
					jala->imagenes->ant->sig = indfot;
					indfot->sig = jala->imagenes;
					indfot->ant = jala->imagenes->ant;
					jala->imagenes->ant = indfot;
				}
			}
			jala->sig = NULL;
			if (Inicio == NULL)
				Inicio = jala;
			else {
				indice = Inicio;
				while (indice->sig != NULL) {
					indice = indice->sig;
				}
				indice->sig = jala;
			}
			jiu.read((char*)&aux, sizeof(char));
		}
		jiu.close();
	}
	else {
		MessageBox(0, "No es Posible Abrir los archivos de Usuarios", "Contactos", MB_OK | MB_ICONINFORMATION);
	}
}
void MetearchiUSU() {
	indice = Inicio;
	fotos *indfot;
	char casita[MAX_PATH] = "";
	sprintf(casita, "%s\\ListaUsu.bin", Bienvenidoacasa);
	ofstream jiu;
	jiu.open(casita, ios::binary | ios::trunc);
	if (jiu.is_open()) {
		if (Inicio != 0) {
			while (indice != NULL) {
				jiu.write((char*)indice->nombre, sizeof(indice->nombre));
				jiu.write((char*)indice->correo, sizeof(indice->correo));
				jiu.write((char*)indice->telefono, sizeof(indice->telefono));
				jiu.write((char*)indice->celular, sizeof(indice->celular));
				jiu.write((char*)indice->direccion, sizeof(indice->direccion));
				jiu.write((char*)indice->categoria, sizeof(indice->categoria));
				jiu.write((char*)indice->cancion, sizeof(indice->cancion));
				jiu.write((char*)&indice->numfot, sizeof(indice->numfot));
				jiu.write((char*)&indice->genero, sizeof(indice->genero));
				indfot = indice->imagenes;
				for (int i = 0; i < indice->numfot; i++) {
					jiu.write((char*)indfot->foto, sizeof(indfot->foto));
					indfot = indfot->sig;
				}
				indice = indice->sig;
			}
		}
		jiu.close();
	}
	else {
		MessageBox(0, "No es Posible Guardar los archivos de Usuarios", "Contactos", MB_OK | MB_ICONINFORMATION);
	}
}
void JalaarchiCATE(HWND hCatego) {
	char catego[30];
	char a;
	char casita[MAX_PATH] = "";
	sprintf(casita, "%s\\ListaCate.bin", Bienvenidoacasa);
	ifstream jac;
	jac.open(casita, ios::binary);
	jac.close();
	jac.open(casita, ios::binary);
	if (jac.is_open()) {
		while (!jac.eof()) {
			jac.getline((char*)catego, sizeof(catego));
			SendMessage(hCatego, CB_ADDSTRING, 0, (LPARAM)catego);
		}
		jac.close();
	}
	else {
		MessageBox(0, "No es Posible Abrir los archivos de Categorias", "Contactos", MB_OK | MB_ICONINFORMATION);
	}

}
void JalaarchiCitas() {
	char cita[30];
	char a;
	char casita[MAX_PATH] = "";
	sprintf(casita, "%s\\ListaCitas.bin", Bienvenidoacasa);
	ifstream jc;
	jc.open(casita, ios::binary);
	jc.close();
	jc.open(casita, ios::binary);
	if (jc.is_open()) {
		jc.read((char*)&a, sizeof(char));
		while (!jc.eof()) {
			jc.seekg(-1, ios::cur);
			indiceC = new citas;
			jc.read((char*)indiceC->NombreC, sizeof(indiceC->NombreC));
			jc.read((char*)indiceC->Motivo, sizeof(indiceC->Motivo));
			jc.read((char*)indiceC->Personas, sizeof(indiceC->Personas));
			jc.read((char*)indiceC->Lugra, sizeof(indiceC->Lugra));
			jc.read((char*)indiceC->Fecha, sizeof(indiceC->Fecha));
			jc.read((char*)indiceC->Hora, sizeof(indiceC->Hora));
			jc.read((char*)indiceC->alarma, sizeof(indiceC->alarma));
			jc.read((char*)&indiceC->dian, sizeof(indiceC->dian));
			jc.read((char*)&indiceC->dia, sizeof(indiceC->dia));
			jc.read((char*)&indiceC->mes, sizeof(indiceC->mes));
			jc.read((char*)&indiceC->año, sizeof(indiceC->año));
			jc.read((char*)&indiceC->hora, sizeof(indiceC->hora));
			jc.read((char*)&indiceC->minuto, sizeof(indiceC->minuto));


			if (inicioC == NULL) {
				inicioC = indiceC;
				indiceC->ant = inicioC;
				indiceC->sig = inicioC;
			}
			else {
				indiceC->sig = inicioC;
				indiceC->ant = inicioC->ant;
				inicioC->ant->sig = indiceC;
				inicioC->ant = inicioC->ant->sig;
			}
			jc.read((char*)&a, sizeof(char));
		}
		jc.close();
	}
	else {
		MessageBox(0, "No es Posible Cargar los archivos de Citas", "Contactos", MB_OK | MB_ICONINFORMATION);
	}
}
void MetearchiCitas() {
	indiceC = inicioC;
	char casita[MAX_PATH] = "";
	sprintf(casita, "%s\\ListaCitas.bin", Bienvenidoacasa);
	ofstream jc;
	jc.open(casita, ios::binary);
	jc.close();
	jc.open(casita, ios::binary | ios::trunc);
	if (jc.is_open()) {
		if (inicioC != 0) {
			do {
				jc.write((char*)indiceC->NombreC, sizeof(indiceC->NombreC));
				jc.write((char*)indiceC->Motivo, sizeof(indiceC->Motivo));
				jc.write((char*)indiceC->Personas, sizeof(indiceC->Personas));
				jc.write((char*)indiceC->Lugra, sizeof(indiceC->Lugra));
				jc.write((char*)indiceC->Fecha, sizeof(indiceC->Fecha));
				jc.write((char*)indiceC->Hora, sizeof(indiceC->Hora));
				jc.write((char*)indiceC->alarma, sizeof(indiceC->alarma));
				jc.write((char*)&indiceC->dian, sizeof(indiceC->dian));
				jc.write((char*)&indiceC->dia, sizeof(indiceC->dia));
				jc.write((char*)&indiceC->mes, sizeof(indiceC->mes));
				jc.write((char*)&indiceC->año, sizeof(indiceC->año));
				jc.write((char*)&indiceC->hora, sizeof(indiceC->hora));
				jc.write((char*)&indiceC->minuto, sizeof(indiceC->minuto));
				indiceC = indiceC->sig;
			} while (indiceC != inicioC);
		}
		jc.close();
	}
	else {
		MessageBox(0, "No es Posible Guardar los archivos de Citas", "Contactos", MB_OK | MB_ICONINFORMATION);
	}
}