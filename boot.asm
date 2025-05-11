usection .text
global _start

_start:
    cli                    ; Desactivar interrupciones
    lgdt [gdt_descriptor]   ; Cargar GDT (Tabla de Descriptores Global)
    
    mov eax, cr0
    or eax, 0x1            ; Activar modo protegido
    mov cr0, eax

    jmp 0x08:protected_mode_start ; Saltar a modo protegido

gdt_start:
    dq 0                   ; Descriptor nulo
    dq 0x00CF9A000000FFFF  ; Código
    dq 0x00CF92000000FFFF  ; Datos

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

protected_mode_start:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    call kernel_main
    hlt                    ; Detener CPU