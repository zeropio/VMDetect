cmake_minimum_required(VERSION 3.15)
project(VMDetect)
enable_language(ASM_NASM)

set(CMAKE_C_STANDARD 99)

set(ASM_SOURCES
        src/cpuid.asm
)

set (SOURCES
        src/main.c
        ${ASM_SOURCES}
        src/common.h
        src/vendors/vbox.h
        src/vendors/vmware.h
        src/vendors.c
        src/vendors/qemu.h
        src/vendors/wsl.h
)

set_source_files_properties(${ASM_SOURCES} PROPERTIES LANGUAGE ASM_NASM)

add_executable(VMDetect ${SOURCES})