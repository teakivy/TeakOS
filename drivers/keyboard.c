#include "keyboard.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/string.h"
#include "../libc/function.h"
#include "../kernel/kernel.h"
#include "../kernel/cmdhandler.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define LEFT_SHIFT_DOWN 0x2A
#define RIGHT_SHIFT_DOWN 0x36
#define CTRL_DOWN 0x1D
#define LEFT_SHIFT_UP 170
#define RIGHT_SHIFT_UP 182
#define CTRL_UP 157

#define UP_ARROW 0x48
#define DOWN_ARROW 0x50

static char key_buffer[256];

#define SC_MAX 57
const char *sc_name[] = { "error", "esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "backspace", "tab", "q", "w", "e", 
        "r", "t", "y", "u", "i", "o", "p", "[", "]", "enter", "lctrl", 
        "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "`", 
        "lshift", "\\", "z", "x", "c", "v", "b", "n", "m", ",", ".", 
        "/", "rshift", "keypad *", "lalt", "spacebar"};
const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', ' ', 'q', 'w', 'e', 'r', 't', 'y', 
        'u', 'i', 'o', 'p', '[', ']', '?', '?', 'a', 's', 'd', 'f', 'g', 
        'h', 'j', 'k', 'l', ';', '\'', '`', '?', '\\', 'z', 'x', 'c', 'v', 
        'b', 'n', 'm', ',', '.', '/', '?', '?', '?', ' '};
const char shift_sc_ascii[] = { '?', '?', '!', '@', '#', '$', '%', '^',     
    '&', '*', '(', ')', '_', '+', '?', ' ', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '{', '}', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ':', '"', '~', '?', '|', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', '<', '>', '?', '?', '?', ' '};

int shift_held = 0;
int ctrl_held = 0;

int command_to = 0;
char zbuffer[256];

static void keyboard_callback(registers_t regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    u8 scancode = port_byte_in(0x60);

    // char str[256];
    // int_to_ascii(scancode, str);
    // kprint("Key: ");
    // kprint(str);
    // kprint("\n");

    if (scancode == LEFT_SHIFT_DOWN || scancode == RIGHT_SHIFT_DOWN) {
        shift_held = 1;
        return;
    }
    if (scancode == LEFT_SHIFT_UP || scancode == RIGHT_SHIFT_UP) {
        shift_held = 0;
        return;
    }
    if (scancode == CTRL_DOWN) {
        ctrl_held = 1;
        return;
    }
    if (scancode == CTRL_UP) {
        ctrl_held = 0;
        return;
    }

    if (scancode == UP_ARROW) {
        if (command_to == 0) {
            strcpy(zbuffer, key_buffer);
        }
        if (command_to < get_command_history_length()) command_to++;
        set_currently_typing(get_command_back(command_to));
        
        strcpy(key_buffer, get_command_back(command_to));
        return;
    }

    if (scancode == DOWN_ARROW) {
        if (command_to > 0) command_to--;
        char *cmd = get_command_back(command_to);
        if (command_to == 0 && zbuffer[0] != '\0') {
            strcpy(key_buffer, zbuffer);
            strcpy(cmd, zbuffer);
        }
        set_currently_typing(cmd);

        strcpy(key_buffer, cmd);
        return;
    }
    
    if (scancode > SC_MAX) return;
    if (scancode == BACKSPACE) {
        backspace(key_buffer);
        kprint_backspace();
    } else if (scancode == ENTER) {
        kprint("\n");
        user_input(key_buffer); /* kernel-controlled function */
        key_buffer[0] = '\0';
        command_to = 0;
    } else {
        char letter = sc_ascii[(int)scancode];
        if (shift_held && letter != ' ') letter = shift_sc_ascii[(int)scancode];
        /* Remember that kprint only accepts char[] */
        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        kprint(str);
    }
    UNUSED(regs);
}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback); 
}