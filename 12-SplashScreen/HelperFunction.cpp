#include"HelperFunction.h"


BOOL IsFilePresent(LPCSTR lpFileName) {
	if (INVALID_FILE_ATTRIBUTES == GetFileAttributes(lpFileName) && GetLastError() == ERROR_FILE_NOT_FOUND) {
		//If Not pressent
		return TRUE;
	}
	return FALSE;
}

void RemoveWhiteSpacesFromStartAndEndOfString(char* str) {
	int i = 0;
	bool bStart = true, bEnd = true;
	int iLen = strlen(str);
	int ind = 0;
	while (str[i]) {
		if (bStart && (int(str[i])) == 32) {
			ind = i;
		}
		else {
			bStart = false;
		}
		if (bEnd && (int(str[iLen - (i + 1)]) == 32)) {
			sprintf(&str[iLen - (i + 1)], "\0");
		}
		else if (int(str[iLen - (i + 1)]) >= 65 && int(str[iLen - (i + 1)]) <= 122) {
			bEnd = false;
		}
		i++;
	}
	i = 0;
	char str1[256] = { "\0" };
	while ((ind != 0) && str[++ind]) {
		sprintf(&str1[i], "%s", &str[ind]);
		i++;
	}
	if (ind != 0) {
		sprintf(str, "%s", str1);
	}
}
