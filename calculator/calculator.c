#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "calculator.h"

int main() {
    //printf("%d",calculate("5*7"));
}

int calculate(char* expression) {

    // INFIX -> POSTFIX

   size_t i = 0;
   stack ops;
   queue output;
   qu_init(&output);
   st_init(&ops);
   stack paren;
   st_init(&paren);

   while(i < strlen(expression)) {
       char c = expression[i];
       token_t new_token = {0};

       switch (c) {
            case ' ':
                i++;
                break;

            case '+':
            case '-':
            case '/':
            case '*':
            case '%':
            case '^':
            {
                // operators cannot be next to each other
                if(i == 0 || i == strlen(expression)-1 || (!isdigit(expression[i+1]) && expression[i+1] != ')' && expression[i+1] != '(' && expression[i+1] != ' ') &&(!isdigit(expression[i-1]) && expression[i-1] != ')' && expression[i-1] != '(' && expression[i-1] != ' ')) { 
                    return -1;
                }
                while (!st_empty(&ops) && ((c != '^' && precedence(peek(&ops))>= precedence(c)))||(c == '^' && (precedence(peek(&ops))>precedence(c)))){
                    int stack_top = st_pop(&ops);
                    new_token.type = TOKEN_OPERATOR;
                    new_token.val = stack_top;
                    enq(new_token, &output);
                }

                st_push(c, &ops);
                i++;
                break;
             }

             case '(':
             {
                st_push(c, &ops);
                st_push(c, &paren);
                i++;
                break;
             }
             case ')':
             {
                while (!st_empty(&ops) &&(char)peek(&ops)!='(') {
                    int stack_top = st_pop(&ops);
                    new_token.type = TOKEN_OPERATOR;
                    new_token.val = stack_top;
                    enq(new_token, &output);
                }
                if (st_empty(&paren)) {
                    return -1;
                }
                st_pop(&paren);
                i++;
                break;
             }
             default:
             {
                int number = 0;
                if(!isdigit(c)){
                    return -1;
                }
                while (isdigit(expression[i])){
                    number *= 10;
                    number += expression[i] - '0';
                    i++;
                }
                new_token.type = TOKEN_NUMBER;
                new_token.val = number;
                enq(new_token, &output);
                break;
             }
         }
     }

     if (!st_empty(&paren)) {
        return -1;
     }
     while (!st_empty(&ops)) {
        int stack_top = st_pop(&ops);
        token_t new_token = {TOKEN_OPERATOR, stack_top};
        enq(new_token, &output);
     }
     int out = 0;
     stack tmp;
     st_init(&tmp);
     while (!qu_empty(&output)) {
        token_t qu_front = deq(&output);
        if (qu_front.type == TOKEN_OPERATOR) {
            switch(qu_front.val) {
              case '+':
                   {
                   int first, second;
                   second = st_pop(&tmp);
                   first = st_pop(&tmp);
                   out = first + second;
                   st_push(out, &tmp);
                   break;
               }
               case '-':
               {
                  int first, second;
                  second = st_pop(&tmp);
                  first = st_pop(&tmp);
                  out = first - second;
                  st_push(out, &tmp);
                  break;
               }
               case '*':
               {
                  int first, second;
                  second = st_pop(&tmp);
                  first = st_pop(&tmp);
                  out = first * second;
                  st_push(out, &tmp);
                  break;
               }
               case '/':
               {
                  int first, second;
                  second = st_pop(&tmp);
                  first = st_pop(&tmp);
                  if (second == 0) {
                    return -1;
                  }
                  out = first / second;
                  st_push(out, &tmp);
                  break;
               }
               case '%':
               {
                  int first, second;
                  second = st_pop(&tmp);
                  first = st_pop(&tmp);
                  if (second == 0) {
                    return -1;
                  }
                  out = first % second;
                  st_push(out, &tmp);
                  break;
               }
               case '^':
               {
                  int first, second;
                  second = st_pop(&tmp);
                  first = st_pop(&tmp);
                  out = (int) pow(first, second);
                  st_push(out, &tmp);
                  break;
                }
             }
         }
         else {
            st_push(qu_front.val, &tmp);
        }
     }
     if (tmp.top != 0) {
            return -1;
     }
     return peek(&tmp);
}
