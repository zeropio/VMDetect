#include <stdio.h>
#include "common.h"

int main() {

    // Check CPUID availability
    printf("Checking CPUID availability... ");
    if (!is_cpuid_supported()) {
        printf("CPUID not supported.");
        return -1;
    }
    printf("Check!\n");

    // Check if it's VM via CPUID
    printf("Checking VM... ");
    if (is_vm_running() == 1) {
        printf("VM not detected.\n");
        return -1;
    }
    printf("Check!\n");

    // Check vendors
    switch (get_vm_vendor()) {
        case VENDOR_VMWARE:
            printf("VMWare detected\n");
            break;
        case VENDOR_VBOX:
            printf("VirtualBox detected\n");
            break;
        case VENDOR_QEMU:
            printf("QEMU detected\n");
            break;
        case VENDOR_WSL:
            printf("WSL detected\n");
            break;
        case VENDOR_UNKNOWN:
            printf("No known virtualization vendor detected\n");
            break;
    }

    return 0;
}