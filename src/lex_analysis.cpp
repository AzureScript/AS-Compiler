//
// Created by Azure on 10/18/2018.
//

#include "lex_public.h"
#include "lex_private.h"

using namespace std;

/*
 * Constants
 */

char curChar;
int lineNum; int charNum;
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
        charNum++;

        // ===== { PRELIMINARY ERROR HANDLING } =====

        //handle empty
        if ( curChar == '\000' && lineNum == 0) {
            sprintf(printData, "File %s is empty! Exiting...", name);
            print();
            return -1;
        } else if ( curChar == '\000' ) {
            sprintf(printData, "Done parsing %s!", name);
            print();
            return 0;
        }else {
            lineNum = 1;
        }

        // newlines
        if (curChar == '\n') {
            lineNum++;
            charNum == 0;
        }

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
            if (wordlen > 100) {
                sprintf(printData, "ERROR! Word %s on line %d is too long! Rename and try again!", tempstr, lineNum);
                print();
            }
        } else if (!isalnum(curChar)){
            wordlen = 0;
        } else {
            sprintf(printData, "Invalid character '%c' at line %d.", curChar, lineNum);
            print();
        }


        // ===== { LEXER BEGIN } =====

        // Letter
        if (isalpha(curChar)) {
            tempWord[wordI] = curChar;
            wordI++;
            while (isalpha(file.peek())) {
                file.get(curChar);
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
        } else if (isdigit(curChar)) {
            tempWord[wordI] = curChar;
            wordI++;
            while (isdigit(file.peek())) {
                file.get(curChar);
                tempWord[wordI] = curChar;
                wordI++;
            }

            string tempFull(tempWord);
            Token num{
                    NUMBER, tempFull
            };
            lexed_file.push_back(num);

            memset(tempWord, 0, sizeof tempWord);
            tempFull.clear(); wordI = 0;


        // String
        } else if (curChar == '"') {
            while (file.peek() != '"') {
                file.get(curChar);
                tempWord[wordI] = curChar;
                wordI++;
            }

            //skip last "
            file.get(curChar);

            string tempFull(tempWord);
            Token str {
                    STRING, tempFull
            };
            lexed_file.push_back(str);

            memset(tempWord, 0, sizeof tempWord);
            tempFull.clear(); wordI = 0;


        // Punctuation
        } else if (ispunct(curChar)) {
            // Delimiter
            if (isDelim(curChar)){
                Token delim {
                    DELIM, string(1, curChar)
                };
                lexed_file.push_back(delim);

            // Other Operator
            } else if (isOtherOp(curChar)) {
                Token other{
                        OP, string(1, curChar)
                };
                lexed_file.push_back(other);

            // Logic Operator
            } else if (isLogic(curChar)) {
                tempWord[wordI] = curChar;
                if (file.peek() == '&' || file.peek() == '|' ) {
                    wordI++; file.get(curChar);
                    tempWord[wordI] = curChar;
                }

                string tempFull(tempWord);
                Token logic {
                        LOGIC, tempFull
                };
                lexed_file.push_back(logic);

                memset(tempWord, 0, sizeof tempWord);
                tempFull.clear(); wordI = 0;

            // Relational Operator
            } else if (startsRelOp(curChar)) {
                tempWord[wordI] = curChar;
                wordI++;
                if (file.peek() == '=') {
                    file.get(curChar);
                    tempWord[wordI] = curChar;
                }

                string tempFull(tempWord);
                if (strcmp(tempWord, "=") == 0) {
                    Token num{
                        ASSIGN, tempFull
                    };
                    lexed_file.push_back(num);
                } else {
                    Token num{
                        REL_OP, tempFull
                    };
                    lexed_file.push_back(num);
                }

                memset(tempWord, 0, sizeof tempWord);
                tempFull.clear(); wordI = 0;
            } else {
                sprintf(printData,"Unexpected Character in %s at %d:%d", name, lineNum, charNum);
                print();
                return -1;
            }
        }
    }

    return 0;
}
