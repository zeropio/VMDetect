//
// Created by Zeropio on 19/12/2023.
//

#ifndef VMDETECT_VBOX_H
#define VMDETECT_VBOX_H

#include <stdio.h>
#include <Windows.h>

// Function to check if VirtualBox Guest Additions processes are running
int checkVirtualBoxProcesses() {
    FILE *fp;
    char buffer[128];

    // Run the command to get the process list
    fp = _popen("tasklist", "r");
    if (fp == NULL) {
        perror("Error opening process list");
        exit(EXIT_FAILURE);
    }

    // Check if VirtualBox Guest Additions processes are present
    while (fgets(buffer, sizeof(buffer) - 1, fp) != NULL) {
        if (strstr(buffer, "VBoxClient.exe") != NULL || strstr(buffer, "VBoxTray.exe") != NULL) {
            _pclose(fp);
            return 1; // VirtualBox Guest Additions process found
        }
    }

    _pclose(fp);
    return 0; // No VirtualBox Guest Additions process found
}

// Function to check if VirtualBox registry keys are present
int checkVirtualBoxRegistry() {
    HKEY hKey;
    const char* vboxKey = "SOFTWARE\\Oracle\\VirtualBox";
    LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, vboxKey, 0, KEY_READ, &hKey);

    if (result == ERROR_SUCCESS) {
        RegCloseKey(hKey);
        return 1; // VirtualBox registry key found
    }

    return 0; // VirtualBox registry key not found
}

int checkVBox() {
    if (checkVirtualBoxProcesses() == 1 || checkVirtualBoxRegistry() == 1) {
        return 1;
    }
    return 0;
}

#endif //VMDETECT_VBOX_H
