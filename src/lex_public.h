//
// Created by Azure on 10/18/2018.
//

#ifndef AZURESCRIPT_LEX_PUBLIC_H
#define AZURESCRIPT_LEX_PUBLIC_H

#ifndef AZURESCRIPT_COMMON_H
#include "common.h"
#endif

    /*
     * Typedefs
     */

typedef enum {
    IDENTIFIER,
    KEYWORD,
    NUMBER,
    STRING,
    ASSIGN,     // such as =
    OP,			// such as :  +  -  *  / %
    REL_OP, 	// such as ==  <  >  !=  <=  >=
    DELIM,		// such as . (  ) , { } ; [ ]
    LOGIC,		// such as && || !
    UNDEF,		// undefined
    EOT 		// end of token
} TokenType;

typedef struct {
    TokenType tokenType;
    std::string value;
} Token;

/*
 * Public Vars
 */

extern std::vector<Token> lexed_file;

/*
 * Functions
 */

int lex_main(char* mainName);
int lex_process_file(char* file);

#endif //AZURESCRIPT_LEX_PUBLIC_H
