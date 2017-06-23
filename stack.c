#include "stack.h"

void push(stack* st, int thing){
  st->contents[st->counter] = thing;
  st->counter++;
}
int peek(stack* st) {
  if (st->counter == 0) {
    return '!';
  }
  int conts = st->contents[st->counter-1];
  return conts;
}
  


int pop(stack* st){
  if (st->counter == 0) {
    return '!';
  }
  int conts = st->contents[st->counter-1];
  st->counter--;
  return conts;
}


  
  
