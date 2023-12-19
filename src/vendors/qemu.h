//
// Created by Zeropio on 19/12/2023.
//

#ifndef VMDETECT_QEMU_H
#define VMDETECT_QEMU_H

#include <stdio.h>
#include <windows.h>

// Function to check if the current host is a VM on QEMU
// Function to check if the current host is a QEMU virtual machine on Windows
int checkVQEMURegistry() {
    HKEY hKey;
    LONG result;

    // Check for the first registry key
    result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System", 0, KEY_READ, &hKey);
    if (result == ERROR_SUCCESS) {
        char biosVersion[256];
        DWORD dataSize = sizeof(biosVersion);

        // Check for the SystemBiosVersion value
        result = RegQueryValueEx(hKey, "SystemBiosVersion", NULL, NULL, (LPBYTE)&biosVersion, &dataSize);

        RegCloseKey(hKey);

        if (result == ERROR_SUCCESS && strstr(biosVersion, "QEMU") != NULL) {
            return 1; // QEMU-specific registry key and value found
        }
    }

    // Check for the second registry key
    result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DEVICEMAP\\Scsi\\Scsi Port 0\\Scsi Bus 0\\Target Id 0\\Logical Unit Id 0", 0, KEY_READ, &hKey);
    if (result == ERROR_SUCCESS) {
        char identifier[256];
        DWORD dataSize = sizeof(identifier);

        // Check for the Identifier value
        result = RegQueryValueEx(hKey, "Identifier", NULL, NULL, (LPBYTE)&identifier, &dataSize);

        RegCloseKey(hKey);

        if (result == ERROR_SUCCESS && strstr(identifier, "QEMU") != NULL) {
            return 1; // QEMU-specific registry key and value found
        }
    }

    return 0; // Not running on QEMU or registry key and value not found
}

int checkQEMU() {
    if (checkVQEMURegistry() == 1) {
        return 1;
    }
    return 0;
}

#endif //VMDETECT_QEMU_H
