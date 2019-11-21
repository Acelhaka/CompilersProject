/************************************
*Amarilda Dyrmishi
*CS 4280
*Project 0
*9/22/2019
**************************************/


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <cstdio>
#include <stdlib.h>    // using exit() to force the system to terminate
using namespace std;   // eliminate the usage of std

#include "buildTree.h"



//This function checks if string is only alphabetic characters
//no digits, uppecase or special characters
bool validateString(string s);


int main (int argc, char *argv[]){
  ifstream fileInput;	
  ofstream fileOut;
  ofstream levelOrderFile, inOrderFile, preOrderFile, postOrderFile;
  string fileName;
  string input = "";		
 
 
  //open a temporary file to write the input from 3 cases 
  fileOut.open("tempFile.txt");

  if( argc == 1) {
  	//reads from the keyboard until simulated EOF
	if(isatty(STDIN_FILENO) == 1){
			
		cout << "Enter input: ";
		//while reading the input, from terminal write it in fileOut
		while(cin >> input){
			fileOut << input << " ";
		}
		cout << "\nReading input from terminal..." << endl;
	}

	//redirecting from filename instead of keyboard 
	else { 
		//while reading the input, from terminal write it in fileOut "tempFile.txt"
	 	while( cin >> input){
			fileOut << input << " ";
	  	 }

		 cout << "\nReading input from redirected file... " << endl;
	}
  }	
   
   //if user enters two arguments, executable + filename
  else if (argc == 2) {
	//read from the file
	fileName = argv[1];

	cout << "FileName : " << fileName <<endl;
	fileInput.open(fileName.c_str());
	if(!fileInput){
	   cout << "ERROR: File does not exist" << endl;
	   exit(0); 
	 }
	 cout << "Reading from the file....." << endl;
	 while( fileInput >> input){
	 	 fileOut << input << " ";
	 }
	
  }

  //if user enters more than two arguments, ERROR case, not allowed
  else {
	cout << "Fatal: Improper usage" << endl;
	cout << "Usage: P0 [filename]" << endl;
	cout << "Terminating program..." << endl;
	exit(0);
  }
 

  string nodes;
  //close the input file and output file
  fileInput.close();
  fileOut.close();

  //open output file "tempFile.txt" in read mode
  fileInput.open("tempFile.txt");
  int count = 0;	//varaible to check if file is empty (if input == 0, file is empty)
  while(fileInput >> nodes){
	count++;
	cout << nodes << " " ;
      //first validate user input, if used upper case, digits or special characters prompt the error message and terminate
    	if(validateString(nodes) == false){
    		cout << "\nERROR: Input contains digits or special characters " << endl;
		exit(0);
  	}
   }

    cout << endl << endl;

   //check if file is empty
    if(count == 0){
             cout << "\n\nERROR: File is Empty" << endl;
	     cout << "Terminating program..." << endl;
             exit(0);
    }

     fileInput.close();
     fileInput.open("tempFile.txt");
 
  //after input is validated, build the tree
    cout << "Building Binary Search Tree..." << endl;

    while(fileInput >> nodes){
         char node = nodes[0];
	 
    	 buildTree(node, nodes);
		 
    }
     
	 fileInput.close();
	 fileInput.open("tempFile.txt");
    string fileName1, fileName2, fileName3, fileName4;
   if(argc == 2){
   	  
	fileName1 = fileName + ".inorder";
  	inOrderFile.open(fileName1.c_str());
	fileName2 = fileName + ".preorder";
	preOrderFile.open(fileName2.c_str());
	fileName3 = fileName + ".postorder";
	postOrderFile.open(fileName3.c_str());
	fileName4 = fileName + ".levelorder";
	levelOrderFile.open(fileName4.c_str());

	 while(fileInput >> nodes){
	       inOrderFile << nodes << " ";
	       preOrderFile << nodes <<" ";
	       levelOrderFile << nodes << " ";
	       postOrderFile << nodes <<" ";
	   }
	  inOrderFile << endl;
	  preOrderFile << endl; 
	  levelOrderFile << endl;
	  postOrderFile << endl;
  }
   else {
   	  fileName1 = "out.inorder";
	  inOrderFile.open(fileName1.c_str());
	  fileName2 = "out.preorder";
	  preOrderFile.open(fileName2.c_str());
	  fileName3 = "out.postorder";
	  postOrderFile.open(fileName3.c_str()); 
	  fileName4 = "out.levelorder";
	  levelOrderFile.open(fileName4.c_str());
   }


  cout <<"\n\nLevel Order traversals..." << endl;
  traverseLevelOrder(levelOrderFile);

  cout << "\n\nIn order traversals..." << endl;
  traverseInOrder(inOrderFile);

  cout <<"\n\nPost Order traversals.." << endl;
  traversePostOrder(postOrderFile);

  cout <<"\n\nPre Order traversals.." << endl;
  traversePreOrder(preOrderFile);

  cout << "\n\nEnd of program 0\n\n " << endl;
  return 0;

}

bool validateString(string s){
    int len = s.length();
    //check each character of a string
    for (int i = 0; i < len; i++){
    	//checking for ASCII code that represent alpha characters only
	if(s[i] < 97 || s[i] > 122)
	    return false;
    }
     return true;
 }
 
