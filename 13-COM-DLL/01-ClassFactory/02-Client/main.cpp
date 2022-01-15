#include<iostream>
#include<Windows.h>
#include"ClassFactoryServer.h"

using namespace std;

//Global Variables
ISum* pISum = NULL;
ISubtract* pISubtract = NULL;

int main() {

	HRESULT hr;
	hr = CoInitialize(NULL);
	if (FAILED(hr)) {
		cout << "CoInitialize FAILED\n";
		return 0;
	}

	HRESULT hr1;
	hr1 = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum);
	if (FAILED(hr1)) {
		cout << "\n" << GetLastError() << endl;
		cout << "CoCreateInstance FAILED\n";
		return 0;
	}
	int a = 100, b = 90, iSum = 0;
	pISum->SumOfTwoIntegers(a, b, &iSum);
	cout << "Sum : " << iSum << endl;

	hr1 = pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);
	if (FAILED(hr1)) {
		cout << "IID_ISubtract FAILED\n";
		return 0;
	}

	pISum->Release();
	pISum = NULL;

	int iSub = 0;
	pISubtract->SubtractionOfTwoIntegers(a, b, &iSub);
	cout << "Sub : " << iSub << endl;
	pISubtract->Release();
	pISubtract = NULL;

	//Uninitialize
	CoUninitialize();

	return 0;
}