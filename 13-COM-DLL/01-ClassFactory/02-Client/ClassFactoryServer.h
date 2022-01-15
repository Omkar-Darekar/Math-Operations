#pragma once

class ISum :public IUnknown {
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0; //Pure Virtual Function
};

class ISubtract :public IUnknown {
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0; //Pure virtual function
};

//CLSID of SumSubtract component // {1332E0FC-4474-4622-B3AE-9276C3D0E89B}
const CLSID CLSID_SumSubtract = { 0x1332e0fc, 0x4474, 0x4622, 0xb3, 0xae, 0x92, 0x76, 0xc3, 0xd0, 0xe8, 0x9b };

//IID of ISum Interface // {8A2886B5-9F49-47FC-A657-07779014C2AF}
const IID IID_ISum = { 0x8a2886b5, 0x9f49, 0x47fc, 0xa6, 0x57, 0x7, 0x77, 0x90, 0x14, 0xc2, 0xaf };

//IID of ISubtract Interface // {EEC6058F-B33E-4505-9F93-802D36329A57}
const IID IID_ISubtract = { 0xeec6058f, 0xb33e, 0x4505, 0x9f, 0x93, 0x80, 0x2d, 0x36, 0x32, 0x9a, 0x57 };



