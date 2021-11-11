/*
Command to run this code -> Open Visual studio Developer Command Prompt and go to Windows.cpp file location and type following command -
1. cl.exe /c /EHsc main.cpp
2. link.exe main.obj resource.res user32.lib gdi32.lib
*/

#include <windows.h>
#include<stdio.h>
#include "resource.h"
#include<iostream>

using namespace std;


//Global Function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

//Global Variable Declaration 

//Entry Point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {
	//Local Variable Declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyFirstWindow");

	//Code

	//Step 1 - Initialize wndclass structure
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//Step 2 - Register wndclass structure
	RegisterClassEx(&wndclass);

	//Step 3 - Create Window in Memory
	hwnd = CreateWindow(szAppName,
		TEXT("OAD : My First Window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	//Steps 4 - Show Window
	ShowWindow(hwnd, iCmdShow);

	//Steps 5 - To Color window
	UpdateWindow(hwnd);

	//Steps 6 - Heart of the body i.e Message loop
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static HWND dlgHwnd;
	//Code
	switch (iMsg) {
	case WM_CREATE:
		ShowWindow(hwnd, SW_SHOWMAXIMIZED);
		dlgHwnd = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(DLG), hwnd, DlgProc);

		if (dlgHwnd == NULL) {
			MessageBox(hwnd, TEXT("Dialog box creation failed"), TEXT("Dialog Error"), MB_OK);
		}
		else {
			/*MessageBox(hwnd, TEXT("Before ShowWindow() "), TEXT("Dialog Succeede"), MB_OK);*/
			ShowWindow(dlgHwnd, SW_SHOW);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void DisableFunctionality(HWND hDlg, int iId) {
	SetDlgItemText(hDlg, iId, TEXT(""));
	SendDlgItemMessage(hDlg, iId, EM_SETREADONLY, TRUE, 0);
}

void EnableFunctionality(HWND hDlg, int iId) {
	SendDlgItemMessage(hDlg, iId, EM_SETREADONLY, FALSE, 0);
}

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	TCHAR str[255], tmp[255];
	UINT uiCode, uiId;
	UINT UserId;
	static BOOL bEnableEditControls, bEnableIdEditControl;
	static HWND h1;
	//const char* Countries[] = { "Great Britain", "Senegal", "Omkar" };
	const char* Countries[10024];// = { "\0" };
	int iSizeOfArray = sizeof(Countries) / sizeof(Countries[0]);
	static FILE* fp;
	static char* pch;
	static char line[255] = { "\0" };
	static string sCity;
	switch (iMsg) {
	case WM_INITDIALOG:
		CheckRadioButton(hDlg, ID_RADIO_REGISTER, ID_RADIO_NEW, ID_RADIO_NEW);
		DisableFunctionality(hDlg, ID_EDIT_TEXT_BOX_1);
		bEnableEditControls = TRUE;
		bEnableIdEditControl = FALSE;
		//SetDlgItemText(hDlg, ID_COMBOBOX_CITY, TEXT("Omkar"));
		//SendMessage(hDlg, ID_COMBOBOX_CITY, 0, reinterpret_cast<LPARAM>((LPCTSTR)Countries[0]));
		//SendDlgItemMessage(hDlg, ID_COMBOBOX_CITY, CB_ADDSTRING, (wParam)0, TEXT("Omkar"));
		
		fp = fopen("City-State-List.txt", "r");
		if (fp == NULL) {
			
			MessageBox(hDlg, TEXT("Error while reading City-State-List.txt file\n"), TEXT("Error"), MB_OK);
			EndDialog(hDlg, 0);
		}
		
		while (fgets(line, 255, fp) != NULL) {
			//cout << "line : " << line << endl;
			pch = strtok(line, " ");
			while (pch != NULL) {
				printf("\nValue : %s", pch);
				pch = strtok(NULL, " ");
				printf("\tKey : %s\t", pch);
				sCity.append(pch);
				SendDlgItemMessage(hDlg, ID_COMBOBOX_CITY, CB_ADDSTRING, 0, (LPARAM)pch);
				break;
			}
			//free(line);
		}
		/*for (int i = 0; i < sCity.length(); i++) {
			SendDlgItemMessage(hDlg, ID_COMBOBOX_CITY, CB_ADDSTRING, 0, (LPARAM)((sCity.pop_back()));
		}*/
		
		//SendDlgItemMessage(GetDlgItem(hDlg, ID_COMBOBOX_CITY), ID_COMBOBOX_CITY, CB_ADDSTRING, 0, (LPARAM)"O");
		break;

	case WM_COMMAND:
		if (wParam == IDOK) {
			GetDlgItemText(hDlg, ID_EDIT_TEXT_BOX_1, str, 255);
			MessageBox(hDlg, str, TEXT("IDRADIO1"), MB_OK);
		}
		if (wParam == IDCANCEL) {
			EndDialog(hDlg, 0);
		}
		if (wParam == ID_RADIO_REGISTER) {
			CheckRadioButton(hDlg, ID_RADIO_REGISTER, ID_RADIO_NEW, ID_RADIO_REGISTER);

			EnableFunctionality(hDlg, ID_EDIT_TEXT_BOX_1);

			DisableFunctionality(hDlg, ID_FNAME_INPUT);
			DisableFunctionality(hDlg, ID_MNAME_INPUT);
			DisableFunctionality(hDlg, ID_LNAME_INPUT);
			bEnableEditControls = FALSE;
			bEnableIdEditControl = TRUE;
		}
		else if (wParam == ID_RADIO_DELETE) {
			CheckRadioButton(hDlg, ID_RADIO_REGISTER, ID_RADIO_NEW, ID_RADIO_DELETE);

			EnableFunctionality(hDlg, ID_EDIT_TEXT_BOX_1);

			DisableFunctionality(hDlg, ID_FNAME_INPUT);
			DisableFunctionality(hDlg, ID_MNAME_INPUT);
			DisableFunctionality(hDlg, ID_LNAME_INPUT);
			bEnableEditControls = FALSE;
			bEnableIdEditControl = TRUE;
		}
		else if (wParam == ID_RADIO_NEW) {
			//MessageBox(hDlg, TEXT("IDAUTORADIO1 selected"), TEXT("IDAUTORADIO1"), MB_OK);
			CheckRadioButton(hDlg, ID_RADIO_REGISTER, ID_RADIO_NEW, ID_RADIO_NEW);
			EnableFunctionality(hDlg, ID_FNAME_INPUT);
			EnableFunctionality(hDlg, ID_MNAME_INPUT);
			EnableFunctionality(hDlg, ID_LNAME_INPUT);

			DisableFunctionality(hDlg, ID_EDIT_TEXT_BOX_1);

			bEnableEditControls = TRUE;
			bEnableIdEditControl = FALSE;
		}
		
		/*Spot validation begins*/
		uiCode = HIWORD(wParam);
		uiId = LOWORD(wParam);
		switch (uiCode) {
		case EN_KILLFOCUS:
			if (uiId == ID_EDIT_TEXT_BOX_1) {
				if (!bEnableIdEditControl)
					break;
				GetDlgItemText(hDlg, ID_EDIT_TEXT_BOX_1, str, 255);

				//If nothing is input and want to switch to another option, allowing to do
				if (strcmp(str, "") == 0)
					break;
				bool bFlag = true;
				int i = 0;
				while (str[i] != '\0') {
					if (!(int(str[i]) >= 48 && int(str[i]) <= 57)) {
						MessageBox(hDlg, TEXT("Text can not be enter in ID field"), TEXT("Error"), MB_OK);
						SetFocus((HWND)lParam);
						bFlag = false;
						break;
					}
					i++;
				}

				if (bFlag) {
					if (!((atoi(str) >= 1) && (atoi(str) <= 99))) {
						MessageBox(hDlg, TEXT("Please enter valid ID"), TEXT("Error"), MB_OK);
						SetFocus((HWND)lParam);
					}
				}
			}

			if (uiId == ID_FNAME_INPUT || uiId == ID_MNAME_INPUT || uiId == ID_LNAME_INPUT) {
				if (!bEnableEditControls)
					break;
				int i = 0;
				int iFlag = 0;
				switch (uiId) {
				case ID_FNAME_INPUT:
					GetDlgItemText(hDlg, ID_FNAME_INPUT, str, 255);
					break;
				case ID_MNAME_INPUT:
					GetDlgItemText(hDlg, ID_MNAME_INPUT, str, 255);
					break;
				case ID_LNAME_INPUT:
					GetDlgItemText(hDlg, ID_LNAME_INPUT, str, 255);
					break;
				}

				//If nothing is input and want to switch to another option, allowing to do
				if (strcmp(str, "") == 0)
					break;
				do {
					if (!(int(str[i]) >= 65 && int(str[i]) <= 90) || str[0] == '\0') {
						MessageBox(hDlg, TEXT("Please enter valid name"), TEXT("Error"), MB_OK);
						SetFocus((HWND)lParam);
						break;
					}
					i++;
				} while (str[i] != '\0');
			}
			break;
		default:
			break;

		}
		break;
	default:
		return(FALSE);
	}
	return(TRUE);
}




