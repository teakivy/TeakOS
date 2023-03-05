#include "clear.h"
#include "../../cmdhandler.h"
#include "../../../drivers/screen.h"

char* cmd_name;
char* cmd_desc;
char* cmd_usage;
char* alias[16];

int execute_clear(int argc, char** argv) {
    clear_screen();
    return 0;
}

void init_clear() {
    cmd_name = "clear";
    cmd_desc = "Clears the screen";
    cmd_usage = "clear";
    alias[0] = '\0';
    add_command(cmd_name, cmd_desc, cmd_usage, alias, execute_clear);
}