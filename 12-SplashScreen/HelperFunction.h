#pragma once

//HelperFunction

#include<Windows.h>
#include<stdio.h>

struct CurrentUser {
	int iId;
};

BOOL IsFilePresent(LPCSTR);
void RemoveWhiteSpacesFromStartAndEndOfString(char* str);
