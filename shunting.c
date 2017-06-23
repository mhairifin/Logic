#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

int precedence(char c);

char* shunt(char* og, int length) {
  char* shunted= malloc(length*sizeof(char));
  int shc = 0;
  
  stack ops;
  ops.counter = 0;

  for (int i = 0; i<length; i++) {
    char curr  = og[i];
    if (curr == '0' || curr == '1' || (curr >= 97 && curr <= 122)) {
      shunted[shc] = curr;
      shc++;
    }
    else {
      if (curr == '(') {
	push(&ops, curr);
      }
      else if (curr == ')') {
	while (peek(&ops) != '(') {
	  shunted[shc] = pop(&ops);
	  shc++;
	}
	pop(&ops);
      }
      else {
        while (peek(&ops)!= '(' && (precedence(curr) <= precedence((char)peek(&ops)))) {
	  char add = pop(&ops);
	  shunted[shc] = add;
	  shc++;
	}
	push(&ops, curr);
      }
    }
    
  }

  char addop = pop(&ops);
  while (addop != '!') {
    shunted[shc] = addop;
    shc++;
    addop = pop(&ops);
  }

  return shunted;
}

int precedence(char c) {
  switch (c){
  case '&':return 8;
  case '#': return 9;
  case '|': return 10;
  case '>': return 6;
  case '-': return 7;
  case '=': return 12;
  default: return 0;
  }
}
  
  
