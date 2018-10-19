/*
 *  AzureScript Compiler
 *  Copyright (c) 2018 Andrew Augustine
 */

#include "common.h"
#include "lex_public.h"

using namespace std;

char printData[];

void print(){
    cout << printData << endl;
    memset(printData, 0, sizeof printData);
}

int main(int argc, char* argv[]) {
    sprintf(printData, "\n=====[ AzureScript Compiler v0.1.0 ]=====\n");
    print();

    // Initial Switch
    switch (argc){
        case 1:
            sprintf(printData, "No file Specified!");
            print();
            return -1;
        case 2:
            sprintf(printData, "Entrypoint: %s", argv[1]);
            print();
            break;
        default:
            sprintf(printData, "Syntax: \nCompiler [File]");
            print();
            break;
    }

    // Start Lexical Analysis
    if (lex_main(argv[1]) != 0){
        return -1;
    }

    return 0;
}