#include <stdio.h>
#include "common.h"

int main() {
    enum VirtualizationVendor vendor = get_vm_vendor();

    // Check CPUID available
    printf("Checking CPUID availabily... ");
    if (!is_cpuid_supported()) {
        printf("CPUID not supported.");
        return -1;
    }
    printf("Check!\n");

    // Check VM available
    printf("Checking VM... ");
    if (is_vm_running() == 0) {
        printf("VM not detected.\n");
        return -1;
    }
    printf("Check!\n");

    // Check vendors
    switch (vendor) {
        case VENDOR_VMWARE:
            printf("VMWare detected\n");
            break;
        case VENDOR_KVM:
            printf("KVM detected\n");
            break;
        case VENDOR_HYPERV:
            printf("Hyper-V detected\n");
            break;
        case VENDOR_UNKNOWN:
            printf("No known virtualization vendor detected\n");
            break;
    }



    return 0;
}