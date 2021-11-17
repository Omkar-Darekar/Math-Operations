#include"HelperFunction.h"

BOOL IsFilePresent(LPCSTR lpFileName) {
	if (INVALID_FILE_ATTRIBUTES == GetFileAttributes(lpFileName) && GetLastError() == ERROR_FILE_NOT_FOUND) {
		//If Not pressent
		return TRUE;
	}
	return FALSE;
}
