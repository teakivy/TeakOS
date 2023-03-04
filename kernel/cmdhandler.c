char cmd_history[128][256] = {0};
int cmd_n = 0;
char* test = "Hello!";

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