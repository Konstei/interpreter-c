#pragma once

#include "../vector/vector.h"

typedef struct {
    unsigned long long length;
    char *str;
} String;

DECLARE_VECTOR(String);

/**
 * @brief Creates, initializes a String and returns a pointer to it
 * @param str The initial string
 * @return String* 
 */

String *stringCreate(char *str);

/**
 * @brief Appends the specified string to the string stored by the String struct
 * @param string Pointer to the String variable to be appended to
 * @param str The string to be appended to the String struct
 * @return String*
 */
String *stringAppend(String *string, char *str);

/**
 * @brief Frees the heap allocated space for the String pointer and it's fields'
 * @param string Pointer to the String variable to be deallocated
 * @return void
 */
void stringFree(String *string);

/**
 * @brief Returns a new String with the specified slice of the original String
 * @param string Pointer to the String variable to be sliced from
 * @param start Starting index of the slice
 * @param end Ending index of the slice
 * @return String*
 */
String *stringSlice(String *string, unsigned int start, unsigned int end);

/**
 * @brief Splits the string into a Vector of Strings
 * @param string Pointer to the String variable to be split
 * @param separator The delimiter to split the string by as a string
 * @return Vector(String)*
 */
Vector(String) *stringSplit(String *string, char *separator);

/**
 * @brief Joins the strings in the Vector into a single String
 * @param separator The delimiter to join the strings by as a string
 * @return String* 
 */
String *stringJoin(Vector(String) *v, char *separator);

/**
 * @brief Returns the index of the first occurence of the specified substring in the string
 * @param string Pointer to the String variable to be searched in
 * @param str The substring to be searched for
 * @param start The starting index of the search
 * @return long long 
 */
long long stringFind(String *string, char *str, unsigned long long start);

/**
 * @brief Returns the number of occurences of the specified substring in the string
 * @param string Pointer to the String variable to be searched in
 * @param str The substring to be searched for
 * @param start The starting index of the search
 * @param end The ending index of the search
 * @return unsigned long long 
 */
unsigned long long stringCount(String *string, char *str, unsigned long long start, unsigned long long end);

/**
 * @brief Removes leading and trailing whitespaces
 * @param str Specifies the string from which the whitespaces to be removed
 * @param direction Specifies the direction from which whitespaces to be removed (-1 for leading, 1 for trailing, default for both)
 * @return String*
 */
String *stringTrim(String *str, int direction);