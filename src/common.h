//
// Useful
//

#ifndef VMDETECT_COMMON_H
#define VMDETECT_COMMON_H

enum VirtualizationVendor {
    VENDOR_UNKNOWN,
    VENDOR_VMWARE,
    VENDOR_VBOX,
    VENDOR_QEMU,
    VENDOR_WSL
};

extern char is_cpuid_supported();
extern char is_vm_running();
enum VirtualizationVendor get_vm_vendor();


#endif //VMDETECT_COMMON_H
