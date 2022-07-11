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

struct Drives{
	char* volumeName;
	char* volumeLabel;
};


struct Drive getDrive(char* volumeName){
	char* volumeLabel = new char[100];
	GetVolumeInformation(
		volumeName,
		volumeLabel,
		100,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		0
	);
	struct Drive drive;
	drive.volumeName = volumeName;
	drive.volumeLabel = volumeLabel;
	strcat(drive.volumeLabel, '\0');
	return drive;
}

Drive* getDrives(){
	char* volumeName = new char[100];
	int buf = GetLogicalDriveStrings(100, volumeName);
	Drive* drives = new Drive[buf/4];
	int size = 0;
	for(int i = 0; i < buf+1; i += 4){
		Drive d = getDrive(&volumeName[i]);
		drives[size] = d;
		++size;
	}
	return drives;
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