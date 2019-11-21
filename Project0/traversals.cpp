#include "traversals.h"
#include <iostream>
#include <iomanip>


void traverseInOrder(TreeNode *nodePtr,ofstream &inOrderFile)
{
	//left - root - right
	if (nodePtr)
	{
		traverseInOrder(nodePtr->left, inOrderFile);
		cout << nodePtr->str << " ";
		printParseTreeInFile(nodePtr->str, nodePtr->level+1, inOrderFile);
		string word = nodePtr->str;
		vector<string> sameChar = printSimilarWord(word);
		if(sameChar.empty() == false)
		{
			for(int i = 0; i < sameChar.size(); i++)
			{
				 cout << sameChar[i] << " ";
				 printParseTreeInFile(sameChar[i], nodePtr->level+1, inOrderFile);
                        }
				
					
		}

		traverseInOrder(nodePtr->right, inOrderFile);
		  
	}
	
}


void traversePostOrder(TreeNode *nodePtr, ofstream &postOrderFile)
{
	//left - right -root
	if (nodePtr)
	{
		traversePostOrder(nodePtr->left, postOrderFile);
		traversePostOrder(nodePtr->right, postOrderFile);
	 	printParseTreeInFile(nodePtr->str, nodePtr->level+1, postOrderFile);
		cout << nodePtr->str << " ";			       
		string word = nodePtr->str;
		vector<string> sameChar = printSimilarWord(word);
		if(sameChar.empty() == false)
	        {
		       for(int i = 0; i < sameChar.size(); i++)
		       {
		               cout << sameChar[i] << " ";
		               printParseTreeInFile(sameChar[i], nodePtr->level+1, postOrderFile);
		       }
		 
		 
		 }
	}
}
									
									
void traversePreOrder(TreeNode *nodePtr, ofstream &preOrderFile )
{
	//root - left - right
	if (nodePtr)
	{
		cout << nodePtr->str << " ";
		printParseTreeInFile(nodePtr->str, nodePtr->level+1, preOrderFile);
		string word = nodePtr->str;
		vector<string> sameChar = printSimilarWord(word);
		if(sameChar.empty() == false)
		{      
		    for(int i = 0; i < sameChar.size(); i++)
		    {
		             cout << sameChar[i] << " ";
		             printParseTreeInFile(sameChar[i], nodePtr->level+1, preOrderFile);
		    }
	       }
	 
		traversePreOrder(nodePtr->left, preOrderFile);
		traversePreOrder(nodePtr->right, preOrderFile);
	}
}



void traverseLevelOrder(TreeNode *nodePtr, int level, ofstream &levelOrderFile){
	if(nodePtr)
	{
		
		if(level == 1){
		    cout << nodePtr->str << " ";
		    printParseTreeInFile(nodePtr->str, nodePtr->level+1, levelOrderFile);
		    string word = nodePtr->str;
		    vector<string> sameChar = printSimilarWord(word);
                    if(sameChar.empty() == false)
		    {
			   for(int i = 0; i < sameChar.size(); i++)
			   {
			        cout << sameChar[i] << " ";
				printParseTreeInFile(sameChar[i], nodePtr->level+1, levelOrderFile);
		           }
		    }
 		}
		else if(level > 1)
		{
			traverseLevelOrder(nodePtr->left,level-1,levelOrderFile);
			traverseLevelOrder(nodePtr->right,level-1,levelOrderFile);
		}
	 }
}
