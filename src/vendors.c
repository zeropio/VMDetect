//
// Created by Zeropio on 17/12/2023.
//

#include "common.h"

enum VirtualizationVendor get_vm_vendor() {
    unsigned int eax, ebx, ecx, edx;

    // Check for VMWare
    eax = 0x40000000;
    __asm__ volatile(
            "cpuid"
            : "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx)
            : "a" (eax)
            );

    if (ebx == 'VMXh') {
        return VENDOR_VMWARE;
    }

    // Check for KVM
    eax = 0x40000000;
    __asm__ volatile(
            "cpuid"
            : "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx)
            : "a" (eax)
            );

    if (ebx == 'KVMK') {
        return VENDOR_KVM;
    }

    // Check for Hyper-V
    eax = 0x40000000;
    __asm__ volatile(
            "cpuid"
            : "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx)
            : "a" (eax)
            );

    if (ebx == 'hypv') {
        return VENDOR_HYPERV;
    }

    return VENDOR_UNKNOWN;
}
