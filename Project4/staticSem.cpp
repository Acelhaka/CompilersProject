#include "token.h"
#include "staticSem.h"
#include "node.h"
#include "scanner.h"
#include <stdio.h>
#include <iomanip>
using namespace std;
#include <string>
#include <sstream>


vector <Token> symbolTable;
int lineNum = 0;		  //used to display the lineNumber on the error message when a varaible is declared more than once
static unsigned int tempCount = 0;//used to create temporary varaibles
string ids;				
string temps;
string brContainer;		  //used to create branch names
static int brCount = 0;
static int inBrCount = 0;	  //used to create In branch names
string ro = "";    		  //storing relational operator
ostringstream oss;

/**********************************************************************
 * This file is used to test the tree that we
 * build in parser.cpp. Tree will be traversed in 
 * pre order, starting Root - left - right (in a binary tree)
 * in our case we have a tree with 4 children, therefore
 * it will process the root - child1 - child2 - child3 - child4
 * It will print the depth of the node, node label and tokens of the node
 * *********************************************************************/
void staticSematic(node_t *p, ofstream &asmFile){
	if(p == NULL)
		return;
	
	if(p){
		
		bool variableDec = false;
		
		//checking if we are declaring a variable or not
		if(p->label.compare("<V>") == 0){
			variableDec = true;
			
		}
		//processing all tokens/terminals that are 
		//sitting in the current node
		// and displaying them 
		for (unsigned int i = 0; i < p->token.size(); i++) {
			//checking if the label is <V>, if it is we look of the identifier declared
			if(variableDec){
				//call insert function to insert the identifier declared on the symbol table
				insert(p, i);
			}
			else{
				//if we are not in <V> node that we check if the identifier in the statements
				//is declared before use. 
				if(p->token[i].type == ID_tk && getIdentifierType(p->token[i].instance) == 0){
					if(verify(p->token[i].instance)){
						cout << "ERROR in line " << p->token[i].lineNumber << " identifier \"" << p->token[i].instance << "\", was not declared before." << endl;
						cout << "\n\n\nTerminating program.... \n";
						exit(0);
					}
				}			
			}
		
		}
		//codeGeneration(p, asmFile);
		if(p->label.compare("<S>") == 0){
			
			staticSematic(p->child1, asmFile);
			staticSematic(p->child2, asmFile);
		}
		//<v> - empty | var identifier . <V>
		if(p->label.compare("<V>") == 0){
		
			if(p->token.size() > 0){
				staticSematic(p->child1, asmFile);
			}
		}
		//<B> -> begin <V><Q>end
		if(p->label.compare("<B>") == 0){
		
			 staticSematic(p->child1, asmFile);
			 staticSematic(p->child2, asmFile);
		}
		//<Q> -> <T> # <Q> | empty
		if(p->label.compare("<Q>") == 0){
			
			 staticSematic(p->child1, asmFile);
			 staticSematic(p->child2, asmFile);
		}
		//<T> -> <A>, | <W>, | <B>, | <I<, | <G>, | <E>,
		if(p->label.compare("<T>") == 0){
			
			staticSematic(p->child1, asmFile);
		}
		//<A> -> scan <A'>
		if(p->label.compare("<A>") == 0){
			writeAtoAsm(p, asmFile);
			staticSematic(p->child1, asmFile);
		}
		//<A'> -> identifier | number
		if(p->label.compare("<A'>") == 0){
			writeAprimetoAsm(p, asmFile);
		}
		// <W> -> write <M>
		if(p->label.compare("<W>") == 0){
			asmFile << "LOAD ";
			staticSematic(p->child1, asmFile);  //process <M>
			writeWtoAsm(p, asmFile);
		}
		//<M> -> <H><M'>
		if(p->label.compare("<M>") == 0){
		        staticSematic(p->child1, asmFile);  //process <H>
			staticSematic(p->child2, asmFile);  //process <M'>

		}
		// <M'> -> +<M> | -<M> | /<M> | *<M> | empty
		if(p->label.compare("<M'>") == 0){
			if(p->token.size() > 0){
				string id = ids;
				writeMprimetoAsm(p, asmFile);      //write operator
				staticSematic(p->child1, asmFile); //process <M>
				oss << "";
				oss << "T" << tempCount;
				string tempVar = oss.str();
				tempCount++;
				oss.str("");
				asmFile << "STORE " << tempVar << endl;
				ids = tempVar;

			}
		}
		//<H> -> &<R> | <R>
		if(p->label.compare("<H>") == 0){
		        staticSematic(p->child1, asmFile);  //process R
			writeHtoAsm(p, asmFile);	    //find absolute value	
		}
		//<R> -> identifier | number
		if(p->label.compare("<R>") == 0){
			writeRtoAsm(p, asmFile);	   //writing id or number
		}
		//<E> -> let identifier : <M>
		if(p->label.compare("<E>") == 0){
			asmFile << "LOAD ";
			staticSematic(p->child1, asmFile); //process M
			writeEtoAsm(p, asmFile);	   //storing to a the identifier	
			
		} 
		//<I> -> if[<M><Z><M>]<T>
		if(p->label.compare("<I>") == 0){
			asmFile << "LOAD "; 
			staticSematic(p->child1, asmFile);  //process M
			staticSematic(p->child2, asmFile);  //process Z
			staticSematic(p->child3, asmFile);  //process M
		
			//for ">" and "<" "=" or "=="we are branching
			//":" not necessary to branch
			if(ro == ":"){ 
				staticSematic(p->child4, asmFile);
			}
			if(ro == ">"){
				 asmFile << "BRZNEG " << brContainer  << endl;	
				 staticSematic(p->child4, asmFile);
			 	 asmFile << brContainer << ": NOOP" << endl;
			}
			if(ro == "<"){
				asmFile << "BRZPOS " << brContainer  << endl;
				staticSematic(p->child4, asmFile);
				asmFile << brContainer << ": NOOP" << endl;
			}
			if(ro =="="){
				asmFile << "BRNEG " << brContainer  << endl;
				asmFile << "BRPOS " << brContainer  << endl;
				staticSematic(p->child4, asmFile);
				asmFile << brContainer << ": NOOP" << endl;
			}
		}
		//<Z> -> < | > | : | = | ==
		if(p->label.compare("<Z>") == 0){
			writeZtoAsm(p, asmFile); 	//write asm for operator
		}
		//<G> -> repeat [ <M><Z><M>] <T>
		if(p->label.compare("<G>") == 0){
			string inBranch =  getInBranchName(); 	//get in branch name Eg: In1
			asmFile << inBranch << ": LOAD " ;	
			staticSematic(p->child1, asmFile);	//process M		
			staticSematic(p->child2, asmFile);	//process Z
			staticSematic(p->child3, asmFile);	//process M
			if(ro == ":"){
				staticSematic(p->child4, asmFile);	//process T
				asmFile << "BR " << inBranch << endl;
			}
			if(ro == ">"){
			        asmFile << "BRZNEG " << brContainer  << endl;
				staticSematic(p->child4, asmFile);
				asmFile << "BR " << inBranch << endl;
			        asmFile << brContainer << ": NOOP" << endl;
			}
			if(ro == "<"){
			        asmFile << "BRZPOS " << brContainer  << endl;
			        staticSematic(p->child4, asmFile);
				asmFile << "BR " << inBranch << endl;
			        asmFile << brContainer << ": NOOP" << endl;
			}
			if(ro =="="){
			        asmFile << "BRNEG " << brContainer  << endl;
			        asmFile << "BRPOS " << brContainer  << endl;
			        staticSematic(p->child4, asmFile);
				asmFile << "BR " << inBranch << endl;
			        asmFile << brContainer << ": NOOP" << endl;
	                }

		}	
	} //end of if condition if(p)
}



void writeAtoAsm(node_t *p, ofstream &asmFile){

	asmFile << "READ ";
}

void writeAprimetoAsm(node_t *p, ofstream &asmFile){

	asmFile << p->token[0].instance << endl;
}

void writeMprimetoAsm(node_t *p, ofstream &asmFile){

	if(p->token[0].instance.compare("+") == 0){
		asmFile << "ADD ";
	}
	if(p->token[0].instance.compare("-") == 0){
	        asmFile << "SUB "; 
	}
	if(p->token[0].instance.compare("*") == 0){
	        asmFile << "MULT "; 
	}
	if(p->token[0].instance.compare("/") == 0){
	        asmFile << "DIV "; 
	}
}
	


void writeHtoAsm(node_t *p, ofstream &asmFile){
	//if token is "&" then we must take absolute value, otherwise we look 
	if(p->token.size() > 0)
	{	
		if(p->token[0].instance.compare("&") == 0){

		brContainer = getBranchName();
		//asmFile << "LOAD " << ids << endl;
		asmFile << "BRZPOS "  << brContainer <<  endl;
		asmFile << "MULT -1" << endl;
		asmFile << "STORE " << ids << endl;
		asmFile << brContainer << ": NOOP" << endl;
		//ids = tempVar;
		}
	}
}



void writeWtoAsm(node_t *p, ofstream &asmFile){
	asmFile <<"WRITE " ;
	asmFile << ids << endl;
}

void writeRtoAsm(node_t *p, ofstream &asmFile){

	asmFile << p->token[0].instance << endl;
	ids = p->token[0].instance;
}


void writeEtoAsm(node_t *p, ofstream &asmFile){
	//asmFile << "LOAD " << ids << endl;
	//storing token on position 2  "let identifier : <M>"
	//token[1] = identifier 
	ids = p->token[1].instance;
	asmFile << "STORE " << ids  << endl;
	
}
      
void writeZtoAsm(node_t *p, ofstream &asmFile){
	//asmFile << "LOAD " << ids << endl;
	if(p->token[0].instance.compare(">") == 0){
		asmFile << "SUB " ;//<< ids << endl;
		brContainer = getBranchName();
		
		ro = ">";
	}
 	if(p->token[0].instance.compare("<") == 0){
		 asmFile << "SUB " ; 
		 brContainer = getBranchName();
	
		 ro = "<";
	}
	if((p->token[0].instance.compare("=") == 0) || (p->token[0].instance.compare("==") == 0)){
		 asmFile << "SUB " ;
		 brContainer = getBranchName();

		 ro = "=";
	}
	if((p->token[0].instance.compare(":") == 0 )){
		 asmFile << "LOAD ";				 
		 ro = ":";
	}
	
}

/*********************************************************************
 * insert(String) - insert the string if not already there 
 * or error if already there. Insert fun with look at all identifiers
 * that are declared (under <V> label) and if another token of type ID_tk
 * and is classified as identifier it will call verify, and if the same
 * varaible is declared twice it will throw an error 
 * *********************************************************************/
void insert(node_t *p,unsigned int i){
	string declaredVar;
	//checking if token is of type ID_tk
         if(p->token[i].type == ID_tk){
	         //checking if identifier type is of type identifier (not keyword)
	         if(getIdentifierType(p->token[i].instance) == 0){
	                 //if all conditions met we store the identifier in a symbol table
			 declaredVar = p->token[i].instance;
			 if(verify(declaredVar) == false){
			           cout << "ERROR, variable \"" << declaredVar << "\" declared on line " << p->token[i].lineNumber << ", was previously declared  on line " << lineNum << endl;
			 	  cout << "\n\n\n Terminating program...\n";
				  exit(0);
			 }

                         symbolTable.push_back(p->token[i]);
                         //cout << "Instersted " << p->token[i].instance << endl;
                 }
        }


}


/************************************************************************
 * bool verify will check if the identifer traversed is in the tree
 * is already in the symbol table or not. This function is used to check
 * for both static semantic rules. If an identifer is declared more than once
 * or if an identifier is not declared at all but is being used.
 * *************************************************************************/
bool verify(string var){
	
	for(unsigned int i = 0; i < symbolTable.size(); i++){
		if(symbolTable[i].instance == var){
			lineNum = symbolTable[i].lineNumber;
			return false;				//identifier was found on the symbol table
		}
	}

   return true;							//identifier was not found on the symbol table
}


void printSymbolTb(ofstream &asmFile){

	// cout << "\nSymbol table:" << endl;
	 asmFile << "STOP" << endl;
	 for(unsigned int i = 0; i < symbolTable.size(); i++){
	 	//cout << symbolTable[i].instance << " " ;
		asmFile << symbolTable[i].instance << " 0" << endl;
	}

	//printing all temporary variables used in the assemblyFile Eg: T1 0
	for(unsigned int j = 0; j < tempCount; j++){
		asmFile << "T" << j << " 0" << endl;
	}

}

//will create a branchName by appending an incrementing number to "Done" + brCount which will keep track of brnaches created
string getBranchName(){
 oss << brCount;
 string brName = "Done" + oss.str();
 brCount++;
 oss.str("");
 return brName;
}

string getInBranchName(){
 oss << inBrCount;
 string brName = "In" + oss.str();
 inBrCount++;
 oss.str("");
 return brName;
}
