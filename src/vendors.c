#include "common.h"
#include "vendors/vmware.h"
#include "vendors/vbox.h"
#include "vendors/qemu.h"
#include "vendors/wsl.h"

enum VirtualizationVendor get_vm_vendor() {
    if (checkVMware() == 1) {
        return VENDOR_VMWARE;
    }

    if (checkVBox() == 1) {
        return VENDOR_VBOX;
    }

    if (checkQEMU() == 1) {
        return VENDOR_QEMU;
    }

    if (checkWSL() == 1) {
        return VENDOR_WSL;
    }

    return VENDOR_UNKNOWN;
};