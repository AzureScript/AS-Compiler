/*
 *  AzureScript Compiler
 *  Copyright (c) 2018 Andrew Augustine
 */

#include <fstream>

#include "lex_analysis.h"

using namespace std;

int main(int argc, char* argv[]) {
    printf("\n=====[ AzureScript Compiler v0.1.0 ]=====\n\n");

    // Initial Switch
    switch (argc){
        case 1:
            printf("No file Specified!");
            return -1;
        case 2:
            printf("Entrypoint: %s", argv[1]);
            break;
        default:
            printf("Syntax: \nCompiler [File]");
            break;
    }

    // Start Lexical Analysis
    lex_main(argv[1]);

    return 0;
}