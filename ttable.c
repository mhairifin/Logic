#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include <string.h>
#include "shunting.h"

int and(int one, int two);
int or(int one, int two);
int xor(int one, int two);
int equal(int one, int two);
int imply(int one, int two);
int not(int one);

int convert(char bool);

int evaluate(char* rpn, int length);

void printTableHead(char* rpn, int length, int numVars);
void println(char* rpn, int length, int* varVals, int numVars);
int toThe(int num);
void truthTable(char*rpn, int numVars);
void laws();

int main(int argc, char* argv[]){
  int numVars = atoi(argv[1]); //turns character argument into number
  // truthTable(argv[2], numVars); //prints out a truth table for the formula
  //laws();

  char* shunted = shunt(argv[2], strlen(argv[2]));
  truthTable(shunted, numVars);
  free(shunted);
}

//computes and prints the truth table
void truthTable(char* rpn, int numVars) {
  int length = strlen(rpn);
  
  int varVals[26]; //stores the values of the variables, of whcih there could be 26
  int max = toThe(numVars); //gets the number of possible combinations of variables
  
  printTableHead(rpn, length, numVars);
  
  for (int number = 0; number<max; number++){ //loops over all possible combos of the variables
    int standIn = number;
    for (int i = 0; i<numVars; i++) {
      varVals[i] = (standIn>>(numVars-i-1)) & 1; //stores the possible values
    }
    println(rpn, length, varVals, numVars); //computes a line of the truth table based on these values
  }
}

//function that prints out the truth table for boolean algebra and demorgans law
/*void laws(){
  printf("\nDistributive Law A");
  truthTable("bc|a&ab&ac&|=", 3);

  printf("\nDistributive Law B");
  truthTable("bc&a|ab|ac|&=", 3);

  printf("\nDeMorgans Law A");
  truthTable("ab|-a-b-&=", 2);

  printf("DeMorgans Law B");
  truthTable("ab&-a-b-|=", 2);
  }*/



int toThe(int num) {
  int two = 2;
  for (int i = 0; i<num-1; i++){
    two=2*two;
  }
  return two;
}

//prints the truth table header
void printTableHead(char* rpn, int length, int numVars) {
  printf("\n");
  for (int i = 0; i<numVars; i++) {
    printf("%c ", i+97);
  }
  printf(": %s : Result\n", rpn);

  for (int i = 0; i< numVars*2 +11+length; i++) {
    printf("=");
  }
  printf("\n");
}

//computes and prints a line of the truth table
void println(char* rpn, int length, int* varVals, int numVars){
  char expression[1000];
  for (int i = 0; i< length; i++) {
    if (rpn[i] >=97 && rpn[i]<=122) {
      expression[i] = varVals[rpn[i]-97]; //replace variable with its value
    }
    else{
      expression[i] = rpn[i];
    }
  }
  for (int i = 0; i< numVars; i++) {
    printf("%d ", varVals[i]); //print the variable values
  }
  printf(": ");
  printf(" :   %d\n", evaluate(expression, length)); //print the result
}

int evaluate(char* rpn, int length) { //evaluates an rpn of just numbers and operators, and prints
  struct stack st;
  st.counter = 0;
  for (int i = 0; i< length; i++) {
    switch (rpn[i]){
    case '&': {
      int result = and(pop(&st), pop(&st));
	push(&st, result);
	printf("%d", result);
	break; }
    case '|': {
      int result = or(pop(&st), pop(&st));
	push(&st, result);
	printf("%d", result);
	break; }
    case '#': { int result = xor(pop(&st), pop(&st));
	push(&st, result);
	printf("%d", result);
	break;}
    case '=': { int result = equal(pop(&st), pop(&st));
	push(&st, result);
	printf("%d", result);
	break; }
    case '>': { int result = imply(pop(&st), pop(&st));
	push(&st, result);
	printf("%d", result);
	break;}
    case '-': { int result = not(pop(&st));
	push(&st, result);
	printf("%d", result);
	break; }
    default: {
      int num = convert(rpn[i]);
      push(&st, num);
      printf(" ");}
    }
  }
  return pop(&st);
}

//converts character 0 or 1 to the number
int convert(char bool) {
  if (bool == '0') {
    return 0;
  }
  else if (bool == '1') {
    return 1;
  }
  else {
    return bool;
  }
}

int not(int one) {
  return !one;
}

int and(int one, int two) {
  return one&&two;
}

int or(int one, int two) {
  return one||two;
}

int xor(int one, int two) {
  if (one&&two) {
    return 0;
  }
  else {
    return one||two;
  }
}

int equal(int one, int two) {
  return one == two;
}

int imply(int one, int two) {
  if (one == 0 && two == 1) {
    return 0;
  }
  else {
    return 1;
  }
}
