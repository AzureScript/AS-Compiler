//
// Created by Azure on 10/18/2018.
//

#include "lex_public.h"
#include "lex_private.h"

/*
 * Constants
 */

char curChar;
int lineNum;
vector<Token> lexed_file;

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
        if (isalpha(curChar)) {
            tempWord[wordI] = curChar;
            wordI++;
            while (file.get(curChar) && isalpha(curChar)) {
                tempWord[wordI] = curChar;
                wordI++;
            }

            // Check if identifier or keyword
            string tempFull(tempWord);
            if (isKeyword(tempWord)) {
                Token word{
                        KEYWORD, tempFull
                };
                lexed_file.push_back(word);
            } else {
                Token word{
                        IDENTIFIER, tempFull
                };
                lexed_file.push_back(word);
            }

            memset(tempWord, 0, sizeof tempWord);
            tempFull.erase(); wordI = 0;


        // Number
        } else if (isdigit(curChar)){
            tempWord[wordI] = curChar;
            wordI++;
            while (file.get(curChar) && isalpha(curChar)) {
                tempWord[wordI] = curChar;
                wordI++;
            }

            string tempFull(tempWord);
            Token num {
                NUMBER, tempFull
            };
            lexed_file.push_back(num);

            memset(tempWord, 0, sizeof tempWord);
            tempFull.clear(); wordI = 0;


        // Punctuation
//        } else if (ispunct(curChar)) {
//            if (isDelim(curChar)){
//                Token delim {
//                    DELIM, &curChar
//                };
//                lexed_file.push_back(delim);
//            } else if (isOtherOp(curChar)) {
//                Token other {
//                    OP, &curChar
//                };
//                lexed_file.push_back(other);
//            }
        }
    }

    //handle empty
    if ( curChar == '\000' ) {
        printf("File %s is empty! Exiting...\n", name);
        return -1;
    }

    return 0;
}
