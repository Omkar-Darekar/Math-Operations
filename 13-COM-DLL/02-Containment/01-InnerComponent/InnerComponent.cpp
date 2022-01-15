/*
* cl.exe /c /EHsc InnerComponent.cpp
* link.exe InnerComponent.obj /DLL /DEF:InnerComponent.def user32.lib gdi32.lib ole32.lib oleaut32.lib kernel32.lib /SUBSYSTEM:WINDOWS
*/

#include <Windows.h>
#include "InnerComponent.h"

//class declaration
class CDivision :public IDivision {
private:
	long m_cRef;

public:
	CDivision();
	~CDivision();

	//IUnknown Method
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IDivision Method
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);
};

class CDivisionClassFactory :public IClassFactory {
private:
	long m_cRef;

public:
	CDivisionClassFactory();
	~CDivisionClassFactory();

	//IUnknown Method
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG AddRef(void);
	ULONG Release(void);

	//IClassFactory Method
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

//global variables
long glNumberOfActiveComponents = 0; 
long glNumberOfServerLocks = 0;

//DLL Main
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

CDivision::CDivision(void) {
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CDivision::~CDivision(void) {
	InterlockedDecrement(&glNumberOfActiveComponents);
}

HRESULT CDivision::QueryInterface(REFIID riid, void** ppv) {
	if (riid == IID_IUnknown) {
		*ppv = static_cast<IDivision*>(this);
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

ULONG CDivision::AddRef(void) {
	InterlockedIncrement(&m_cRef);
	return(S_OK);
}

ULONG CDivision::Release(void) {
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return (0);
	}
	return (m_cRef);
}

HRESULT CDivision::DivisionOfTwoIntegers(int a, int b, int* c) {
	if (b == 0)	b = 1;
	*c = a / b;
	return (S_OK);
}

CDivisionClassFactory::CDivisionClassFactory(void) {
	m_cRef = 1;
}

CDivisionClassFactory::~CDivisionClassFactory(void) {

}

HRESULT CDivisionClassFactory::QueryInterface(REFIID riid, void** ppv) {
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

ULONG CDivisionClassFactory::AddRef(void) {
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CDivisionClassFactory::Release(void) {
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return (0);
	}
	return (m_cRef);
}

HRESULT CDivisionClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv) {
	CDivision* pcDivision = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL) {
		return (CLASS_E_NOAGGREGATION);
	}

	pcDivision = new CDivision;
	if (pcDivision == NULL) {
		return (E_OUTOFMEMORY);
	}

	hr = pcDivision->QueryInterface(riid, ppv);
	pcDivision->Release();
	return (hr);
}

HRESULT CDivisionClassFactory::LockServer(BOOL fLock) {
	if (fLock) {
		InterlockedIncrement(&glNumberOfServerLocks);
	}
	else {
		InterlockedDecrement(&glNumberOfServerLocks);
	}
	return (S_OK);
}


HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv) {
	CDivisionClassFactory* pcDivisionClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_Division) {
		return (CLASS_E_CLASSNOTAVAILABLE);
	}
	pcDivisionClassFactory = new CDivisionClassFactory;
	if (pcDivisionClassFactory == NULL) {
		return (E_OUTOFMEMORY);
	}

	hr = pcDivisionClassFactory->QueryInterface(riid, ppv);
	pcDivisionClassFactory->Release();
	return (hr);
}

HRESULT __stdcall DllCanUnloadNow(void) {
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0)) {
		return (S_OK);
	}
	else {
		return (S_FALSE);
	}
}





