#include <windows.h>
#include <tlhelp32.h>
#include <boost/filesystem.hpp>

struct Drive{
	char* letter;
	unsigned long int serialNumber;
};

bool findMyProc();
int getLength();
void copyDir(char* from, char* to);
Drive getNumber(int i);
Drive getNumberFromLetter(char* letter);
bool manageMedia(char* media, bool signal);