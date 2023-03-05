#include "cmdhandler.h"
#include "../drivers/screen.h"
#include "../libc/string.h"

#include "commands/clear/clear.c"
#include "commands/echo/echo.c"
#include "commands/color/color.c"
#include "commands/exit/exit.c"


char cmd_history[128][256] = {0};
int cmd_n = 0;


command commands[128] = {0};
int command_count = 0;

#define NULL 0

void add_command(char* name, char* desc, char* usage, char** alias, int (*execute_func)(int, char**)) {
    commands[command_count].name = name;
    commands[command_count].desc = desc;
    commands[command_count].usage = usage;
    commands[command_count].alias = alias;
    commands[command_count].execute = execute_func;
    command_count++;
}

void initialize_commands() {
    init_clear();
    init_echo();
    init_color();
    init_exit();
}

int execute_command(char* cmd) {
    char* argv[128] = {0};
    int argc = 0;
    char* token = strtok(cmd, " ");
    while (token != NULL) {
        argv[argc] = token;
        argc++;
        token = strtok(NULL, " ");
    }

    for (int i = 0; i < command_count; i++) {
        if (strcmp(commands[i].name, cmd) == 0) {
            add_command_to_history(cmd);
            return commands[i].execute(argc, argv);
        }
    }

    kprint_c("Command not found: ", 0x04);
    kprint_c(cmd, 0x0c);
    kprint_c("\n", 0x04);
    return 1;
}

char* get_command_from_history(int num) {
    return cmd_history[num];
}

char* get_last_command() {
    if (cmd_n == 0) return "np";
    return cmd_history[cmd_n - 1];
}

void add_command_to_history(char* cmd) {
    int i;
    for (i = 0; cmd[i] != '\0'; i++) {
        cmd_history[cmd_n][i] = cmd[i];
    }
    cmd_history[0][i] = '\0';
    cmd_n++;
}

char* get_command_back(int n) {
    if (n > cmd_n) return "";
    return cmd_history[cmd_n - n];
}

void set_currently_typing(char* str) {
    for (int i = 0; i < 100; i++) {
        kprint_backspace();
    }

    kprint(str);
}

int get_command_history_length() {
    return cmd_n;
}