#include <windows.h>
#include <tlhelp32.h>

bool findMyProc(){
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

char* getLabel(char volumeLetter){
	char* volumeName = new char[3];
	volumeName[0] = volumeLetter;
	volumeName[1] = ':';
	volumeName[2] = '\\';
	char* volumeLabel = new char[1024];
	if(GetVolumeInformation(
		volumeName,
		volumeLabel,
		1024,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		0));
	return volumeLabel;
}

char* getLetter(){
	char* volumeName = new char[100];
	int buf = GetLogicalDriveStrings(100, volumeName);
	char* drive = new char[buf];
	int size = 0;
	for(int i = 0; i < buf+1; ++i){
		if((volumeName[i] > 64 && volumeName[i] < 91) || (volumeName[i] > 96 && volumeName[i] < 123)){
			drive[size] = volumeName[i];
			++size;
		}
	}
	drive[size] = '\0';
	return drive;
}

//IOCTL_STORAGE_LOAD_MEDIA
//IOCTL_STORAGE_EJECT_MEDIA
bool manageMedia(char* media, bool signal){
	HANDLE usb_drive;
	usb_drive = CreateFileA(media, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	long unsigned int dw;
	if(signal) return DeviceIoControl(usb_drive, IOCTL_STORAGE_LOAD_MEDIA, NULL, 0, NULL, 0, &dw, NULL);
	else return DeviceIoControl(usb_drive, IOCTL_STORAGE_EJECT_MEDIA, NULL, 0, NULL, 0, &dw, NULL);
}