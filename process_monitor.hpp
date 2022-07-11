#include <windows.h>
#include <tlhelp32.h>
#include <string.h>

struct Drive{
	char* volumeName;
	char* volumeLabel;
};

bool findMyProc();
struct Drive getDrive(char* volumeName);
bool manageMedia(char*, bool);
char* getDrives()