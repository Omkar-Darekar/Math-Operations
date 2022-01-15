#include<iostream>
#include<Windows.h>
#include"InnerComponent.h"
using namespace std;

int main() {
	int iNum1, iNum2, iDIv;
	TCHAR str[255];
	HRESULT hr, hr1;
	IDivision* pIDivision = NULL;

	hr1 = CoInitialize(NULL);
	if (FAILED(hr1)) {
		cout << "CoInitialize FAILED\n";
		return 0;
	}

	hr = CoCreateInstance(CLSID_Division, NULL, CLSCTX_INPROC_SERVER, IID_IDivision, (void**)&pIDivision);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("ISum interface can not be obtained"), TEXT("Error"), MB_OK);
		//DestroyWindow(hwnd);
		return 0;
	}

	iNum1 = 50;
	iNum2 = 5;

	pIDivision->DivisionOfTwoIntegers(iNum1, iNum2, &iDIv);
	wsprintf(str, TEXT("Division of %d and %d is %d"), iNum1, iNum2, iDIv);
	MessageBox(NULL, str, TEXT("Division result"), MB_OK);

	CoUninitialize();
	return 0;
}