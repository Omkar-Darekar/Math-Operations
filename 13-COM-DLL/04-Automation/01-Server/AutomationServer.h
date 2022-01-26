#pragma once

class ISqaureCubeRoot : public IDispatch {
public:
	virtual RESULT __stdcall SquareRoot(float, float*) = 0; //Pure virtual function

	virtual HRESULT __stdcall CubeRoot(float, float*) = 0; //Pure virtual function
};

//CLSID of ISqaureCubeRoot // {C73675EF-2E24-4FAA-ACBD-30AE1610B506}
const CLSID CLSID_ISqaureCubeRoot = { 0xc73675ef, 0x2e24, 0x4faa, 0xac, 0xbd, 0x30, 0xae, 0x16, 0x10, 0xb5, 0x6 };

//IID of SquareRoot Interface // {0080A7F8-FCD4-4925-97AD-D9363DC1498A}
const IID IID_SquareRoot = { 0x80a7f8, 0xfcd4, 0x4925, 0x97, 0xad, 0xd9, 0x36, 0x3d, 0xc1, 0x49, 0x8a };



