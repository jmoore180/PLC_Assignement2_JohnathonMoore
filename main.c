#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int charClass;
char lexeme[100];
char reserveWords [10][10] = {"for", "if", "else", "while", "do", "int", "float", "switch","return"};
int totlex[1000];
int totcnt = 0;
int currlex = -1;
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp;
int lookup(char ch);
void addChar(void);
void getChar(void);
void getNonBlank(void);
int lex(void);
void expr(void);
void term(void);
void factor(void);
void error(void);

void syn(void);
void statement(void);
void whilestmt(void);
void boolexpr(void);
void id(void);
void block(void);
void dostmt(void);
void ifstmt(void);
void forstmt(void);
void returnstmt(void);
void assignstmt(void);

#define LETTER 0 
#define DIGIT 1 
#define SINGLEQUOTE 2 
#define DOUBLEQUOTE 3
#define DECIMAL 4 
#define UNDERSCORE 5
#define SEMICOL 6
#define UNKNOWN 99 


#define FLOAT_LIT 9
#define INT_LIT 10
#define IDENT 11
#define KEYWORD 12
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define DECIMAL_POINT 27
#define LESS_THAN 28
#define GREAT_THAN 29

#define FOR_CODE 30
#define IF_CODE 31
#define ELSE_CODE 32
#define WHILE_CODE 33
#define DO_CODE 34
#define INT_CODE 35
#define FLOAT_CODE 36
#define SWITCH_CODE 37
#define RETURN_CODE 38

#define LEFT_CURL 50
#define RIGHT_CURL 51

int main(void) {
  if ((in_fp = fopen("textFile.in", "r")) != NULL){
	 	getChar();
	 do {
	 	lex();
	 } while (nextToken != EOF);
  if(nextToken == EOF)
    syn();
    //expr();
	 }
   else{
     printf("No File \n");
   }
   return 0;
}

void addChar(void) {
	if (lexLen <= 98) {
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = '\0';
	} else
	printf("Error - lexeme is too long \n");
}

void getChar(void){
  if ((nextChar = getc(in_fp)) != EOF) {
		 if (isalpha(nextChar))
		 	charClass = LETTER;
		 else if (isdigit(nextChar))
		 	charClass = DIGIT;
     else if (nextChar == '_')
      charClass = UNDERSCORE;
		 else
		 	charClass = UNKNOWN;
	 } else
	 	charClass = EOF;
}

void getNonBlank(void) {
	while (isspace(nextChar))
	getChar();
}

int lex(void) {
	 lexLen = 0;
	 getNonBlank();
	 switch (charClass) {
		 case LETTER:
			 addChar();
			 getChar();
			 while (charClass == LETTER || charClass == DIGIT || charClass == UNDERSCORE) {
				 addChar();
				 getChar();
			 }
       if(strcmp(lexeme, reserveWords[0]) == 0)
        nextToken = FOR_CODE;
       else if(strcmp(lexeme, reserveWords[1]) == 0)
        nextToken = IF_CODE;
       else if(strcmp(lexeme, reserveWords[2]) == 0)
        nextToken = ELSE_CODE;
       else if(strcmp(lexeme, reserveWords[3]) == 0)
        nextToken = WHILE_CODE;
       else if(strcmp(lexeme, reserveWords[4]) == 0)
        nextToken = DO_CODE;
       else if(strcmp(lexeme, reserveWords[5]) == 0)
        nextToken = INT_CODE;
       else if(strcmp(lexeme, reserveWords[6]) == 0)
        nextToken = FLOAT_CODE;
       else if(strcmp(lexeme, reserveWords[7]) == 0)
        nextToken = SWITCH_CODE;
       else if(strcmp(lexeme, reserveWords[8]) == 0)
        nextToken = RETURN_CODE;
			 else
        nextToken = IDENT;
			 break;

     case UNDERSCORE:
       addChar();
       getChar();
       while (charClass == LETTER || charClass == DIGIT || charClass == UNDERSCORE) {
				 addChar();
				 getChar();
			 }
			 nextToken = IDENT;
			 break;

		 case DIGIT:
			 addChar();
			 getChar();
			 while (charClass == DIGIT) {
				 addChar();
				 getChar();
         if (nextChar == 'f' || nextChar == 'F' || nextChar == 'l' || nextChar == 'L'){
            addChar();
            getChar();
            nextToken = FLOAT_LIT;
            break;
         }
         if(nextChar == 'E' || nextChar == 'e'){
            addChar();
            getChar();
            if (nextChar == 'f' || nextChar == 'F' || nextChar == 'l' || nextChar == 'L'){
              addChar();
              getChar();
              nextToken = FLOAT_LIT;
              break;
            }
            if(nextChar == '-'){
              addChar();
              getChar();
              while(charClass == DIGIT){
                addChar();
                getChar();
                if (nextChar == 'f' || nextChar == 'F' || nextChar == 'l' || nextChar == 'L'){
                  addChar();
                  getChar();
                  nextToken = FLOAT_LIT;
                  break;
                }
              }
              nextToken = FLOAT_LIT;
              break;
            } else if(charClass == DIGIT){
              while(charClass == DIGIT){
                addChar();
                getChar();
                if (nextChar == 'f' || nextChar == 'F' || nextChar == 'l' || nextChar == 'L'){
                  addChar();
                  getChar();
                  nextToken = FLOAT_LIT;
                  break;
                }
              }
              nextToken = FLOAT_LIT;
              break;
			      }
         }
       }
       if (charClass == UNKNOWN && nextChar == '.'){
         addChar();
				 getChar();
         while (charClass == DIGIT) {
				  addChar();
				  getChar();
          if (nextChar == 'f' || nextChar == 'F' || nextChar == 'l' || nextChar == 'L'){
            addChar();
            getChar();
            nextToken = FLOAT_LIT;
            break;
          }
          if(nextChar == 'E' || nextChar == 'e'){
            addChar();
            getChar();
            if (nextChar == 'f' || nextChar == 'F' || nextChar == 'l' || nextChar == 'L'){
              addChar();
              getChar();
              nextToken = FLOAT_LIT;
              break;
            }
            if(nextChar == '-'){
              addChar();
              getChar();
              while(charClass == DIGIT){
                addChar();
                getChar();
                if (nextChar == 'f' || nextChar == 'F' || nextChar == 'l' || nextChar == 'L'){
                  addChar();
                  getChar();
                  nextToken = FLOAT_LIT;
                  break;
                }
              }
              nextToken = FLOAT_LIT;
              break;
            } else if(charClass == DIGIT){
              while(charClass == DIGIT){
                addChar();
                getChar();
                if (nextChar == 'f' || nextChar == 'F' || nextChar == 'l' || nextChar == 'L'){
                  addChar();
                  getChar();
                  nextToken = FLOAT_LIT;
                  break;
                }
              }
              nextToken = FLOAT_LIT;
              break;
            }
          }
         }
         nextToken = FLOAT_LIT;
       } else {
			 nextToken = INT_LIT;
       }
		 	break;
       
		 case UNKNOWN:
        if (nextChar == '.'){
          addChar();
          getChar();
          if(charClass == DIGIT){
            addChar();
            getChar();
            while(charClass == DIGIT){
              addChar();
              getChar();
              if (nextChar == 'f' || nextChar == 'F' || nextChar == 'l' || nextChar == 'L'){
                addChar();
                getChar();
                nextToken = FLOAT_LIT;
                break;
              }
              else if(nextChar == 'E' || nextChar == 'e'){
                addChar();
                getChar();
                if (nextChar == 'f' || nextChar == 'F' || nextChar == 'l' || nextChar == 'L'){
                  addChar();
                  getChar();
                  nextToken = FLOAT_LIT;
                  break;
                }
                if(nextChar == '-'){
                  addChar();
                  getChar();
                  while(charClass == DIGIT){
                    addChar();
                    getChar();
                    if (nextChar == 'f' || nextChar == 'F' || nextChar == 'l' || nextChar == 'L'){
                      addChar();
                      getChar();
                      nextToken = FLOAT_LIT;
                      break;
                    }
                  }
                  nextToken = FLOAT_LIT;
                  break;
                } else if(charClass == DIGIT){
                  while(charClass == DIGIT){
                    addChar();
                    getChar();
                    if (nextChar == 'f' || nextChar == 'F' || nextChar == 'l' || nextChar == 'L'){
                      addChar();
                      getChar();
                      nextToken = FLOAT_LIT;
                      break;
                    }
                  }
                  nextToken = FLOAT_LIT;
                  break;
			          }
              }
              nextToken = FLOAT_LIT;
            }
          } else {
            nextToken = DECIMAL_POINT;
          } 
        } else {
          lookup(nextChar);
          getChar();
        }
			 break;
		case EOF:
			 nextToken = EOF;
			 lexeme[0] = 'E';
			 lexeme[1] = 'O';
			 lexeme[2] = 'F';
			 lexeme[3] = '\0';
		 	break;
	 }
	 printf("Next token is: %d, Next lexeme is %s\n",
	 nextToken, lexeme);
   totlex[totcnt] = nextToken;
   totcnt++;
	 return nextToken;
}

int lookup(char ch) {
	 switch (ch) {
		 case '(':
			 addChar();
			 nextToken = LEFT_PAREN;
			 break;
		 case ')':
			 addChar();
			 nextToken = RIGHT_PAREN;
			 break;
		 case '+':
			 addChar();
			 nextToken = ADD_OP;
			 break;
		 case '-':
			 addChar();
			 nextToken = SUB_OP;
			 break;
		 case '*':
			 addChar();
			 nextToken = MULT_OP;
			 break;
		 case '/':
			 addChar();
			 nextToken = DIV_OP;
			 break;
		 case '=':
			 addChar();
			 nextToken = ASSIGN_OP;
			 break;
		 case '.':
			 addChar();
			 nextToken = DECIMAL_POINT;
			 break;
     case '"':
			 addChar();
			 nextToken = DOUBLEQUOTE;
			 break;
     case '\'':
			 addChar();
			 nextToken = SINGLEQUOTE;
			 break;
     case ';':
        addChar();
        nextToken = SEMICOL;
        break;
     case '<':
        addChar();
        nextToken = LESS_THAN;
        break;
     case '>':
        addChar();
        nextToken = GREAT_THAN;
        break;
     case '{':
        addChar();
        nextToken = LEFT_CURL;
        break;
     case '}':
        addChar();
        nextToken = RIGHT_CURL;
        break;
		 default:
			 addChar();
			 nextToken = EOF;
			 break;
	 }
	 return nextToken;
}

void expr(void) {
	 term();
	 while (nextToken == ADD_OP || nextToken == SUB_OP) {
		 lex();
		 term();
	 }
}

void term(void) {
	 factor();
	 while (nextToken == MULT_OP || nextToken == DIV_OP) {
		 lex();
		 factor();
	 }
}

void factor(void) {
	 if (nextToken == IDENT || nextToken == INT_LIT || nextToken == FLOAT_LIT)
		 lex();
	 else { if (nextToken == LEFT_PAREN) {
		 lex();
		 expr();
		 if (nextToken == RIGHT_PAREN)
		 	lex();
		 else
		 	error();
		 }
		 else
		 error();
	 }
	 printf("Exit <factor>\n");
}


void error(void){
 exit(1);
}

void syn(void){
  totcnt = 0;
  currlex = totlex[totcnt];
  printf("This is: %d\n", currlex);
  while(currlex != -1){
    statement();
  }
  printf("Code Is Correct!");
  return;
}

void statement(void){
  //printf("stmt\n");
  if(currlex == 33){
    whilestmt();
  }
  else if(currlex == 50){
    block();
  }
  else if(currlex == 34){
    dostmt();
  }
  else if(currlex == 31){
    ifstmt();
  }
  //else if(currlex == 30){
   // forstmt();
  //}
  else if(currlex == 11){
    assignstmt();
  }
  else if(currlex == 38){
    returnstmt();
  }
  return;
}

void whilestmt(void){
  printf("Whilestmt\n");
  totcnt++;
  currlex = totlex[totcnt];
    if(currlex != 25){
      error();
    }
    else{
      totcnt++;
      currlex = totlex[totcnt];
      if(currlex != 11){
        error();
      }
      else{
        boolexpr();
        totcnt++;
        currlex = totlex[totcnt];
        if(currlex != 26){
          error();
        }
        else{
          totcnt++;
          currlex = totlex[totcnt];
          return;
        }
      }
    }
    return;
}

void boolexpr(void){
  //printf("Boolexpr\n");
  totcnt++;
  currlex = totlex[totcnt];
  if(currlex == 20)
    {
      totcnt++;
      currlex = totlex[totcnt];
      if(currlex != 20)
        error();
      else{
        totcnt++;
        currlex = totlex[totcnt];
        id();
      }
    }

  else if(currlex == 28 || currlex == 29){
    totcnt++;
    currlex = totlex[totcnt];
    if(currlex == 20){
      totcnt++;
      currlex = totlex[totcnt];
      id();
    }
    else
      id();
  }
  
}

void id(void){
  if(currlex != 9 && currlex != 10 && currlex != 11)
    error();
  return;
}

void block(void){
  printf("Block\n");
  totcnt++;
  currlex = totlex[totcnt];
  if(currlex != 51){
    statement();
  } 
  totcnt++;
  currlex = totlex[totcnt];
  return;
}  

void dostmt(void){
  printf("doWhile\n");
  totcnt++;
  currlex = totlex[totcnt];
  if(currlex != 50)
    error();
  else{
    block();
    if(currlex != 33)
      error();
    else{
        whilestmt();
        if(currlex != 6)
          error();
        else{
          totcnt++;
          currlex = totlex[totcnt];
          return;
        }
    }
  }
}

void ifstmt(void){
  printf("ifstmt\n");
  totcnt++;
  currlex = totlex[totcnt];
    if(currlex != 25){
      error();
    }
    else{
      totcnt++;
      currlex = totlex[totcnt];
      if(currlex != 11){
        error();
      }
      else{
        boolexpr();
        totcnt++;
        currlex = totlex[totcnt];
        if(currlex != 26){
          error();
        }
        else{
          totcnt++;
          currlex = totlex[totcnt];
          statement();
          if(currlex == 32){
            printf("elsestmt\n");
            totcnt++;
            currlex = totlex[totcnt];
            statement();
          }
        }
      }
    }
    return;
}



void operation(void){
  printf("opperation\n");
  id();
  totcnt++;
  currlex = totlex[totcnt];
  if(currlex == 21 || currlex == 22 || currlex == 23 || currlex == 24){
    totcnt++;
    currlex = totlex[totcnt];
    id();
  }
  else{
    error();
  }
  totcnt++;
  currlex = totlex[totcnt];
  return;
}

void assignstmt(void){
  printf("assignstmt\n");
  totcnt++;
  currlex = totlex[totcnt];
  if(currlex != 20)
    error();
  else{
    totcnt++;
    currlex = totlex[totcnt];
    operation();
    if(currlex != 6){
      error();
    }
    else{
      totcnt++;
      currlex = totlex[totcnt];
      return;
    }
  }
}

void returnstmt(void){
  printf("returnstmt\n");
  totcnt++;
  currlex = totlex[totcnt];
  id();
  totcnt++;
  currlex = totlex[totcnt];
  return;
}