#include "echo.h"
#include "../../cmdhandler.h"
#include "../../../drivers/screen.h"

char* cmd_name;
char* cmd_desc;
char* cmd_usage;
char* alias[16];



int execute_echo(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        kprint(argv[i]);
        kprint(" ");
    }

    kprint("\n");

    return 0;
}

void init_echo() {
    cmd_name = "echo";
    cmd_desc = "Echoes the input";
    cmd_usage = "echo <text>";
    alias[0] = '\0';
    add_command(cmd_name, cmd_desc, cmd_usage, alias, execute_echo);
}