#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"
#include <fstream>
#include <iostream>

const int UPPER = 0;
const int LOWER = 1;
const int DIGIT = 2;
const int OPERATOR = 3;
const int EQUAL = 4;
const int EOF_ = 5;

const int ERR_1 = -1001;
const int ERR_2 = -1002;

const int ID_tk = 11;
const int DIGIT_tk = 12;
const int OP_tk = 13;
const int EOF_tk = 14;
const int EQ_tk = 15;
const int DEQ_tk = 16;

const int INITIAL = 0;
const int STATE_1 = 1;
const int STATE_2 = 2; 
const int STATE_3 = 3;
const int STATE_4 = 4;
const int STATE_5 = 5;
const int STATE_6 = 6;

const int CHAR_COL = 7;
const int STATE = 7;


/*Finate State Automaton table */

/*********************************************************************
 * 	[A-Z]	[a-z]	[0-9]	[operator]	[=]	[EOF]
 * S0	ERROR    S1      s6      s5	        s3      EOF_tk		 
 * S1   S2  	 s2	 s2 	 ERROR          ERROR 	ERROR
 * S2	S2	 S2	 S2	 ID_tk	 	ID_tk	ID_tk
 * S3   EQ_tk	 EQ_tk	EQ_tk	 EQ_tk		s4	EQ_tk
 * s4   DE_tk	 DE_tk	DE_tk	 DE_tk		DE_tk	DE_tk
 * S5 	OP_tk	 OP_tk	OP_tk	 OP_tk		OP_tk	OP_tk
 * S6	D_tk	 D_tk	s6	 D_tk	        D_tk 	D_tk
 * *******************************************************************/




void scanner(string line, int lineNumber);
int getColIndex(char ch);
bool errorState(int state);
bool finalState(int state);
void displayToken(Token *t);
int getIdentifierType(string s);
void displayErrorMessage(int err);

#endif
