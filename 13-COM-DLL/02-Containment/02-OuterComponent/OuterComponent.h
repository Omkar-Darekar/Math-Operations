#pragma once
class IMultiplication :public IUnknown {
public:
	virtual HRESULT __stdcall MultiplicationOfTwoNumbers(int, int, int*) = 0;
};


//CLSID for IMultiplication // {58E151CD-F417-4BB2-A636-326C390F4BCD}
const CLSID CLSID_IMultiplication = { 0x58e151cd, 0xf417, 0x4bb2, 0xa6, 0x36, 0x32, 0x6c, 0x39, 0xf, 0x4b, 0xcd };

//IID for IMultiplication // {1BB1755B-250D-4265-84E9-3CD852D29E94}
const IID IID_IMultiplication = { 0x1bb1755b, 0x250d, 0x4265, 0x84, 0xe9, 0x3c, 0xd8, 0x52, 0xd2, 0x9e, 0x94 };



