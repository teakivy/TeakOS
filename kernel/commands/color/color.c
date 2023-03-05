#include "color.h"
#include "../../cmdhandler.h"
#include "../../../drivers/screen.h"
#include "../../../libc/string.h"

char* cmd_name;
char* cmd_desc;
char* cmd_usage;
char* alias[16];



int execute_color(int argc, char** argv) {
    if (argc != 2) {
        kprint_c("Usage: ", 0x04);
        kprint_c(cmd_usage, 0x0c);
        kprintln();
        return 1;
    }

    char color = 0x0f;

    to_upper(argv[1]);
    
    switch (argv[1][0]) {
        case '0':
            color = 0xf0;
            break;
        case '1':
            color = 0x01;
            break;
        case '2':
            color = 0x02;
            break;
        case '3':
            color = 0x03;
            break;
        case '4':
            color = 0x04;
            break;
        case '5':
            color = 0x05;
            break;
        case '6':
            color = 0x06;
            break;
        case '7':
            color = 0x07;
            break;
        case '8':
            color = 0x08;
            break;
        case '9':
            color = 0x09;
            break;
        case 'A':
            color = 0x0A;
            break;
        case 'B':
            color = 0x0B;
            break;
        case 'C':
            color = 0x0C;
            break;
        case 'D':
            color = 0x0D;
            break;
        case 'E':
            color = 0x0E;
            break;
        case 'F':
            color = 0x0F;
            break;
        default:
            kprint_c("Invalid color: ", 0x04);
            kprint_c(argv[1], 0x0c);
            kprintln();
            return 1;
    }



    set_terminal_color(color);
    kprint("Terminal color changed to 0x");
    if (strcmp(argv[1], "0") == 0) {
        kprint("1");
    } else {
        kprint("0");
    }
    kprint(argv[1]);
    kprint(" successfully!");
    kprintln();

    return 0;
}

void init_color() {
    cmd_name = "color";
    cmd_desc = "Changes the color of the terminal";
    cmd_usage = "color <0|1|2|3|4|5|6|7|8|9|A|B|C|D|E|F>";
    alias[0] = '\0';
    add_command(cmd_name, cmd_desc, cmd_usage, alias, execute_color);
}