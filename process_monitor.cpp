#include <windows.h>
#include <tlhelp32.h>

bool findMyProc() {
  HANDLE hSnapshot;
  PROCESSENTRY32 pe;
  BOOL hResult;
  char* notepad = "notepad.exe";

  hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

  if (INVALID_HANDLE_VALUE == hSnapshot) return 0;

  pe.dwSize = sizeof(PROCESSENTRY32);
  hResult = Process32First(hSnapshot, &pe);
  
  while (hResult) {
    if (strcmp(notepad, pe.szExeFile) == 0) {
      return true;
      break;
    }
    hResult = Process32Next(hSnapshot, &pe);
  }

  CloseHandle(hSnapshot);
  return false;
}

char* getDisks(){
	char* lpBuffer = (char*)malloc(100 * sizeof(char));
    int test = GetLogicalDriveStrings(100, lpBuffer);
	char* result = new char[test];
	memset(result, 0, test);
	for(int i = 0; i < test; ++i){
		if(lpBuffer[i] > 64 && lpBuffer[i] < 90) strcat(result, &lpBuffer[i]);
	}
	return result;
}

//IOCTL_STORAGE_LOAD_MEDIA
//IOCTL_STORAGE_EJECT_MEDIA
void manageMedia(char* media, bool signal){
	HANDLE usb_drive;
	usb_drive = CreateFileA(media, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	long unsigned int dw;
	if(signal) DeviceIoControl(usb_drive, IOCTL_STORAGE_LOAD_MEDIA, NULL, 0, NULL, 0, &dw, NULL);
	else DeviceIoControl(usb_drive, IOCTL_STORAGE_EJECT_MEDIA, NULL, 0, NULL, 0, &dw, NULL);
}
