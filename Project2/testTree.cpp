#include "token.h"
#include "node.h"

#include <stdio.h>
#include <iomanip>
using namespace std;


/*This file is used to test the tree that we
 * build in parser.cpp. Tree will be traversed in 
 * pre order, starting Root - left - right (in a binary tree)
 * in our case we have a tree with 4 children, therefore
 * it will process the root - child1 - child2 - child3 - child4
 * It will print the depth of the node, node label and tokens of the node*/
void traversePreOrder(node_t *p){
	if(p == NULL)
		return;
	if(p){
		//shifting the output ny two spaces according to the
		//depth of the tree that the node is sitting
		cout <<"|" << setw(p->level*2) <<  p->level << ": ";
		cout << p->label << " " ;
		//processing all tokens/terminals that are 
		//sitting in the current node
		// and displaying them 
		for (int i = 0; i < p->token.size(); i++) 
		         cout << p->token[i].instance << " "; 
		cout << endl;
		
		traversePreOrder(p->child1);
		traversePreOrder(p->child2);
		traversePreOrder(p->child3);
		traversePreOrder(p->child4);
	}
}


