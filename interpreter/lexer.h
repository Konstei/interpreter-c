#pragma once

#include "../string/string.h"


/**
 * @brief Counts the number of opening and closing multiline comments
 * @param line The line of code to be checked
 * @param opening The number of opening comments, transferred by reference to store the computed value
 * @param closing The number of closing comments, transferred by reference to store the computed value
 */
void commentsCount(String *line, int *opening, int *closing);

/**
 * @brief Deletes all comments from the passed string
 * @param code The code as a string from which the comments are deleted
 */
String *commentsDelete(String *code);