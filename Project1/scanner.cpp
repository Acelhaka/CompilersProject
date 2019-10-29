#include "scanner.h"
#include "token.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h> 
#include <string>
#include<bits/stdc++.h> 

using namespace std;

//defining FSA as descibed in scanner.h
int table[][CHAR_COL] = { {ERR_1, STATE_1, STATE_6, STATE_5, STATE_3, EOF_tk 	},
                             {STATE_2, STATE_2, STATE_2, ERR_2, ERR_2, ERR_2},
                             {STATE_2, STATE_2, STATE_2, ID_tk, ID_tk, ID_tk},
                             {EQ_tk, EQ_tk, EQ_tk, EQ_tk, STATE_4, EQ_tk},
                             {DEQ_tk, DEQ_tk, DEQ_tk, DEQ_tk, DEQ_tk, DEQ_tk},
                             {OP_tk, OP_tk, OP_tk, OP_tk, OP_tk, OP_tk},
                             {DIGIT_tk, DIGIT_tk, STATE_6, DIGIT_tk, DIGIT_tk, DIGIT_tk} };



/*scanner function will process each line passed by the  testScanner
 * and will start processing the lines char by char. For each char 
 * it will assign a col value,and for every new token will start 
 * with an INITIAL state. Overhead is also implemented in this 
 * function. if it sees a whitespace it will ignore and start 
 * processing the other tokens, until a char other than white 
 * space is found						*/

void scanner(string line, int lineNumber){
	Token token;
	char ch;
	int col;
	int state = INITIAL;
	unsigned int i = 0;
	bool lookahead = false;
	int nextState;
	string s = "";
	ch = line[i];
	token.lineNumber = lineNumber;
         while(i <= line.length()){

		 col = getColIndex(ch);
	         nextState = table[state][col];

	  //if identified an error state display the message
	  if(errorState(nextState)){
	  	displayErrorMessage(nextState);
	        state = INITIAL;   
		exit(0);
	  }
	  //if identified a final state, display the tokens
	  //and call filter2 if tokken is identifier
	  else if(nextState > 10 && nextState <= 16){
	     if(lookahead == false){		
		token.instance.assign(s);
		token.type = nextState;
		displayToken(&token);
		}
		state = INITIAL;
		if(ch== 32){
		  lookahead  = true;
		  continue;
		 }
		s="";
	     
		lookahead = false;
	   }
	   //not reached final state yet
	  else {
	  
	  	s += ch;
	   	state = nextState;
		i++;
	 	ch = line[i]; 	
	}
    }
	 
}


/*functin will identify if we reach an error state
* error states are all token that we have assigned values
* from -1001 & -1002, it will return a boolean,to show if error
* state or not  */
bool errorState(int state){
	if(state < -1000)
		return true;
return false;
}


/*functin will identify if we reach final state
 * final states are all token that we have assigned values 
 * from 10 -16, it will return a boolean,to show if final 
 * state or not						*/
bool finalState(int state){
	if(state > 10 && state <= 16)
	   cout << "final state " << endl;
		return true;
return false;
}


/*functions get each character and matchese it
 * with a column number from the table,
 * will return the col number of the char */
 int getColIndex(char ch){
       int col = 0;
       if(ch >= 65 && ch <= 90)
          col = UPPER;
         else if( ch >= 97 && ch <= 122)
                 col = LOWER;
         else if(ch >= 48 && ch <= 58)
                col = DIGIT;
         else if(ch == 61)
                col = EQUAL;
         else
                col = OPERATOR;
  return col;
 }


/*Function to display each token, token type, line number
 * receives as an input the token struct and prints on the 
 * screen characteristics of each. */
void displayToken(Token *t){
	
	   if(t->type == ID_tk){
	   	//keyword
	   	if(getIdentifierType(t->instance) == 1)
			cout <<"|" <<  setw(12) << "Keyword " << setw(15) << t->instance << setw(12) << t->lineNumber << endl;
		else
			cout << "|" << setw(12) << "Identifier " << setw(15)  <<  t->instance << setw(12) << t->lineNumber << endl;
	   }
	   else if(t->type == DIGIT_tk){
	   	cout <<"|" <<  setw(12)  << "Digit " << setw(15) <<  t->instance << setw(12) << t->lineNumber << endl;
	   }
	   else if(t->type == OP_tk || t->type == EQ_tk){ 
	   	if(t->instance[0] != 32)
		 	cout << "|" << setw(12)  << "Operator " << setw(15) << t->instance << setw(12) << t->lineNumber << endl;
	   }
	   else{
	   	cout << "|" << setw(12)  << "Operator " << setw(15) << t->instance << setw(12) << t->lineNumber << endl;
	   }
 }

 /* function represents filter2, checks if
  * an identifier is a keywork
  * Will loop in array of keywords, until
  * it finds a match, then return keyword
  * otherwise will return identifier = 0*/
 int getIdentifierType(string s){
  string keywords[] = {"begin", "end", "repeat", "if", "then", "let", "void", "var", "return", "scan", "write", "program"};

  for(int i = 0; i < 12; i++){
     if( s.compare(keywords[i]) == 0)
       	return 1;           //keyword
  }
  return 0;		    //identifier
  }



/*function will compare the error identified and display
 * the message related to it	
 * if error = ERR_1, we have a token starting with capital letter
 * if error = ERR_2  we have an identifier token less than 2 char*/
  void displayErrorMessage(int err){
  if(err == ERR_1)
     cout << "|  ERROR: Tokens should not start with capital letters. " << endl;
  else if(err == ERR_2)
    cout << "|  ERROR: Identifier token should be at least 2 characters " << endl;
  return;
   }
