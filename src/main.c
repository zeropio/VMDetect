#include <stdio.h>
#include "common.h"

void printHeader(const char *title) {
    printf("\n=================================\n");
    printf("     %s\n", title);
    printf("=================================\n");
}

int main() {

    // Check CPUID availability
    printHeader("Checking CPUID Availability");
    printf("Status: ");
    if (!is_cpuid_supported()) {
        printf("\033[1;31mNot supported\033[0m\n");
        return -1;
    }
    printf("\033[1;32mSupported\033[0m\n");

    // Check if it's a VM via CPUID
    printHeader("Checking Virtual Machine");
    printf("Status: ");
    if (is_vm_running() == 1) {
        printf("\033[1;31mVirtual Machine detected\033[0m\n");
        return -1;
    }
    printf("\033[1;32mNo Virtual Machine detected\033[0m\n");

    // Check vendors
    printHeader("Checking Virtualization Vendor");
    switch (get_vm_vendor()) {
        case VENDOR_VMWARE:
            printf("\033[1;34mVMWare detected\033[0m\n");
            break;
        case VENDOR_VBOX:
            printf("\033[1;34mVirtualBox detected\033[0m\n");
            break;
        case VENDOR_QEMU:
            printf("\033[1;34mQEMU detected\033[0m\n");
            break;
        case VENDOR_WSL:
            printf("\033[1;34mWSL detected\033[0m\n");
            break;
        case VENDOR_UNKNOWN:
            printf("\033[1;33mNo known virtualization vendor detected\033[0m\n");
            break;
    }

    return 0;
}
