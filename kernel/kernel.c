#include "../cpu/isr.h"
#include "../libc/string.c"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "cmdhandler.h"

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
    add_command_to_history(input);
    if (strcmp(input, "end") == 0) {
        kprint("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    }

    if (strcmp(input, "clear") == 0) {
        clear_screen();
        kprint(terminal_line);
        return;
    }
    if (strcmp(input, "overclock to 10ghz and make a fire") == 0) {
        set_terminal_color(0x04);
        kprint_c("Ok, ");
        kprint_c("done!");
        kprint("\n");
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