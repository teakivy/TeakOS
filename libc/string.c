#include "string.h"

/**
 * Converts an int to a string
 */
void int_to_ascii(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}

/**
 * Reverses a string
 */
void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/**
 * Returns string length
 */
int strlen(char s[]) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

/**
 * Appends a char to the end of a string
 */
void append(char s[], char n) {
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

/**
 * Removes a char from a string
 */
void backspace(char s[]) {
    int len = strlen(s);
    s[len-1] = '\0';
}

/**
 * Returns <0 if s1<s2, 0 if s1==s2, >0 if s1>s2
 */
int strcmp(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

void to_lower(char* str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] |= 0x20;
        }
    }
}

void to_upper(char* str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] &= ~0x20;
        }
    }
}

char* strcopy(char* str) {
    char res[strlen(str)];
    for (int i = 0; i < strlen(str); i++) {
        res[i] = str[i];
    }

    return res;
}