#include "../cpu/isr.h"
#include "../libc/string.c"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"

void main() {
    clear_screen();
    isr_install();
    irq_install();

    kprint("Welcome to TeakOS!\n> ");

    strcmp("12", "12");
}

void user_input(char *input) {
    if (strcmp(input, "END") == 0) {
        kprint("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    }

    if (strcmp(input, "CLEAR") == 0) {
        clear_screen();
    }
    kprint("You said: ");
    kprint(input);
    kprint("\n> ");
}