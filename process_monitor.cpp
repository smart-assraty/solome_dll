#include <windows.h>
#include <tlhelp32.h>
#include <boost/filesystem.hpp>

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

void copyDir(char* from, char* to){
	boost::filesystem::path source = from;
	boost::filesystem::path destination = to;
	boost::filesystem::copy(source, destination);
}

int getLength(){
	char* lpBuffer = new char[100];
	int buf_length = GetLogicalDriveStrings(100, lpBuffer);
	return buf_length/4;
}

struct Drive{
	char* letter;
	unsigned long int serialNumber;
};

Drive getNumber(int i){
	char* lpBuffer = new char[100];
	int buf_length = GetLogicalDriveStrings(100, lpBuffer);
	long unsigned int serialNumber;
	Drive d;
	bool hVol = GetVolumeInformation(&lpBuffer[i], nullptr, 0, &serialNumber, nullptr, nullptr, nullptr, 0);
	if(hVol == false){
		d.letter = NULL;
		d.serialNumber = 0;
	}
	else{
		d.letter = &lpBuffer[i];
		d.serialNumber = serialNumber;
	}
	return d;
}

Drive getNumberFromLetter(char* letter){
	Drive d;
	long unsigned int serialNumber;
	bool hVol = GetVolumeInformation(letter, nullptr, 0, &serialNumber, nullptr, nullptr, nullptr, 0);
	if(hVol == false){
		d.letter = NULL;
		d.serialNumber = 0;
	}
	else{
		d.letter = letter;
		d.serialNumber = serialNumber;
	}
	return d;
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