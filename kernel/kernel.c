#include "../drivers/screen.h"

void main() {
    clear_screen();
    kprint_at("Welcome to TeakOS!", (MAX_COLS - 18) / 2, 8);
    kprint_at("Press any key to continue...", (MAX_COLS - 28) / 2, 12);
}