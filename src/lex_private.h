//
// Created by Azure on 10/18/2018.
//

#ifndef AZURESCRIPT_LEX_PRIVATE_H
#define AZURESCRIPT_LEX_PRIVATE_H

#include <string>
#include <vector>
#include <string.h>

using std::string;
using std::vector;

    /*
     * Typedefs
     */

typedef enum {
    IDENTIFIER,
    KEYWORD,
    NUMBER,
    REL_OP, 	// such as ==  <  >  =!=    =>  =<
    OP,			// such as = :  +  -  *  / %
    DELIM,		// such as . (  ) , { } ; [ ]
    UNDEF,		// undefined
    EOT 		// end of token
} TokenType;

typedef struct {
    TokenType tokenType;
    char* value;
} Token;

    /*
     * Constants
     */

vector<Token> lexed_file;

// Keyword list
char const *keywords[] = {
        "function", "var", "if", "then", "else"
};

// RelOps
char const *relOps[] = {
        "==", "<", ">", "!=", "=>", "=<"
};

// Other Ops
char const otherOps[] = {':', '+', '-', '*', '/', '%'};

// Delims
char const delims[] = {'.', '(', ')', ',', '{', '}', ';', '[', ']'};


// Temporary vars

vector<char> tempWord;
vector<char> tempNum;
vector<char> tempKey;




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

int isRelOp(char c) {
    int i;
    int result = 0; // false
    if (c == '=' || c == '<' || c == '>') {
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
