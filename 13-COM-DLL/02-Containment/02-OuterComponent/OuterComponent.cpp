/*
* cl.exe /c /EHsc OuterComponent.cpp
* link.exe OuterComponent.obj /DLL /DEF:OuterComponent.def user32.lib ole32.lib oleaut32.lib gdi32.lib /SUBSYSTEM:WINDOWS
*/

#include<Windows.h>
//#include"InnerOuterComponentHeaderFileForClient.h"
#include"InnerComponent.h"
#include "OuterComponent.h"

//class declaration
class CMultiplication : public IMultiplication, IDivision {
private:
	long m_cRef;
	IDivision* m_pIDivision;
public:
	//Constructor and destructor of CMultiplication
	CMultiplication(void);
	~CMultiplication(void);

	//IUnknown Methods
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IMultiplication Method
	HRESULT __stdcall MultiplicationOfTwoNumbers(int, int, int*);

	//IDivision Method
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);

	//Custom method for inner component creation
	HRESULT __stdcall InitializeInnerComponent(void);
};

class CMultiplicationClassFactory :public IClassFactory {
private:
	long m_cRef;
public:
	//Constructor and Destructor
	CMultiplicationClassFactory(void);
	~CMultiplicationClassFactory(void);

	//IUnknown Method
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IClass Factory Method
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

//global variables
long glNumberOfActiveComponents = 0;
long glNumberOfServerLock = 0;

//DllMain
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved) {
	//code
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return (TRUE);
}

CMultiplication::CMultiplication(void) {
	//Initialization of private variable
	m_pIDivision = NULL;

	InterlockedIncrement(&glNumberOfActiveComponents);
}

CMultiplication::~CMultiplication(void) {
	InterlockedDecrement(&glNumberOfActiveComponents);
	if (m_pIDivision) {
		m_pIDivision->Release();
		m_pIDivision = NULL;
	}
}

HRESULT CMultiplication::QueryInterface(REFIID riid, void** ppv) {
	if (riid == IID_IUnknown) {
		*ppv = static_cast<IMultiplication*>(this);
	}
	else if (riid == IID_IMultiplication) {
		*ppv = static_cast<IMultiplication*>(this);
	}
	else if (riid == IID_IDivision) {
		*ppv = static_cast<IDivision*>(this);
	}
	else {
		*ppv = NULL;
		return (E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return (S_OK);
}

ULONG CMultiplication::AddRef(void) {
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CMultiplication::Release(void) {
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return (0);
	}
	return(m_cRef);
}

HRESULT CMultiplication::MultiplicationOfTwoNumbers(int a, int b, int* c) {
	*c = a * b;
	return (S_OK);
}

HRESULT CMultiplication::DivisionOfTwoIntegers(int a, int b, int* c) {
	m_pIDivision->DivisionOfTwoIntegers(a, b, c);
	return (S_OK);
}

HRESULT CMultiplication::InitializeInnerComponent(void) {
	HRESULT hr;
	hr = CoCreateInstance(CLSID_Division, NULL, CLSCTX_INPROC_SERVER, IID_IDivision, (void**)&m_pIDivision);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("IDivision Interface can not be obtained from INNER Component"), TEXT("ERROR"), MB_OK);
		return (E_FAIL);
	}
	return (S_OK);
}

//CMultiplicationClassFactory Methods

CMultiplicationClassFactory::CMultiplicationClassFactory(void) {
	m_cRef = 1;
}

CMultiplicationClassFactory::~CMultiplicationClassFactory(void) {

}

HRESULT CMultiplicationClassFactory::QueryInterface(REFIID riid, void** ppv) {
	if (riid == IID_IUnknown) {
		*ppv = static_cast<IClassFactory*>(this);
	}
	else if (riid == IID_IClassFactory) {
		*ppv = static_cast<IClassFactory*>(this);
	}
	else {
		*ppv = NULL;
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return (S_OK);
}

ULONG CMultiplicationClassFactory::AddRef(void) {
	InterlockedIncrement(&m_cRef);
	return (S_OK);
}

ULONG CMultiplicationClassFactory::Release(void) {
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return (0);
	}
	return (m_cRef);
}

HRESULT CMultiplicationClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv) {
	CMultiplication* pCMultiplication = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL) {
		return (CLASS_E_NOAGGREGATION);
	}

	pCMultiplication = new CMultiplication;
	if (pCMultiplication == NULL) {
		return (E_OUTOFMEMORY);
	}

	hr = pCMultiplication->InitializeInnerComponent();
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("FAILED to initialize INNER component"), TEXT("ERROR"), MB_OK);
		pCMultiplication->Release();
		return (hr);
	}

	hr = pCMultiplication->QueryInterface(riid, ppv);
	pCMultiplication->Release();
	return (hr);
}

HRESULT CMultiplicationClassFactory::LockServer(BOOL fLock) {
	if (fLock) {
		InterlockedIncrement(&glNumberOfServerLock);
	}
	else {
		InterlockedDecrement(&glNumberOfServerLock);
	}

	return (S_OK);
}

//DLL Export Function
HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv) {
	CMultiplicationClassFactory* pCMultiplicationClassFactory = NULL;
	HRESULT hr;
	if (rclsid != CLSID_IMultiplication) {
		return (CLASS_E_CLASSNOTAVAILABLE);
	}
	pCMultiplicationClassFactory = new CMultiplicationClassFactory;
	if (pCMultiplicationClassFactory == NULL) {
		return (E_OUTOFMEMORY);
	}
	hr = pCMultiplicationClassFactory->QueryInterface(riid, ppv);
	pCMultiplicationClassFactory->Release();
	return(hr);
}

HRESULT __stdcall DllCanUnloadNow(void) {
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLock == 0)) {
		return (S_OK);
	}
	else {
		return (S_FALSE);
	}
}
