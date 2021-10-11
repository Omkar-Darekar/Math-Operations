/*
Command to run this code -> Open Visual studio Developer Command Prompt and go to Windows.cpp file location and type following command -
1. cl.exe /c /EHsc Windows.cpp
2. link.exe Windows.obj user32.lib gdi32.lib
*/

#include <windows.h>
#define DLG 101

//Global Function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

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

BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	switch (iMsg) {
	case WM_INITDIALOG:
		//SetFocus(GetDlgItem(hDlg, IDCANCEL));
		SetFocus(hDlg);
		break;
	case WM_COMMAND:
		if (wParam == IDOK) {
			EndDialog(hDlg, 0);
		}
		break;
	default:
		return(FALSE);
	}
	return(TRUE);
}