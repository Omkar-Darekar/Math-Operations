#pragma once

class IDivision :public IUnknown {
public:
	//IDivision methods
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0; //Pure virtual function
};

//CLSID of Division // {F3EE55FB-1DD7-4813-99C6-A3D54D9E4512}
const CLSID CLSID_Division = { 0xf3ee55fb, 0x1dd7, 0x4813, 0x99, 0xc6, 0xa3, 0xd5, 0x4d, 0x9e, 0x45, 0x12 };


//IID of IDivision Interface // {23EBAB8F-8952-423C-A1C0-21F6F55DEC9F}
const IID IID_IDivision = { 0x23ebab8f, 0x8952, 0x423c, 0xa1, 0xc0, 0x21, 0xf6, 0xf5, 0x5d, 0xec, 0x9f };


