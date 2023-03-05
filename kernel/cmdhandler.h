#ifndef CMDHANDLER_H
#define CMDHANDLER_H

typedef struct command {
    char* name;
    char* desc;
    char* usage;
    char** alias;
    int (*execute)(int, char**);
} command;

char* get_command_from_history(int num);
char* get_last_command();
void add_command_to_history(char* cmd);
char* get_command_back(int n);
void set_currently_typing(char* str);
int get_command_history_length();
void initialize_commands();
int execute_command(char* cmd);
void add_command(char* name, char* desc, char* usage, char** alias, int (*execute)(int, char**));


#endif