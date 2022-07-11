#include <windows.h>
#include <tlhelp32.h>

bool findMyProc();
char* getLabel(char volumeLetter);
char* getLetter();
bool manageMedia(char* media, bool signal);