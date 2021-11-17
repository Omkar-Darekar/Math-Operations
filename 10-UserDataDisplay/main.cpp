/*
Command to run this code -> Open Visual studio Developer Command Prompt and go to Windows.cpp file location and type following command -
1. cl.exe /c /EHsc main.cpp
2. link.exe main.obj resource.res user32.lib gdi32.lib
*/

#include <windows.h>
#include<stdio.h>
#include "resource.h"
#include<iostream>
#include<algorithm>
#include<map>
#include <iterator>

#include "HelperFunction.h"
//#include <bits/stdc++.h>

using namespace std;


//Global Function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

//Global Variable Declaration 
// 
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

// Function to check the small string
bool compare(string& s1, string& s2)
{
	return s1.size() < s2.size();
}

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	TCHAR str[255], tmp[255];
	wchar_t State[255];
	UINT uiCode, uiId, UserId;
	static BOOL bEnableEditControls, bEnableIdEditControl, bRegisteredSelected, bDeleteSelected;
	static HWND h1;
	const char* Countries[10024];
	int iSizeOfArray = sizeof(Countries) / sizeof(Countries[0]);
	static FILE* fp;
	static char* pch;
	static char line[255] = { "\0" };
	static string sCity;
	int TotalNumberOfItemInCombobox;
	static char FName[256] = { "\0" }, MName[256] = { "\0" }, LName[256] = { "\0" }, FileUserData[1024] = { "\0" }, CityChoosen[256] = { "\0" };
	

	switch (iMsg) {
	case WM_INITDIALOG:
		CheckRadioButton(hDlg, ID_RADIO_REGISTER, ID_RADIO_NEW, ID_RADIO_NEW);
		DisableFunctionality(hDlg, ID_EDIT_TEXT_BOX_1);
		bEnableEditControls = TRUE;
		bEnableIdEditControl = FALSE;
		
		//Initially Register and Delete 
		bRegisteredSelected = FALSE;
		bDeleteSelected = FALSE;

		fp = fopen("City-State-List.txt", "r");
		if (fp == NULL) {
			
			MessageBox(hDlg, TEXT("Error while reading City-State-List.txt file\n"), TEXT("Error"), MB_OK);
			EndDialog(hDlg, 0);
		}
		
		while (fgets(line, 255, fp) != NULL) {
			pch = strtok(line, " ");
			while (pch != NULL) {
				//pch = KEY
				pch = strtok(NULL, " ");
				// pch = Value
				//sCity.append(pch);
				SendDlgItemMessage(hDlg, ID_COMBOBOX_CITY, CB_ADDSTRING, 0, (LPARAM)pch);
				break;
			}
		}
		TotalNumberOfItemInCombobox = SendDlgItemMessage(hDlg, ID_COMBOBOX_CITY, CB_GETCOUNT, 0, 0);
		for (int i = 0; i < TotalNumberOfItemInCombobox; i++) {
			SendDlgItemMessage(hDlg, ID_COMBOBOX_CITY, CB_GETLBTEXT, i, (LPARAM)pch);
			sCity.append(pch);
		}
		break;

	case WM_COMMAND:
		if (wParam == IDOK) {
			TCHAR FilePath[256];
			int i = 0;
			for (i = 1; i <= 100; i++) {
				wsprintf(FilePath, TEXT("%d.txt"), i);
				if (IsFilePresent((LPCSTR)FilePath))
					break;
			}
			/*Checking input string which is going to be write into file is not NULL*/
			if (!(strcmp(FName, "")) || !(strcmp(MName, "")) || !(strcmp(LName, "")) || !(strcmp(CityChoosen, ""))) {
				MessageBox(hDlg, TEXT("Please enter valid inputs"), TEXT("Error"), MB_OK);
				break;
			}
			sprintf(FileUserData, "ID : %d\n%s %s %s\nCity : %s", i, FName, MName, LName, CityChoosen);
			fp = fopen(FilePath, "a+");
			if (fp == NULL) {
				MessageBox(hDlg, TEXT("Error while creating new user!"), TEXT("ERROR"), MB_OK);
				break;
			}
			fprintf(fp, "%s", FileUserData);
			fclose(fp);

			/*Clearing text from input box after writing it into file*/
			DisableFunctionality(hDlg, ID_FNAME_INPUT);
			DisableFunctionality(hDlg, ID_MNAME_INPUT);
			DisableFunctionality(hDlg, ID_LNAME_INPUT);
			
			TCHAR temp[256];
			wsprintf(temp, "Your ID is %d. Please note it down carefully.", i);
			MessageBox(hDlg, temp, TEXT("Information"), MB_OK);

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

			//Register radio button pressed, bRegisteredSelected flag will be true.
			bRegisteredSelected = TRUE;

			bDeleteSelected = FALSE;
		}
		else if (wParam == ID_RADIO_DELETE) {
			CheckRadioButton(hDlg, ID_RADIO_REGISTER, ID_RADIO_NEW, ID_RADIO_DELETE);

			EnableFunctionality(hDlg, ID_EDIT_TEXT_BOX_1);

			DisableFunctionality(hDlg, ID_FNAME_INPUT);
			DisableFunctionality(hDlg, ID_MNAME_INPUT);
			DisableFunctionality(hDlg, ID_LNAME_INPUT);
			bEnableEditControls = FALSE;
			bEnableIdEditControl = TRUE;

			bDeleteSelected = TRUE;

			bRegisteredSelected = FALSE;
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

			bRegisteredSelected = FALSE;
			bDeleteSelected = FALSE;
		}
		

		/* City-State Combobox*/
		uiCode = HIWORD(wParam);
		uiId = LOWORD(wParam);
		switch (uiCode) {
		case CBN_SELCHANGE:
			if (uiId == ID_COMBOBOX_CITY) {
				int iIndexOfSelectedOption = SendDlgItemMessage(hDlg, ID_COMBOBOX_CITY, CB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hDlg, ID_COMBOBOX_CITY, CB_GETLBTEXT, iIndexOfSelectedOption, (LPARAM)pch);
				//MessageBox(hDlg, (LPCTSTR)pch, TEXT("COMBO BOX"), MB_OK);
				strcpy(CityChoosen, pch);
			}
			break;

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
						break;
					}
					else {
						char FilePath[256] = { "\0" };
						sprintf(FilePath, "%d.txt", atoi(str));

						//checking user is registered or not
						if (IsFilePresent((LPCSTR)FilePath)) {
							MessageBox(hDlg, TEXT("User is not registered.\nPlease register first"), TEXT("User not available"), MB_OK);
							SetFocus((HWND)lParam);
							break;
						}
						if (wParam == ID_RADIO_REGISTER) {
							MessageBox(hDlg, TEXT("Regester selected"), TEXT("OK"), MB_OK);
						}
						else if (wParam == ID_RADIO_DELETE) {
							MessageBox(hDlg, TEXT("Delete selected"), TEXT("OK"), MB_OK);
						}
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
					strcpy(FName, str);
					break;
				case ID_MNAME_INPUT:
					GetDlgItemText(hDlg, ID_MNAME_INPUT, str, 255);
					strcpy(MName, str);
					break;
				case ID_LNAME_INPUT:
					GetDlgItemText(hDlg, ID_LNAME_INPUT, str, 255);
					strcpy(LName, str);
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




