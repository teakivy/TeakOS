#include "../cpu/isr.h"
#include "../libc/string.c"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"

char *terminal_line;

void main() {
    terminal_line = "> ";
    clear_screen();
    isr_install();
    irq_install();

    kprint("Welcome to TeakOS!\n");
    kprint(terminal_line);
}

void user_input(char *input) {
    char* cmd = strcopy(input);
    to_lower(cmd);
    if (strcmp(input, "end") == 0) {
        kprint("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    }

    if (strcmp(input, "clear") == 0) {
        clear_screen();
        kprint(terminal_line);
        return;
    }
    kprint_c(input, 0x03);
    kprint("\n");
    kprint(terminal_line);
}

char* get_terminal_line() {
    return terminal_line;
}