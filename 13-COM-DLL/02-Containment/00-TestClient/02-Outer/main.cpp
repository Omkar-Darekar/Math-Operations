#include<iostream>
#include<Windows.h>
#include"InnerOuterComponentHeaderFileForClient.h"
using namespace std;

int main() {
	int iNum1, iNum2, iDIv, iMul;
	TCHAR str[255];
	HRESULT hr, hr1;
	IDivision* pIDivision = NULL;
	IMultiplication* pIMultiplication = NULL;

	hr1 = CoInitialize(NULL);
	if (FAILED(hr1)) {
		cout << "CoInitialize FAILED\n";
		return 0;
	}

	//hr = CoCreateInstance(CLSID_Division, NULL, CLSCTX_INPROC_SERVER, IID_IDivision, (void**)&pIDivision);
	hr = CoCreateInstance(CLSID_IMultiplication, NULL, CLSCTX_INPROC_SERVER, IID_IMultiplication, (void**)&pIMultiplication);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("IMultiplication interface can not be obtained"), TEXT("Error"), MB_OK);
		//DestroyWindow(hwnd);
		return 0;
	}

	iNum1 = 50;
	iNum2 = 5;
	pIMultiplication->MultiplicationOfTwoNumbers(iNum1, iNum2, &iMul);
	wsprintf(str, TEXT("Multiplication of %d and %d is %d"), iNum1, iNum2, iMul);
	MessageBox(NULL, str, TEXT("Division result"), MB_OK);

	hr = pIMultiplication->QueryInterface(IID_IDivision, (void**)&pIDivision);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("IDivision interface can not be obtained"), TEXT("Error"), MB_OK);
		//DestroyWindow(hwnd);
		return 0;
	}

	pIMultiplication->Release();

	pIDivision->DivisionOfTwoIntegers(iNum1, iNum2, &iDIv);
	wsprintf(str, TEXT("Division of %d and %d is %d"), iNum1, iNum2, iDIv);
	MessageBox(NULL, str, TEXT("Division result"), MB_OK);

	pIDivision->Release();

	CoUninitialize();
	return 0;
}