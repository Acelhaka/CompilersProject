#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <cstdio>
#include <stdlib.h>    // using exit() to force the system to terminate
#include <vector>
#include "token.h"
using namespace std;   // eliminate the usage of std


/*Number of childs is the maximum number of nonterminals 
 * that we have for a grammar EG: <I> -> if [ <M> <Z> <M> ] <T>
 * as seen we have four nonterminal that are M, Z, M and T
 * level keeps track of the tree level that each nodes belongs
 * label, describes the nonterminal (the function that is processing)
 * or the root for every subtree
 * vector <Token> token stores each token processed by the parser,
 * (token.instance, token.type, token.lineNumber) */

struct node_t
{
	node_t *child1, *child2, *child3, *child4;	
	int level;
	string label;
	vector<Token> token;  
};	      





#endif 
