#include "exit.h"
#include "../../cmdhandler.h"
#include "../../../drivers/screen.h"

char* cmd_name;
char* cmd_desc;
char* cmd_usage;
char* alias[16];



int execute_exit(int argc, char** argv) {
    clear_screen();

    kprint_at("Exiting...", (MAX_COLS - 10) / 2, MAX_ROWS / 2);
    asm volatile("hlt");

    return 0;
}

void init_exit() {
    cmd_name = "exit";
    cmd_desc = "Exits the terminal";
    cmd_usage = "exit";
    alias[0] = '\0';
    add_command(cmd_name, cmd_desc, cmd_usage, alias, execute_exit);
}