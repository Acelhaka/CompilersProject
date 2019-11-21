#include "buildTree.h"
#include "traversals.h"
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

vector<string> words;         //stores all the words traversed by the BST
vector<string> similarWords;  //stores all the words which first character was previously seen by BST

TreeNode *root ;
int maxLevel = 0;	      //stores the maxLevel of the tree, used for levelOrder traversals

void insert(TreeNode *&nodePtr, TreeNode *&newNode)
{
	int level = 0;
	if (nodePtr == 0)
	{
		nodePtr = newNode;
	
	}
	else if (newNode->key < nodePtr->key)
	{
		 //calling insert function to create a new node pointing to theleft		
		 insert( nodePtr->left, newNode);
	 	 newNode->level++;	
		 level = newNode->level;
		 if(level > maxLevel)
		 	maxLevel = level;
	}
	else
	{
	 	
	 	insert(nodePtr->right, newNode);
		newNode->level++;
		level = newNode->level;
		if(level > maxLevel)
			maxLevel = level;
	}
	 
}


/*TreeInsert function will create a new node for each element it will take*/
void buildTree(char input, string str)
{
	TreeNode *newNode = 0;
	
	newNode = new TreeNode;
	newNode->key = input;
	newNode->left = newNode->right = 0;
	newNode->str = str;
	newNode->level = 0;
	if(sameCharWord(str)){
		similarWords.push_back(str);
	}
	else{

		words.push_back(str);
		insert(root, newNode);
	}
	

}


void printParseTree(string node, int level){
	
	 cout << "|" << setw(level*2) << level <<": " << node << endl;
	 	
}


void printParseTreeInFile(string node, int level, ofstream &outFile){

         outFile << "|" << setw(level*2) ;
         outFile << level ;
         outFile <<": " ;
	 outFile << node[0] << " ";
         outFile << node << endl;
}




void traverseInOrder(ofstream &inOrderFile)
{
	traverseInOrder(root, inOrderFile);
}


void traversePostOrder(ofstream &postOrderFile)
{
	traversePostOrder(root, postOrderFile);
}


void traversePreOrder(ofstream &inOrderFile)
{
	traversePreOrder(root, inOrderFile);
}



void traverseLevelOrder(ofstream &levelOrderFile)
{	
	for (int i = 0; i < maxLevel+1; i++){
	
        traverseLevelOrder(root,i+1, levelOrderFile);
	}
 }     


//finds word in the file that start with the same char
bool sameCharWord(string word)
{  if(words.size() > 0){
	for(int i = 0; i < words.size(); i++)
	{
		if(word[0] == words[i][0]){
		return true;
		}
	}
    }	
    return false;
}


//if words start with the same char, store in a vector
vector<string> printSimilarWord(string word)
{
   vector<string> sameChar;
   for(int i = 0; i < similarWords.size(); i++)
   {
	 if(word[0] == similarWords[i][0]){
		 sameChar.push_back(similarWords[i]);
	}
   }
  return sameChar;
}
