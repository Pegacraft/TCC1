//
// Created by jkorw on 18.02.2022.
//

#ifndef TURING_COMPLETE_PARSE_H
#define TURING_COMPLETE_PARSE_H

#include <stdlib.h>

typedef enum token_type {
    VALUE, //any number, string etc
    IDENTIFIER, //any identifier, like variable/function names or keywords
    SYMBOL, //any symbol, that is not a bracket
    OPENING_BLOCK, // {
    CLOSING_BLOCK, // }
    OPENING_ROUND_BRACKET, // (
    CLOSING_ROUND_BRACKET, // )
    OPENING_ARRAY_BRACKET, // [
    CLOSING_ARRAY_BRACKET // ]
} token_type;

typedef struct token {
    token_type type;
    char value;
    struct token *next;
} token;

token *create_token(token_type type, char value);

token *tokenize(const char *data);

#endif //TURING_COMPLETE_PARSE_H
