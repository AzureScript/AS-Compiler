//
// Created by Azure on 10/18/2018.
//

#include <iostream>
#include <fstream>
#include <exception>
#include <algorithm>

#include "lex_analysis.h"
#include "lex_private.h"

using namespace std;

/*
 * Constants
 */

char curChar;
int lineNum;

/*
 * Functions
 */

int lex_main(char* mainName){
    lex_process_file(mainName);
}

int lex_process_file(char* name){
    ifstream file (name);
    char tempstr[101];
    int wordlen = 0;

    while (file.get(curChar)) {

        // ===== { PRELIMINARY ERROR HANDLING } =====

        // newlines
        if (curChar == '\n')
            lineNum++;

        // comments
        if (curChar == '/') {
            file.get(curChar);
            if (curChar == '/'){
                while (curChar != '\n'){
                    file.get(curChar);
                }
                lineNum++;
            }
        }

        // word length checker
        if (isalnum(curChar)){
            tempstr[wordlen] = curChar;
            wordlen++;
            if (wordlen > 100)
                printf("ERROR! Word %s on line %d is too long! Rename and try again!\n", tempstr, lineNum);
        } else if (isspace(curChar) || isExAcceptableChar(curChar)){
            wordlen = 0;
        } else {
            printf("Invalid character '%c' at line %d.\n", curChar, lineNum);
        }


        // ===== { LEXER BEGIN } =====

        // Letter
        if (isalpha(curChar)){
            tempWord.push_back(curChar);
            while (file.get(curChar) && isalpha(curChar)) {
                tempWord.push_back(curChar);
            }

            // Check if identifier or keyword
            if (isKeyword(&tempWord[0])){
                Token word {
                    KEYWORD, &tempWord[0]
                };
                lexed_file.push_back(word);
            } else {
                Token word {
                    IDENTIFIER, &tempWord[0]
                };
                lexed_file.push_back(word);
            }
            tempWord.clear();


        // Number
        } else if (isdigit(curChar)){
            tempNum.push_back(curChar);
            while (file.get(curChar) && isdigit(curChar)) {
                tempWord.push_back(curChar);
            };
            Token num {
                NUMBER, &tempNum[0]
            };
            lexed_file.push_back(num);
            tempWord.clear();


        // Punctuation
        } else if (ispunct(curChar)) {
            if (isDelim(curChar)){
                Token delim {
                    DELIM, &curChar
                };
                lexed_file.push_back(delim);
            } else if (isOtherOp(curChar)) {
                Token other {
                    OP, &curChar
                };
                lexed_file.push_back(other);
            }
        }
    }

    //handle empty
    if ( curChar == NULL) {
        printf("File %s is empty! Exiting...", name);
        return -1;
    }

    return 0;
}
