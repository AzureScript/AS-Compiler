//
// Created by Azure on 10/18/2018.
//

#ifndef AZURESCRIPT_LEX_PRIVATE_H
#define AZURESCRIPT_LEX_PRIVATE_H

#ifndef AZURESCRIPT_COMMON_H
#include "common.h"
#endif

    /*
     * Constants
     */

// Keyword list
char const *keywords[] = {
        "function", "var", "if", "then", "else"
};

// RelOps
char const *relOps[] = {
        "==", "<", ">", "!=", "<=", ">="
};

// Other Ops
char const otherOps[] = {':', '+', '-', '*', '/', '%'};

// Delims
char const delims[] = {'.', '(', ')', ',', '{', '}', ';', '[', ']'};

// Temporary vars
char tempWord[100];
int wordI = 0;




    /*
     * Functions
     */

int isExAcceptableChar(char c) {
    if (c == '.' || c == '(' || c == ')' || c == ',' || c =='{' || c == '}' ||
        c == ';' || c == '[' || c == ']' ||
        c == ':' || c == '+' || c == '-' || c == '*' || c == '/' || c == '%' ||
        c == '=' || c == '<' || c == '>' || c == '!') {

        return 1;
    } else {
        return 0;
    }
}

int startsRelOp(char c) {
    int i;
    int result = 0; // false
    if (c == '=' || c == '<' || c == '>') {
        result = 1;
    }
    return result;
}

int isLogic(char c) {
    int i;
    int result = 0; // false
    if (c == '&' || c == '|' || c == '!') {
        result = 1;
    }
    return result;
}

int isOtherOp(char c) {
    int i;
    int result = 0; // false
    for (i = 0; i < 6; i++) {
        if (otherOps[i] == c)
            result = 1;
    }
    return result;
}

int isDelim(char c) {
    int i;
    int result = 0; // false
    for (i = 0; i < 9; i++) {
        if (delims[i] == c)
            result = 1;
    }
    return result;
}

int isKeyword(char *str) {
    int i;
    int result = 0; // false
    for (i = 0; i < 5; i++) {
        if (!strcmp(keywords[i], str))
            result = 1;
    }
    return result;
}

#endif //AZURESCRIPT_LEX_PRIVATE_H
