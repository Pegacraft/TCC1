//
// Created by jkorw on 18.02.2022.
//

#include "parse.h"

token *create_token(token_type type, char value) {
    token *token1 = malloc(sizeof(token));
    token1->type = type;
    token1->value = value;
    return token1;
}

token *tokenize(const char *data) {
    token *head = NULL;
    token *tail = NULL;
    char curr;
    int pos = 0;
    token_type type;
    while ((curr = data[pos]) != '\0') {
        if (curr >= 'a' && curr <= 'z') {
            type = IDENTIFIER;
        } else if (curr >= '0' && curr <= '9') {
            type = VALUE;
        } else {
            switch (curr) {
                case '(':
                    type = OPENING_ROUND_BRACKET;
                    break;
                case ')':
                    type = CLOSING_ROUND_BRACKET;
                    break;
                case '{':
                    type = OPENING_BLOCK;
                    break;
                case '}':
                    type = CLOSING_BLOCK;
                    break;
                case '[':
                    type = OPENING_ARRAY_BRACKET;
                    break;
                case ']':
                    type = CLOSING_ARRAY_BRACKET;
                    break;
                default:
                    type = SYMBOL;
                    break;
            }
        }
        token *pToken = create_token(type, curr);
        if (head == NULL) {
            head = pToken;
            tail = pToken;
        } else {
            tail->next = pToken;
            tail = pToken;
        }
        pos++;
    }
    return head;
}
