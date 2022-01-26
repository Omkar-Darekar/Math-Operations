#include<Windows.h>
#include<stdio.h>
#include<math.h>
#include"AutomationServer.h"

class CSquareCubeRoot :public ISqaureCubeRoot {
private:
	long m_cRef;
	ITypeInfo* m_pITypeInfo;

public:
	CSquareCubeRoot(void);
	~CSquareCubeRoot(void);

	//IUnknown Method
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IDispatch Method
	HRESULT __stdcall GetTypeInfoCount(UINT*);
	HRESULT __stdcall GetTypeInfo(UINT*);
	HRESULT __stdcall GetTypeInfo(UINT, LCID, ITypeInfo**);
	HRESULT __stdcall GetIDsOfNames(REFIID, LPOLESTR*, UINT, LCID, DISPID*);
	HRESULT __stdcall Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*);

	//Sqaure Root
	HRESULT __stdcall SquareRoot(float, float*);

	//Cube Root
	HRESULT __stdcall CubeRoot(float, float*);

	//Custom Method
	HRESULT InitInstance(void);
};

//class Factory
class CSquareCubeClassFactory :public IClassFactory {
private:
	long m_cRef;

public:
	CSquareCubeClassFactory(void);
	~CSquareCubeClassFactory(void);

	//IUnknown Method
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IClassFactory Method
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

//Global Method
long  glNumberOfActiveComponents = 0;
long glNumberOfServerLock = 0;

// {35EA64BD-089F-4B63-8FE0-163F16AFFAEC}
const GUID LIBID_AutomationServer = { 0x35ea64bd, 0x89f, 0x4b63, 0x8f, 0xe0, 0x16, 0x3f, 0x16, 0xaf, 0xfa, 0xec };

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


CSquareCubeRoot::CSquareCubeRoot(void) {
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CSquareCubeRoot::~CSquareCubeRoot(void) {
	InterlockedDecrement(&glNumberOfActiveComponents);
}

//CSquareCubeRoot IUnknown Property
HRESULT CSquareCubeRoot::QueryInterface(REFIID riid, void** ppv) {
	if (riid == IID_IUnknown) {
		*ppv = static_cast<ISqaureCubeRoot*>(this);
	}
	else if (riid == IID_IDispatch) {
		*ppv = static_cast<ISqaureCubeRoot*>(this);
	}
	else if (riid == IID_SquareRoot) {
		*ppv = static_cast<ISqaureCubeRoot*>(this);
	}
	else {
		*ppv = NULL;
		MessageBox(NULL, TEXT("NO Interface found at [Query Interface]"), TEXT("ERROR"), MB_OK);
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return (S_OK);
}

ULONG CSquareCubeRoot::AddRef(void) {
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSquareCubeRoot::Release(void) {
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		m_pITypeInfo->Release();
		m_pITypeInfo = NULL;
		delete(this);
		return (0);
	}
	return (m_cRef);
}

HRESULT CSquareCubeRoot::SquareRoot(float a, float* b) {
	*b = sqrtf(a);
	return(S_OK);
}

HRESULT CSquareCubeRoot::CubeRoot(float a, float* b) {
	*b = cbrtf(a);
	return (S_OK);
}

HRESULT CSquareCubeRoot::InitInstance(void) {
	void ComErrorDesciptionString(HWND, HRESULT);

	HRESULT hr;

	ITypeLib* pITypeLib = NULL;

	if (m_pITypeInfo == NULL) {
		hr = LoadRegTypeLib(LIBID_AutomationServer, 1, 0, LANG_NEUTRAL, &pITypeLib);
		if (FAILED(hr)) {
			MessageBox(NULL, TEXT("Error at InitInstance:LoadRegTypeLib"), TEXT("ERROR"), MB_OK);
			ComErrorDesciptionString(NULL, hr);
			return (hr);
		}
		hr = pITypeLib->GetTypeInfoOfGuid(IID_SquareRoot, &m_pITypeInfo);
		if (FAILED(hr)) {
			MessageBox(NULL, TEXT("Error at InitInstance:GetTypeInfoOfGuid"), TEXT("ERROR"), MB_OK);
			ComErrorDesciptionString(NULL, hr);
			pITypeLib->Release();
			return (hr);
		}

		pITypeLib->Release();
	}

	return(S_OK);
}

CSquareCubeClassFactory::CSquareCubeClassFactory(void) {
	m_cRef = 1;
}

CSquareCubeClassFactory::~CSquareCubeClassFactory(void) {

}

HRESULT CSquareCubeClassFactory::QueryInterface(REFIID riid, void** ppv) {
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

HRESULT CSquareCubeClassFactory::AddRef(void) {
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CSquareCubeClassFactory::Release(void) {
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete (this);
		return (0);
	}
	return (m_cRef);
}

HRESULT CSquareCubeClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv) {
	CSquareCubeRoot* pCSquareCubeRoot = NULL;
	HRESULT hr;

	if (pCSquareCubeRoot != NULL) {
		MessageBox(NULL, TEXT("pCSquareCubeRoot != NULL"), TEXT("ERROR"), MB_OK);
		return (CLASS_E_NOAGGREGATION);
	}

	pCSquareCubeRoot = new CSquareCubeRoot;
	if (pCSquareCubeRoot == NULL) {
		MessageBox(NULL, TEXT("pCSquareCubeRoot == NULL"), TEXT("ERROR"), MB_OK);
		return(E_OUTOFMEMORY);
	}



}


