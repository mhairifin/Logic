typedef struct stack {
  int contents[1000];
  int counter;
}stack;

int pop(stack* st);
void push(stack* st, int thing);
int peek(stack* st);
