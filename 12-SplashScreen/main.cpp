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
LRESULT CALLBACK SplashWndProc(HWND, UINT, WPARAM, LPARAM);

//Global Variable Declaration 
CurrentUser user;
TCHAR MaiWindowWrttingStr[999056] = { "\0" };
HBITMAP hSplashBMP;
LONG BitmapWidth1, BitmapHeight1;
const char SplashClassName[] = "SplashWindowClass";
HDC hSplashDC;
HDC hMemoryDC;
HWND hwnd, dlgHwnd;

//Entry Point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {
	//Local Variable Declaration
	WNDCLASSEX wndclass;
	
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

	// Initializing Splash Window 
	WNDCLASSEX    splashwc;
	splashwc.cbSize = sizeof(WNDCLASSEX);
	splashwc.style = 0;
	splashwc.lpfnWndProc = (WNDPROC)SplashWndProc;
	splashwc.cbClsExtra = 0;
	splashwc.cbWndExtra = 0;
	splashwc.hInstance = hInstance;
	splashwc.hIcon = NULL;
	splashwc.hIconSm = NULL;
	splashwc.hCursor = LoadCursor(NULL, IDC_ARROW);
	splashwc.hbrBackground = NULL;
	splashwc.lpszMenuName = NULL;
	splashwc.lpszClassName = SplashClassName;

	//Registering Splash window
	if (!RegisterClassEx(&splashwc)) {
		MessageBox(NULL, "Failed To Register The Splash Window Class.", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//Taking desktop center
	RECT DesktopRect;
	GetWindowRect(GetDesktopWindow(), &DesktopRect);

	hSplashBMP = LoadBitmap(hInstance, MAKEINTRESOURCE(ID_BITMAP));
	if (!hSplashBMP) {
		MessageBox(NULL, "Failed To Load Bitmap", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}


	BITMAP Bitmap1;
	GetObject(hSplashBMP, sizeof(BITMAP), &Bitmap1);
	BitmapWidth1 = Bitmap1.bmWidth;
	BitmapHeight1 = Bitmap1.bmHeight;
	HWND hSplashWnd1 = CreateWindowEx(0,
		SplashClassName,
		"ASTROMEDICOMP",
		WS_POPUP,
		(DesktopRect.right - BitmapWidth1) / 2,

		(DesktopRect.bottom - BitmapHeight1) / 2,

		Bitmap1.bmWidth,
		Bitmap1.bmHeight,
		NULL,
		NULL,
		hInstance,
		NULL);
	if (!hSplashWnd1) {
		MessageBox(NULL, "Splash Window Creation Failed.", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	hSplashDC = GetDC(hSplashWnd1);
	hMemoryDC = CreateCompatibleDC(hSplashDC);
	SelectObject(hMemoryDC, (HGDIOBJ)hSplashBMP);
	ShowWindow(hSplashWnd1, SW_SHOW);
	UpdateWindow(hSplashWnd1);


	////Steps 4 - Show Window
	//ShowWindow(hwnd, iCmdShow);

	////Steps 5 - To Color window
	//UpdateWindow(hwnd);

	//Steps 6 - Heart of the body i.e Message loop
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	
	FILE* fp;

	//Paint 
	HDC hdc;
	RECT rc;
	PAINTSTRUCT ps;
	TCHAR str11[] = TEXT("Hello World !!!");

	//Code
	switch (iMsg) {
	case WM_CREATE:
		break;

	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		//SetBkColor(hdc, RGB(0, 0, 0));
		//SetTextColor(hdc, RGB(0, 255, 0));
		//DrawText(hdc, MaiWindowWrttingStr, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		DrawText(hdc, MaiWindowWrttingStr, -1, &rc, DT_LEFT);

		EndPaint(hwnd, &ps);
		
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

void SetTextToTextBox(HWND hDlg, int ID, char* str) {
	SetDlgItemText(hDlg, ID, LPCSTR(str));
}

void DisableCheckBox(HWND hDlg, int ID) {
	HWND TmpCBhWnd = GetDlgItem(hDlg, ID);
	EnableWindow(TmpCBhWnd, FALSE);
}

void EnableCheckBox(HWND hDlg, int ID) {
	HWND TmpCBhWnd = GetDlgItem(hDlg, ID);
	EnableWindow(TmpCBhWnd, TRUE);
}

void DisablePushButton(HWND hDlg, int ID) {
	HWND TmpCBhWnd = GetDlgItem(hDlg, ID);
	EnableWindow(TmpCBhWnd, FALSE);
}

void EnablePushButton(HWND hDlg, int ID) {
	HWND TmpCBhWnd = GetDlgItem(hDlg, ID);
	EnableWindow(TmpCBhWnd, TRUE);
}
//
// Returns the real parent window
// Same as GetParent(), but doesn't return the owner
//
HWND GetRealParent(HWND hWnd)
{
	HWND hParent;

	//hParent = GetAncestor(hWnd, GA_ROOT);
	hParent = GetParent(hWnd);
	if (!hParent || hParent == GetDesktopWindow()) {
		MessageBox(NULL, TEXT("Desktop"), TEXT("DESKTOP"), MB_OK);
		return NULL;
	}

	return hParent;
}
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	TCHAR str[255], tmp[255];
	wchar_t State[255];
	UINT uiCode, uiId, UserId;
	static BOOL bEnableEditControls, bEnableIdEditControl, bRegisteredSelected, bDeleteSelected, bNewUserSelected;
	static HWND h1;
	const char* Countries[10024];
	int iSizeOfArray = sizeof(Countries) / sizeof(Countries[0]);
	static FILE* fp;
	static char* pch;
	static char line[255] = { "\0" };
	static string sCity;
	int TotalNumberOfItemInCombobox;
	static char FName[256] = { "\0" }, MName[256] = { "\0" }, LName[256] = { "\0" }, FileUserData[1024] = { "\0" }, CityChoosen[256] = { "\0" };
	
	//Paint 
	HDC hdc;
	RECT rc;
	PAINTSTRUCT ps;
	TCHAR str11[] = TEXT("Hello World !!!");

	switch (iMsg) {
	case WM_INITDIALOG:
		//By default New radio button check
		CheckRadioButton(hDlg, ID_RADIO_REGISTER, ID_RADIO_NEW, ID_RADIO_NEW);
		
		//Initially disabling everything
		DisableFunctionality(hDlg, ID_EDIT_TEXT_BOX_1);
		DisableFunctionality(hDlg, ID_ADDITION_TEXTBOX_1);
		DisableFunctionality(hDlg, ID_ADDITION_TEXTBOX_2);
		DisableFunctionality(hDlg, ID_SUBTRACTION_TEXTBOX_1);
		DisableFunctionality(hDlg, ID_SUBTRACTION_TEXTBOX_2);
		DisableFunctionality(hDlg, ID_MULTIPLICATION_TEXTBOX_1);
		DisableFunctionality(hDlg, ID_MULTIPLICATION_TEXTBOX_2);
		DisableFunctionality(hDlg, ID_DIVISION_TEXTBOX_1);
		DisableFunctionality(hDlg, ID_DIVISION_TEXTBOX_2);
		DisableFunctionality(hDlg, ID_SQUARE_TEXTBOX);
		DisableFunctionality(hDlg, ID_CUBE_TEXTBOX);
		DisableFunctionality(hDlg, ID_SQUAREROOT_TEXTBOX);
		DisableFunctionality(hDlg, ID_CUBEROOT_TEXTBOX);
		DisableFunctionality(hDlg, ID_SIN_TEXTBOX);
		DisableFunctionality(hDlg, ID_COS_TEXTBOX);
		//Diabling all Checkboxes
		DisableCheckBox(hDlg, ID_CHECKBOX_ADD);
		DisableCheckBox(hDlg, ID_CHECKBOX_SUB);
		DisableCheckBox(hDlg, ID_CHECKBOX_MUL);
		DisableCheckBox(hDlg, ID_CHECKBOX_DIV);
		DisableCheckBox(hDlg, ID_CHECKBOX_SQR);
		DisableCheckBox(hDlg, ID_CHECKBOX_CUBE);
		DisableCheckBox(hDlg, ID_CHECKBOX_SQR_ROOT);
		DisableCheckBox(hDlg, ID_CHECKBOX_CUBE_ROOT);
		DisableCheckBox(hDlg, ID_CHECKBOX_SIN);
		DisableCheckBox(hDlg, ID_CHECKBOX_COS);

		//Disabling Log button
		DisablePushButton(hDlg, ID_LOG_PUSHBUTTON);

		bEnableEditControls = TRUE;
		bEnableIdEditControl = FALSE;
		
		//Initially Register and Delete is False because it New user selected already
		bRegisteredSelected = FALSE;
		bDeleteSelected = FALSE;

		//Initially New user selected
		bNewUserSelected = TRUE;

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
		//Cancel button clicked
		if (wParam == IDCANCEL) {
			EndDialog(hDlg, 0);

			//Getting parent window handle and maximizing it so user can manually close main window.
			HWND hwndParent = GetRealParent(hDlg);
			ShowWindow(hwndParent, SW_SHOWMAXIMIZED);
			break;
		}

		//Log button clicked
		if (wParam == ID_LOG_PUSHBUTTON) {
			//wsprintf(MaiWindowWrttingStr, TEXT("Hello Omkar %d"), 10);
			char UserFileName[256] = { "\0" };
			sprintf(UserFileName, "%d.txt", user.iId);
			int it = 0;
			fp = fopen(UserFileName, "r");
			if (fp == NULL) {
				MessageBox(hDlg, TEXT("Unable to open current user log file. Please check user is registered."), TEXT("FILE ERROR"), MB_OK);
				break;
			}
			char line[256] = { "\0" };
			while (fgets(line, sizeof(line), fp) != 0) {
				strcat(MaiWindowWrttingStr, line);
			}
			fclose(fp);
			EndDialog(hDlg, 0);

			//Getting parent window handle and maximizing it so OS will send WM_PAINT message and log will get write on the main window.
			HWND hwndParent = GetRealParent(hDlg);
			ShowWindow(hwndParent, SW_SHOWMAXIMIZED);

			break;
		}

		if (wParam == IDOK) {
			if (bDeleteSelected) {
				//If delete selected
				GetDlgItemText(hDlg, ID_EDIT_TEXT_BOX_1, str, 255);
				wsprintf(tmp, TEXT("%s.txt"), str);
				if (DeleteFileA(LPCSTR(tmp))) {
					MessageBox(hDlg, TEXT("User successfully removed"), TEXT("Success"), MB_OK);
				}
				else {
					MessageBox(hDlg, TEXT("Error while removing user"), TEXT("Error"), MB_OK);
				}

				//Disabling Log button
				DisablePushButton(hDlg, ID_LOG_PUSHBUTTON);
			}
			else if (bRegisteredSelected) {
				//If register is selected, show its value to text box in read only format
				GetDlgItemText(hDlg, ID_EDIT_TEXT_BOX_1, str, 255);
				if (strcmp(str, "") == 0) {
					MessageBox(hDlg, TEXT("Enter valid number"), TEXT("Error"), MB_OK);
					break;
				}

				//Setting current user to structure variable
				user.iId = atoi(str);
				
				char FileName[256] = { "\0" };
				sprintf(FileName, "%s.txt", str);
				fp = fopen(FileName, "r");
				if (fp == NULL) {
					MessageBox(hDlg, TEXT("Error while retriving user."), TEXT("File access error"), MB_OK);
					break;
				}
				char line[256] = { "\0" };
				int TextLineCnt = 1;
				while (fgets(line, sizeof(line), fp) != NULL) {
					if (TextLineCnt == 1){}
					else if (TextLineCnt == 2) {
						//Setting FName, MName, LName from the file to Text box
						const char delim[] = ":";
						char* token = NULL;
						token = strtok(line, delim);
						while (token != NULL) {
							token = strtok(NULL, delim);
							break;
						}
						char FName[256] = { "\0" }, MName[256] = { "\0" }, LName[256] = { "\0" };

						sprintf(line, "%s", token);
						const char delim1[] = " ";
						token = NULL;
						token = strtok(line, delim1);
						int iTmpCnt = 1;
						while (token != NULL) {
							if (iTmpCnt == 1)
								sprintf(FName, "%s", token);
							else if (iTmpCnt == 2)
								sprintf(MName, "%s", token);
							else if (iTmpCnt == 3)
								sprintf(LName, "%s", token);
							token = strtok(NULL, delim1);
							iTmpCnt++;
						}

						SetTextToTextBox(hDlg, ID_FNAME_INPUT, FName);
						SetTextToTextBox(hDlg, ID_MNAME_INPUT, MName);
						SetTextToTextBox(hDlg, ID_LNAME_INPUT, LName);

						//Enabling CheckBox
						EnableCheckBox(hDlg, ID_CHECKBOX_ADD);
						EnableCheckBox(hDlg, ID_CHECKBOX_SUB);
						EnableCheckBox(hDlg, ID_CHECKBOX_MUL);
						EnableCheckBox(hDlg, ID_CHECKBOX_DIV);
						EnableCheckBox(hDlg, ID_CHECKBOX_SQR);
						EnableCheckBox(hDlg, ID_CHECKBOX_CUBE);
						EnableCheckBox(hDlg, ID_CHECKBOX_SQR_ROOT);
						EnableCheckBox(hDlg, ID_CHECKBOX_CUBE_ROOT);
						EnableCheckBox(hDlg, ID_CHECKBOX_SIN);
						EnableCheckBox(hDlg, ID_CHECKBOX_COS);
					}
					else if (TextLineCnt == 3){
						const char delim[] = ":";
						char* token = NULL;
						token = strtok(line, delim);
						while (token != NULL) {
							token = strtok(NULL, delim);
							break;
						}
						TotalNumberOfItemInCombobox = SendDlgItemMessage(hDlg, ID_COMBOBOX_CITY, CB_GETCOUNT, 0, 0);
						for (int i = 0; i < TotalNumberOfItemInCombobox; i++) {
							SendDlgItemMessage(hDlg, ID_COMBOBOX_CITY, CB_GETLBTEXT, i, (LPARAM)pch);
							if (strcmp(token, pch) == 0) {
								MessageBox(hDlg, (LPCSTR)token, TEXT(""), MB_OK);
								MessageBox(hDlg, (LPCSTR)pch, TEXT(""), MB_OK);
								break;
							}
							else {
								fp = fopen("_Temp.txt", "a+");
								if (fp != NULL) {
									fprintf(fp, "-%s- != -%s-", token, pch);
									fclose(fp);
								}
							}
						}
						
					}
						
					//Incrementing counter after every line read
					TextLineCnt++;
				}

				//Enabling Log button
				EnablePushButton(hDlg, ID_LOG_PUSHBUTTON);
			}
			else if (bNewUserSelected) {
				//Disabling Log button
				DisablePushButton(hDlg, ID_LOG_PUSHBUTTON);


				TCHAR FilePath[256];
				int i = 0;
				for (i = 1; i <= 100; i++) {
					wsprintf(FilePath, TEXT("%d.txt"), i);
					if (IsFilePresent((LPCSTR)FilePath))
						break;
				}

				/*Checking input string which is going to be write into file is not NULL*/
				GetDlgItemText(hDlg, ID_FNAME_INPUT, FName, 255);
				GetDlgItemText(hDlg, ID_MNAME_INPUT, MName, 255);
				GetDlgItemText(hDlg, ID_LNAME_INPUT, LName, 255);
				if (!(strcmp(FName, "")) || !(strcmp(MName, "")) || !(strcmp(LName, "")) || !(strcmp(CityChoosen, ""))) {
					MessageBox(hDlg, TEXT("Please enter valid inputs"), TEXT("Error"), MB_OK);
					break;
				}

				//Taking current date and time
				SYSTEMTIME SysTime;
				GetLocalTime(&SysTime);

				sprintf(FileUserData, "ID : %d\nName : %s %s %s\nCity : %sRegistration Date and Time : %02d-%02d-%02d %02d:%02d:%02d",
					i, FName, MName, LName, CityChoosen, SysTime.wDay, SysTime.wMonth, SysTime.wYear, SysTime.wHour, SysTime.wMinute, SysTime.wSecond);
				
				//After using variable, freeing it for further use.
				strcpy(&CityChoosen[0], "\0");
				
				//After creating user, setting combobox to -1.
				HWND hwnd = GetDlgItem(hDlg, ID_COMBOBOX_CITY);
				SendMessage(hwnd, CB_SETCURSEL, (WPARAM)-1, 0);

				fp = fopen(FilePath, "a+");
				if (fp == NULL) {
					MessageBox(hDlg, TEXT("Error while creating new user!"), TEXT("FILE ACCESS ERROR"), MB_OK);
					break;
				}
				fprintf(fp, "%s", FileUserData);
				fclose(fp);

				/*Clearing text from input box after writing it into file*/
				SetDlgItemText(hDlg, ID_FNAME_INPUT, TEXT(""));
				SetDlgItemText(hDlg, ID_MNAME_INPUT, TEXT(""));
				SetDlgItemText(hDlg, ID_LNAME_INPUT, TEXT(""));
				
				TCHAR temp[256];
				wsprintf(temp, "Your ID is %d. Please note it down carefully.", i);
				MessageBox(hDlg, temp, TEXT("Login Information"), MB_OK);

			}
			//SetDlgItemText(hDlg, ID_EDIT_TEXT_BOX_1, TEXT(""));
			SetTextToTextBox(hDlg, ID_EDIT_TEXT_BOX_1, "");
			
			break;
		}

		if (wParam == ID_RADIO_REGISTER) {
			CheckRadioButton(hDlg, ID_RADIO_REGISTER, ID_RADIO_NEW, ID_RADIO_REGISTER);
			
			EnableFunctionality(hDlg, ID_EDIT_TEXT_BOX_1);

			DisableFunctionality(hDlg, ID_FNAME_INPUT);
			DisableFunctionality(hDlg, ID_MNAME_INPUT);
			DisableFunctionality(hDlg, ID_LNAME_INPUT);
			bEnableEditControls = FALSE;
			bEnableIdEditControl = TRUE;
			bNewUserSelected = FALSE;

			//Register radio button pressed, bRegisteredSelected flag will be true.
			bRegisteredSelected = TRUE;

			bDeleteSelected = FALSE;

			//Disabling COMBOBOX
			HWND TmpHwnd = GetDlgItem(hDlg, ID_COMBOBOX_CITY);
			EnableWindow(TmpHwnd, FALSE);

			//Diabling all Checkboxes
			DisableCheckBox(hDlg, ID_CHECKBOX_ADD);
			DisableCheckBox(hDlg, ID_CHECKBOX_SUB);
			DisableCheckBox(hDlg, ID_CHECKBOX_MUL);
			DisableCheckBox(hDlg, ID_CHECKBOX_DIV);
			DisableCheckBox(hDlg, ID_CHECKBOX_SQR);
			DisableCheckBox(hDlg, ID_CHECKBOX_CUBE);
			DisableCheckBox(hDlg, ID_CHECKBOX_SQR_ROOT);
			DisableCheckBox(hDlg, ID_CHECKBOX_CUBE_ROOT);
			DisableCheckBox(hDlg, ID_CHECKBOX_SIN);
			DisableCheckBox(hDlg, ID_CHECKBOX_COS);

			//Disabling Log button
			DisablePushButton(hDlg, ID_LOG_PUSHBUTTON);
		}
		else if (wParam == ID_RADIO_DELETE) {
			CheckRadioButton(hDlg, ID_RADIO_REGISTER, ID_RADIO_NEW, ID_RADIO_DELETE);

			EnableFunctionality(hDlg, ID_EDIT_TEXT_BOX_1);

			DisableFunctionality(hDlg, ID_FNAME_INPUT);
			DisableFunctionality(hDlg, ID_MNAME_INPUT);
			DisableFunctionality(hDlg, ID_LNAME_INPUT);
			
			//Disabling COMBOBOX
			HWND TmpHwnd = GetDlgItem(hDlg, ID_COMBOBOX_CITY);
			EnableWindow(TmpHwnd, FALSE);

			bEnableEditControls = FALSE;
			bEnableIdEditControl = TRUE;

			bDeleteSelected = TRUE;

			bRegisteredSelected = FALSE;
			bNewUserSelected = FALSE;

			//Diabling all Checkboxes
			DisableCheckBox(hDlg, ID_CHECKBOX_ADD);
			DisableCheckBox(hDlg, ID_CHECKBOX_SUB);
			DisableCheckBox(hDlg, ID_CHECKBOX_MUL);
			DisableCheckBox(hDlg, ID_CHECKBOX_DIV);
			DisableCheckBox(hDlg, ID_CHECKBOX_SQR);
			DisableCheckBox(hDlg, ID_CHECKBOX_CUBE);
			DisableCheckBox(hDlg, ID_CHECKBOX_SQR_ROOT);
			DisableCheckBox(hDlg, ID_CHECKBOX_CUBE_ROOT);
			DisableCheckBox(hDlg, ID_CHECKBOX_SIN);
			DisableCheckBox(hDlg, ID_CHECKBOX_COS);

			//Disabling Log button
			DisablePushButton(hDlg, ID_LOG_PUSHBUTTON);
		}
		else if (wParam == ID_RADIO_NEW) {
			//MessageBox(hDlg, TEXT("IDAUTORADIO1 selected"), TEXT("IDAUTORADIO1"), MB_OK);
			CheckRadioButton(hDlg, ID_RADIO_REGISTER, ID_RADIO_NEW, ID_RADIO_NEW);
			EnableFunctionality(hDlg, ID_FNAME_INPUT);
			EnableFunctionality(hDlg, ID_MNAME_INPUT);
			EnableFunctionality(hDlg, ID_LNAME_INPUT);

			DisableFunctionality(hDlg, ID_EDIT_TEXT_BOX_1);	

			bNewUserSelected = TRUE;
			bEnableEditControls = TRUE;
			bEnableIdEditControl = FALSE;

			bRegisteredSelected = FALSE;
			bDeleteSelected = FALSE;

			//Enabling COMBOBOX
			HWND TmpHwnd = GetDlgItem(hDlg, ID_COMBOBOX_CITY);
			EnableWindow(TmpHwnd, TRUE);

			//Diabling all Checkboxes
			DisableCheckBox(hDlg, ID_CHECKBOX_ADD);
			DisableCheckBox(hDlg, ID_CHECKBOX_SUB);
			DisableCheckBox(hDlg, ID_CHECKBOX_MUL);
			DisableCheckBox(hDlg, ID_CHECKBOX_DIV);
			DisableCheckBox(hDlg, ID_CHECKBOX_SQR);
			DisableCheckBox(hDlg, ID_CHECKBOX_CUBE);
			DisableCheckBox(hDlg, ID_CHECKBOX_SQR_ROOT);
			DisableCheckBox(hDlg, ID_CHECKBOX_CUBE_ROOT);
			DisableCheckBox(hDlg, ID_CHECKBOX_SIN);
			DisableCheckBox(hDlg, ID_CHECKBOX_COS);

			//Disabling Log button
			DisablePushButton(hDlg, ID_LOG_PUSHBUTTON);
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
							SetTextToTextBox(hDlg, ID_EDIT_TEXT_BOX_1, "");
							break;
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

		//Add
		if (wParam == ID_CHECKBOX_ADD) {
			BOOL bChecked = IsDlgButtonChecked(hDlg, ID_CHECKBOX_ADD);
			if (bChecked) {
				//To uncheck and disabling textbox
				CheckDlgButton(hDlg, ID_CHECKBOX_ADD, BST_UNCHECKED);
				DisableFunctionality(hDlg, ID_ADDITION_TEXTBOX_1);
				DisableFunctionality(hDlg, ID_ADDITION_TEXTBOX_2);
			}
			else {
				//To check and enabling textbox
				CheckDlgButton(hDlg, ID_CHECKBOX_ADD, BST_CHECKED);
				EnableFunctionality(hDlg, ID_ADDITION_TEXTBOX_1);
				EnableFunctionality(hDlg, ID_ADDITION_TEXTBOX_2);
			}
		}

		//Sub
		if (wParam == ID_CHECKBOX_SUB) {
			BOOL bChecked = IsDlgButtonChecked(hDlg, ID_CHECKBOX_SUB);
			if (bChecked) {
				//To uncheck and disabling textbox
				CheckDlgButton(hDlg, ID_CHECKBOX_SUB, BST_UNCHECKED);
				DisableFunctionality(hDlg, ID_SUBTRACTION_TEXTBOX_1);
				DisableFunctionality(hDlg, ID_SUBTRACTION_TEXTBOX_2);
			}
			else {
				//To check and enabling textbox
				CheckDlgButton(hDlg, ID_CHECKBOX_SUB, BST_CHECKED);
				EnableFunctionality(hDlg, ID_SUBTRACTION_TEXTBOX_1);
				EnableFunctionality(hDlg, ID_SUBTRACTION_TEXTBOX_2);
			}
		}

		//Multiplication
		if (wParam == ID_CHECKBOX_MUL) {
			BOOL bChecked = IsDlgButtonChecked(hDlg, ID_CHECKBOX_MUL);
			if (bChecked) {
				//To uncheck and disabling textbox
				CheckDlgButton(hDlg, ID_CHECKBOX_MUL, BST_UNCHECKED);
				DisableFunctionality(hDlg, ID_MULTIPLICATION_TEXTBOX_1);
				DisableFunctionality(hDlg, ID_MULTIPLICATION_TEXTBOX_2);
			}
			else {
				//To check and enabling textbox
				CheckDlgButton(hDlg, ID_CHECKBOX_MUL, BST_CHECKED);
				EnableFunctionality(hDlg, ID_MULTIPLICATION_TEXTBOX_1);
				EnableFunctionality(hDlg, ID_MULTIPLICATION_TEXTBOX_2);
			}
		}

		//Division
		if (wParam == ID_CHECKBOX_DIV) {
			BOOL bChecked = IsDlgButtonChecked(hDlg, ID_CHECKBOX_DIV);
			if (bChecked) {
				//To uncheck and disabling textbox
				CheckDlgButton(hDlg, ID_CHECKBOX_DIV, BST_UNCHECKED);
				DisableFunctionality(hDlg, ID_DIVISION_TEXTBOX_1);
				DisableFunctionality(hDlg, ID_DIVISION_TEXTBOX_2);
			}
			else {
				//To check and enabling textbox
				CheckDlgButton(hDlg, ID_CHECKBOX_DIV, BST_CHECKED);
				EnableFunctionality(hDlg, ID_DIVISION_TEXTBOX_1);
				EnableFunctionality(hDlg, ID_DIVISION_TEXTBOX_2);
			}
		}

		//Square
		if (wParam == ID_CHECKBOX_SQR) {
			BOOL bChecked = IsDlgButtonChecked(hDlg, ID_CHECKBOX_SQR);
			if (bChecked) {
				//To uncheck and disabling textbox
				CheckDlgButton(hDlg, ID_CHECKBOX_SQR, BST_UNCHECKED);
				DisableFunctionality(hDlg, ID_SQUARE_TEXTBOX);
			}
			else {
				//To check and enabling textbox
				CheckDlgButton(hDlg, ID_CHECKBOX_SQR, BST_CHECKED);
				EnableFunctionality(hDlg, ID_SQUARE_TEXTBOX);
			}
		}

		//Cube
		if (wParam == ID_CHECKBOX_CUBE) {
			BOOL bChecked = IsDlgButtonChecked(hDlg, ID_CHECKBOX_CUBE);
			if (bChecked) {
				//To uncheck and disabling textbox
				CheckDlgButton(hDlg, ID_CHECKBOX_CUBE, BST_UNCHECKED);
				DisableFunctionality(hDlg, ID_CUBE_TEXTBOX);
			}
			else {
				//To check and enabling textbox
				CheckDlgButton(hDlg, ID_CHECKBOX_CUBE, BST_CHECKED);
				EnableFunctionality(hDlg, ID_CUBE_TEXTBOX);
			}
		}

		//Square root
		if (wParam == ID_CHECKBOX_SQR_ROOT) {
			BOOL bChecked = IsDlgButtonChecked(hDlg, ID_CHECKBOX_SQR_ROOT);
			if (bChecked) {
				//To uncheck and disabling textbox
				CheckDlgButton(hDlg, ID_CHECKBOX_SQR_ROOT, BST_UNCHECKED);
				DisableFunctionality(hDlg, ID_SQUAREROOT_TEXTBOX);
			}
			else {
				//To check and enabling textbox
				CheckDlgButton(hDlg, ID_CHECKBOX_SQR_ROOT, BST_CHECKED);
				EnableFunctionality(hDlg, ID_SQUAREROOT_TEXTBOX);
			}
		}

		//Cube root
		if (wParam == ID_CHECKBOX_CUBE_ROOT) {
			BOOL bChecked = IsDlgButtonChecked(hDlg, ID_CHECKBOX_CUBE_ROOT);
			if (bChecked) {
				//To uncheck and disabling textbox
				CheckDlgButton(hDlg, ID_CHECKBOX_CUBE_ROOT, BST_UNCHECKED);
				DisableFunctionality(hDlg, ID_CUBEROOT_TEXTBOX);
			}
			else {
				//To check and enabling textbox
				CheckDlgButton(hDlg, ID_CHECKBOX_CUBE_ROOT, BST_CHECKED);
				EnableFunctionality(hDlg, ID_CUBEROOT_TEXTBOX);
			}
		}

		//Sine
		if (wParam == ID_CHECKBOX_SIN) {
			BOOL bChecked = IsDlgButtonChecked(hDlg, ID_CHECKBOX_SIN);
			if (bChecked) {
				//To uncheck and disabling textbox
				CheckDlgButton(hDlg, ID_CHECKBOX_SIN, BST_UNCHECKED);
				DisableFunctionality(hDlg, ID_SIN_TEXTBOX);
			}
			else {
				//To check and enabling textbox
				CheckDlgButton(hDlg, ID_CHECKBOX_SIN, BST_CHECKED);
				EnableFunctionality(hDlg, ID_SIN_TEXTBOX);
			}
		}

		//Cosec
		if (wParam == ID_CHECKBOX_COS) {
			BOOL bChecked = IsDlgButtonChecked(hDlg, ID_CHECKBOX_COS);
			if (bChecked) {
				//To uncheck and disabling textbox
				CheckDlgButton(hDlg, ID_CHECKBOX_COS, BST_UNCHECKED);
				DisableFunctionality(hDlg, ID_COS_TEXTBOX);
			}
			else {
				//To check and enabling textbox
				CheckDlgButton(hDlg, ID_CHECKBOX_COS, BST_CHECKED);
				EnableFunctionality(hDlg, ID_COS_TEXTBOX);
			}
		}

		break;

	default:
		return(FALSE);
	}
	return(TRUE);
}



LRESULT CALLBACK SplashWndProc(HWND hWnd, UINT Msg, WPARAM  wParam, LPARAM  lParam)
{
	switch (Msg)
	{
	case WM_ERASEBKGND:

		BitBlt((HDC)wParam, 0, 0, BitmapWidth1, BitmapHeight1, hMemoryDC, 0, 0, SRCCOPY);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_SPACE)
		{
			DeleteObject(hSplashBMP);
			ReleaseDC(hWnd, hSplashDC);
			ReleaseDC(hWnd, hMemoryDC);
			DestroyWindow(hWnd);


			/*ShowWindow(hwnd, SW_SHOW);
			UpdateWindow(hwnd);
			SetForegroundWindow(hwnd);*/
			ShowWindow(hwnd, SW_SHOWMINIMIZED);
			dlgHwnd = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(DLG), hwnd, DlgProc);

			if (dlgHwnd == NULL) {
				MessageBox(hwnd, TEXT("Dialog box creation failed"), TEXT("Dialog Error"), MB_OK);
			}
			else {
				/*MessageBox(hwnd, TEXT("Before ShowWindow() "), TEXT("Dialog Succeede"), MB_OK);*/
				ShowWindow(dlgHwnd, SW_SHOW);
			}
			break;
		}
	default:
		return (DefWindowProc(hWnd, Msg, wParam, lParam));
	}
	return 0;
}


