//
// Useful
//

#ifndef VMDETECT_COMMON_H
#define VMDETECT_COMMON_H

enum VirtualizationVendor {
    VENDOR_UNKNOWN,
    VENDOR_VMWARE,
    VENDOR_KVM,
    VENDOR_HYPERV
};

extern char is_cpuid_supported();
extern char is_vm_running();
enum VirtualizationVendor get_vm_vendor();

#endif //VMDETECT_COMMON_H
