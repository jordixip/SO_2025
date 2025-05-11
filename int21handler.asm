section .text
    global setup_interrupts

setup_interrupts:
    ; Guardar el manejador antiguo de INT 21h
    mov ax, 0x3521   ; Obtener el manejador de INT 21h
    int 0x21
    mov [old_int21], bx
    mov [old_int21+2], es

    ; Establecer nuestro manejador
    cli
    mov dx, new_int21_handler
    mov ax, 0x2521   ; Establecer el nuevo manejador de INT 21h
    int 0x21
    sti
    ret

new_int21_handler:
    cmp ah, 0x09     ; Comprobar si es la función de imprimir cadena
    je print_string
    cmp ah, 0x02     ; Comprobar si es imprimir carácter
    je print_char
    cmp ah, 0x4C     ; Comprobar si es terminar programa
    je exit_program

    ; Restaurar la interrupción original si no reconocemos el comando
    jmp far [old_int21]

print_string:
    push si
    mov si, dx

    cmp si, 0x0000   ; Verificar si el puntero es NULL
    je .error_null

.loop:
    lodsb
    cmp al, '$'
    je .done
    cmp al, 0x00
    je .error_no_dollar

    mov ah, 0x0E
    mov bh, 0x00
    int 0x10
    jmp .loop

.error_null:
    mov dx, error_msg_null
    call print_error
    jmp .done

.error_no_dollar:
    mov dx, error_msg_no_dollar
    call print_error
    jmp .done

.done:
    pop si
    ret

print_char:
    mov ah, 0x0E
    mov bh, 0x00
    int 0x10
    ret

exit_program:
    mov ax, 0x4C00
    int 0x21
    ret

print_error:
    ; Aquí podrías definir una rutina para mostrar mensajes de error
    ret

section .data
    error_msg_null db "Error: Puntero nulo", 0x0D, 0x0A, '$'
    error_msg_no_dollar db "Error: Falta '$' en la cadena", 0x0D, 0x0A, '$'

section .bss
    old_int21 resd 1  ; Variable para almacenar la interrupción original