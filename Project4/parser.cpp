#include "parser.h"
#include "scanner.h"
#include "token.h"
#include "node.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>   //exit function
#include <string>
#include<bits/stdc++.h>
using namespace std;


Token tk;
static int k = 1;		//keeps track of tokens that need to be processed by scanner
static string expectedTk = "";	//added expectedTk for debbugging
				//also a useful component to display on the
				//error message, will tell the user what this the expected token for the error thrown


node_t * parser(){
   int treeDepth = 0;       //to keep track of tree level after each function treeLevel(depth increces)
  // cout <<"Starting parser" << endl << endl;
   node_t* root;

   tk = scanner(k);	
   root = S(treeDepth); 				//processing S
   if(tk.type == EOF_tk){	
     //after each statement is checked and last token type is EOF
     //indicates that the statements were correct with the grammar
   //  cout << "File was parsed Successfully" << endl;
   }
   else {
   	expectedTk = "EOF_tk";	
   	displayError();
	
   }

   return root;
}
	

node_t* S(int treeDepth){
  // cout << "processing S" << endl;
   node_t *p = getNode("<S>");			//allocate memory for each child and assign the root to be
    p->level = treeDepth;			//<S> (label the root node)
    if (tk.instance == "program"){		//one node processed increment treeDepth
	  treeDepth++;
   	p->token.push_back(tk);
   	k++;
   	tk = scanner(k);	
  	p->child1 = V(treeDepth);		//processing V and assigning to child1 (leftmost child)
  	p->child2 = B(treeDepth);		//processing B and assigning to child2 (next to the leftmost child)
   }
   else {
   	expectedTk = "program";			//otherwise display an error because first line of file
   	displayError();				//according to grammar should be "program"
   }
   return p;
}
	

node_t* B(int treeDepth){
   node_t *p = getNode("<B>");			//label the root node of the subtree to <B> and allocate
   if (tk.instance == "begin"){			// memory, assign the child1-4 to NULL
     	p->level = treeDepth; 	

     	p->token.push_back(tk);			//each token/terminal part of <B> assign to the vector Structure 
    	k++;					
	treeDepth++;
  	tk = scanner(k);			//consume begin
    	p->child1 = V(treeDepth);
  	  p->child2 = Q(treeDepth);
	if(tk.instance == "end"){
	  p->token.push_back(tk);
	  k++;
          tk = scanner(k);     			//consume token end
	  return p;
	}
	else{
	  expectedTk = "end";			//if the expected token "end" is not seen through an error message
	  displayError();
	}
   }
   else {
       expectedTk = "begin";
       displayError();
   }

   return p;
}


node_t* V(int treeDepth){
 
   node_t* p = getNode("<V>");			//allocate memory and assign the root of subtree with label <V>
 
   if(tk.instance == "var"){
   	p->level = treeDepth;
   	p->token.push_back(tk);
	treeDepth++;
   	k++;
	tk = scanner(k);			//consume token var
	if(getIdentifierType(tk.instance) == 0){
	   p->token.push_back(tk);
	   k++;
	   tk = scanner(k);
	   if(tk.instance == "."){
	      p->token.push_back(tk);
	      k++;
	      tk = scanner(k);			//consume token .
      	      p->child1=V(treeDepth);		//call V and assign the return value to child1
	      return p;
	   }
	   else {
	   	expectedTk = ".";
	   	displayError();
	   }
	}
	else{
	   expectedTk = "ID_tk";  
	   displayError();
	}
   }
   else {			        	//predicts V is empty
   	return NULL;
  }

  return p;
}


node_t* M(int treeDepth){
  // cout << "Process M " << endl;
   node_t *p = getNode("<M>");
   p->level = treeDepth;
   treeDepth++;
   p->child1 = H(treeDepth);			//processing H
   p->child2 = Mprime(treeDepth);		//processing Mprime
   return p;
}


//process M' nonterminal
node_t* Mprime(int treeDepth){
  // cout << "Process Mprime " << endl;
   node_t *p = getNode("<M'>");
   //checking if first token is part of first set of M'
   if(tk.instance == "+" || tk.instance == "-" || tk.instance == "/"
     || tk.instance == "*"){
     p->level = treeDepth;
     p->token.push_back(tk);
     k++;
     tk = scanner(k);	 			//processing the operator
     treeDepth++;
     p->child1 = M( treeDepth);			//processing M
     return p;
   }
   else 
   	return NULL;				//predict Mprime -> empty
}


//process H
node_t* H(int  treeDepth){
   //cout << "Process H " << endl;
   node_t *p = getNode("<H>");
   if(tk.instance == "&"){
 
	p->level = treeDepth;
       	treeDepth++;
   	p->token.push_back(tk);
   	k++;
   	tk = scanner(k); 			//consume &
	 p->child1 = R(treeDepth);		//processing R
	return p;
   }
   //getIdentifierType will return 1 if identifier is a keyword and 0 otherwise
   else if(getIdentifierType(tk.instance) == 0 || tk.type == DIGIT_tk){
   	  p->level = treeDepth; 	
	  treeDepth++;
	  p->child1 = R(treeDepth);
	return p;
   }
   else{
	expectedTk = "& or ID_tk or DIGIT_tk";
	displayError();
   }

   return p;
   	
}


//process R
node_t* R(int treeDepth){
  // cout << "Process R" << endl;
   node_t* p = getNode("<R>");
   
   p->level = treeDepth;
   treeDepth++;
   if(getIdentifierType(tk.instance) == 0 || tk.type == DIGIT_tk){	//<R> -> id | digit
   	p->token.push_back(tk);
  	k++;
   	tk = scanner(k);
	return p;
   }
   else {
   	expectedTk = "ID_tk or DIGIT_tk" ;
        displayError();
   }

   return p;
}


//process Q
node_t* Q(int treeDepth){
  // cout << "Process Q" << endl;
   node_t * p = getNode("<Q>");
   //checking if first token is part of first set for Q
   if(tk.instance == "scan" || tk.instance == "write" || tk.instance == "begin" || tk.instance == "if" || tk.instance == "repeat" || tk.instance == "let"){
 
 	 p->level = treeDepth;
  	treeDepth++;
   	p->child1 = T(treeDepth);				//processing T
   	if(tk.instance == "#"){	
		p->token.push_back(tk);
   		k++;
		tk = scanner(k);			        //consume #
		p->child2 = Q(treeDepth);			//processing Q
		return p;
	}
	else{
		expectedTk = "#";
		displayError();
	}
   }
   else{
	return NULL;		 				//predicts Q->empty
   }

   return p;
}


node_t* T(int treeDepth){
  // cout << "Process T" << endl;
   node_t *p = getNode("<T>");
   
   p->level = treeDepth;
   treeDepth++;
   if(tk.instance == "scan"){
   	p->child1 = A(treeDepth);				//processing A
	if(tk.instance == ","){
		p->token.push_back(tk);
		k++;
		tk = scanner(k);				//consume ,
		return p;
	}
	else{
		expectedTk = ",";
		displayError();
	}

   }
   else if(tk.instance == "write"){
   	p->child1 = W(treeDepth);				//processing W
	if(tk.instance == ","){
		p->token.push_back(tk);
	      	k++;
		tk = scanner(k); 		  	        //consume ,
		return p;
	}	
  	else{
		expectedTk = ",";
		displayError();
	}	
   }
   else if(tk.instance == "if"){
  	p->child1 = I(treeDepth);				//processing I
	if(tk.instance == ","){
		p->token.push_back(tk);
		k++;
		tk = scanner(k);				//consume ,
		return p;
	  }
     	else{
		expectedTk = ",";
		displayError();
	}
   }
   else if(tk.instance == "repeat"){
   	p->child1 = G(treeDepth);				//processing G
	if(tk.instance == ","){
		p->token.push_back(tk);
		k++;
		tk = scanner(k);				//consume ,
		return p;
	}
	else {
		expectedTk = ",";
		displayError();
	}
   }
   else if(tk.instance == "let"){
   	p->child1 = E(treeDepth);				//processing E
	if(tk.instance == ","){
		p->token.push_back(tk);
		k++;
		tk = scanner(k);				//consuming ,
		return p;
	}
 	else{
		expectedTk = ",";
		displayError();
	}
   }
   else if(tk.instance == "begin"){
   	p->child1 = B(treeDepth);
	return p;
   }
   else {
   	expectedTk = "repeat, let, begin, scan, write or if";
   	displayError();
   }

   return p;
}



node_t* A(int treeDepth){
  // cout << "Process A" << endl;
   node_t *p = getNode("<A>");
   p->level = treeDepth;
   treeDepth++;

   if(tk.instance == "scan"){
   	p->token.push_back(tk);
   	k++;
	  tk = scanner(k);					//consume scan
	  p->child1 = Aprime(treeDepth);			//processing Aprime
	return p;
   }
   else {
   	expectedTk = "scan";
   	displayError();
   }
   return p;
}


node_t* Aprime(int treeDepth){
   //cout << "Process Aprime" << endl;
   node_t *p = getNode("<A'>");
   p->level = treeDepth;
   treeDepth++;
   if(getIdentifierType(tk.instance) == 0 || tk.type == DIGIT_tk){
   	p->token.push_back(tk);
   	k++;
	tk = scanner(k);					//consume ID or Digit tk
	return p;
   }
   else {
        expectedTk = "ID_tk or DIGIT_tk";
  	displayError();			
  }
  return p;

}


node_t* W(int treeDepth){
  // cout << "Process W" << endl;
   node_t *p = getNode("<W>");
   p->level = treeDepth;

   treeDepth++;
    if(tk.instance == "write"){
   	p->token.push_back(tk);
	k++;
	tk = scanner(k);				//consume token write
	p->child1 = M(treeDepth);			//processing M
	return p;
   }
   else{
   	expectedTk = "write";
   	displayError();
   }
   return p;
}



node_t* I(int treeDepth){
  // cout << "Process I" << endl;
   node_t *p = getNode("<I>");
   p->level = treeDepth;
   treeDepth++;
   if(tk.instance == "if"){
   	p->token.push_back(tk);
   	k++;
	tk = scanner(k);					//consume token if
	if(tk.instance == "["){
		p->token.push_back(tk);
		k++;
		tk = scanner(k);				//consume token [
		p->child1 = M(treeDepth);			//processing M
		p->child2 = Z(treeDepth);			//processing Z
		p->child3 = M(treeDepth);			//processing M
		if(tk.instance == "]"){
			p->token.push_back(tk);
			k++;
			tk = scanner(k);		        //consume token ]
			p->child4 = T(treeDepth);		//processing T
			return p;
		}
		else{	
			expectedTk = "]";
			displayError();
		}
	}
	else{
		expectedTk = "[";
		displayError();
	}
    }
    else {
    	expectedTk = "if";
    	displayError();
    }

    return p;
}



node_t* G(int treeDepth){
   //cout << "Process G" << endl;
   node_t *p = getNode("<G>");
   
   p->level = treeDepth;
   treeDepth++;
   if(tk.instance == "repeat"){
   	p->token.push_back(tk);
	k++;
	tk = scanner(k);      		     	     //consume token repeat
	if(tk.instance == "["){
		p->token.push_back(tk);
		k++;
		tk = scanner(k); 	       	        //consume token [
		p->child1 = M(treeDepth);	        //processing M
		p->child2 = Z(treeDepth);               //processing Z
		p->child3 = M(treeDepth);               //processing M
		if(tk.instance == "]"){
		  p->token.push_back(tk);
		  k++;
		  tk = scanner(k);			//consume token ]
	 	  p->child4 = T(treeDepth);   		//processing T
		  return p;
		}
		else{
			expectedTk = "]";
			displayError();
		}
	}
	else{
		expectedTk = "[";
	       displayError();
	}
   }							
   else {
   	expectedTk = "repeat";
   	displayError();
  }
  return p;
 }



node_t* E(int treeDepth){
	//cout << "processing E " << endl;
	node_t *p = getNode("<E>");

	p->level = treeDepth;
 	treeDepth++;
	if(tk.instance == "let"){
		p->token.push_back(tk);
		k++;
		tk = scanner(k);				//consuming let
		if(getIdentifierType(tk.instance) == 0){
			p->token.push_back(tk);
			k++;
			tk = scanner(k);			//consume token identifier
			if(tk.instance == ":"){
				p->token.push_back(tk);
				k++;
				tk = scanner(k);		//consume token :
				p->child1 = M(treeDepth);	//processing M
				return p;
			}
			else {
				expectedTk = ":";
				displayError();
			}
		}
		else {
			expectedTk = "ID_tk";
			displayError();
		}
	}
	else{
		expectedTk = "let";
		displayError();
	}

	return p;
}


//nonterminal Z
node_t* Z(int treeDepth){
	node_t *p = getNode("<Z>");
	
	p->level = treeDepth;
 treeDepth++;
	if(tk.instance == "<" || tk.instance == ">" || tk.instance == ":" ||
	tk.instance == "=" || tk.instance == "=="){
		p->token.push_back( tk);
		k++;
		tk = scanner(k);		//consume the token < or > or : or == or =	
		return p;
	}
	else {
		expectedTk = "<, >, :, = or == tokens";
		displayError();
	}
   return p;
}



/*displayError will be called when an error is spotted 
 * on the grammar. it will display the line Number where
 * the error was found and will also display what the token
 * or expected token should have been along with the 
 * wrong token invoked*/
 
void displayError(){
	cout << "ERROR at line: " << tk.lineNumber << ", Wrong token \"" << tk.instance << "\",  Expected token: \"" <<
	expectedTk << "\" " << endl;
	cout << endl ;
	cout << "Terminating Program... \n\n"<< endl;
	exit(0);

}


/*getNode allocated a new node after each function call
 * and will label the nonterminal with a description 
 * Eg: nonterminal <B> is label with "<B>" when function B() 
 * is called*/
node_t *getNode(string type){
	node_t *p = new node_t();
	p->child1 = NULL;
	p->child2 = NULL;
	p->child3 = NULL;
	p->child4 = NULL;
	p->label = type;
	return p;
}
