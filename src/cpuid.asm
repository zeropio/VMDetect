;; Based on the code from Xeno Kovah in 2021 for OpenSecurityTraining2
;; Architecture 2001 class (https://ost2.fyi/Arch2001)

section .text
global is_cpuid_supported
global is_vm_running

is_cpuid_supported:
   ; The manual says:
   ; "The ID flag (bit 21) in the EFLAGS register indicates support for the CPUID instruction.
   ; If a software procedure can set and clear this flag, the processor executing the procedure
   ; supports the CPUID instruction.""
   ; So let's see if we can set or clear the ID flag
   pushfq                   ; Save RFLAGS to stack
   mov r15, [rsp]           ; Store a copy of the original flags in r15 to restore later
   bts qword [rsp], 21      ; Copy original bit 21 into carry flag, and set bit 21
   jnc try_write_rflags     ; If original bit 21 was zero, we've modified bit 21 and are ready to try
                            ; writing to RFLAGS
   btr qword [rsp], 21      ; Else, if original bit 21 was 1, our bts instruction didn't change it,
                            ; so reset bit 21 to change it
try_write_rflags:
   popfq                    ; Try to write a change to RFLAGS
   mov rax, 1               ; Presume success, and change rax if necessary
   pushfq                   ; Save RFLAGS again
   cmp [rsp], r15           ; CMP (SUB) the current and original flags. If they are the same, ZF=1, otherwise ZF=0
   jnz cleanup              ; If what's was originally in the register != what's there now, ZF=0 and we changed
                            ; ID flag, so return 1
   mov rax, 0               ; Else they're the same, so no change, so we couldn't alter ID flag and CPUID isn't
                            ; supported, so return 0

cleanup:
   mov [rsp], r15           ; Restore the original RFLAGS from r15
   popfq                    ; Write original RFLAGS back, and balance the stack
   ret

is_vm_running:
   ; Check if the hypervisor present bit (bit 31) is set after executing CPUID
   mov eax, 1
   cpuid
   test edx, 1 << 31  ; Test the 31st bit in the EDX register (hypervisor present bit)
   jnz vm_detected    ; If the bit is set, jump to vm_detected
   mov eax, 0          ; If the bit is not set, return 0
   ret

vm_detected:
   mov eax, 1          ; Set EAX to 1 to indicate VM detection
   ret