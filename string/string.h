#pragma once

typedef struct {
    unsigned int length;
    char *str;
} String;

/**
 * @brief Creates, initializes a String and returns a pointer to it
 * @param initialString The initial string as a char*
 * @return String* 
 */
String *stringCreate(char *initialString);

/**
 * @brief Appends the specified string to the string stored by the String struct
 * @param string Pointer to the String variable to be appended to
 * @param str The string to be appended to the String struct
 */
String *stringAppend(String *string, char *str);

/**
 * @brief Frees the heap allocated space for the String pointer and it's fields'
 * @param string Pointer to the String variable to be deallocated
 */
void stringFree(String *string);