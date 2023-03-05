#include "../cpu/isr.h"
#include "../libc/string.c"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "cmdhandler.h"

char *terminal_line;

void main() {
    terminal_line = "> ";
    clear_screen();
    kprint("Welcome to TeakOS!\n");
    isr_install();
    irq_install();
    initialize_commands();

    kprint(terminal_line);

}

void user_input(char *input) {
    if (strcmp(input, "overclock to 10ghz and make a fire") == 0) {
        set_terminal_color(0x04);
        kprint("Ok, done!\n");
        kprint(terminal_line);
        return;
    }

    int executed = execute_command(input);
    kprint(terminal_line);
}

char* get_terminal_line() {
    return terminal_line;
}