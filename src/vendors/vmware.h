//
// Created by Zeropio on 19/12/2023.
//

#ifndef VMDETECT_VMWARE_H
#define VMDETECT_VMWARE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Function to check if VMware Tools processes are running
int checkVMwareProcesses() {
    FILE *fp;
    char buffer[128];

    // Run the command to get the process list
    fp = _popen("tasklist", "r");
    if (fp == NULL) {
        perror("Error opening process list");
        exit(EXIT_FAILURE);
    }

    // Check if VMware Tools processes are present
    while (fgets(buffer, sizeof(buffer) - 1, fp) != NULL) {
        if (strstr(buffer, "vmtoolsd.exe") != NULL) {
            _pclose(fp);
            return 1; // VMware Tools process found
        }
    }

    _pclose(fp);
    return 0; // No VMware Tools process found
}

int checkVMwareRegistry() {
    HKEY hKey;
    const char* vmwareKey = "SOFTWARE\\VMware, Inc.\\VMware Tools";
    LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, vmwareKey, 0, KEY_READ, &hKey);

    if (result == ERROR_SUCCESS) {
        RegCloseKey(hKey);
        return 1; // VMware registry key found
    }

    return 0; // VMware registry key not found
}

int checkVMware() {
    if (checkVMwareProcesses() == 1 || checkVMwareRegistry() == 1) {
        return 1;
    }
    return 0;
}

#endif //VMDETECT_VMWARE_H
