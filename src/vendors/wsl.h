//
// Created by Zeropio on 19/12/2023.
//

#ifndef VMDETECT_WSL_H
#define VMDETECT_WSL_H

#include <stdio.h>
#include <windows.h>

int checkWSL() {
    SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
    if (hSCManager == NULL) {
        return 0; // Unable to open the service control manager
    }

    SC_HANDLE hService = OpenService(hSCManager, "LxssManager", SERVICE_QUERY_STATUS);
    if (hService != NULL) {
        // The service exists, indicating WSL
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        return 1;
    }

    CloseServiceHandle(hSCManager);
    return 0; // Service not found, likely not running in WSL
}

#endif //VMDETECT_WSL_H
