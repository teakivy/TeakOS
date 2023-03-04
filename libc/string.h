#ifndef STRING_H
#define STRING_H

void int_to_ascii(int n, char str[]);
void reverse(char s[]);
int strlen(char s[]);
void backspace(char s[]);
void append(char s[], char n);
int strcmp(char s1[], char s2[]);
void to_lower(char* str);
void to_upper(char* str);
void strcpy(char* dest, char* src);
void strcat(char* dest, char* src);

#endif