#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <cstdio>
#include <stdlib.h>    // using exit() to force the system to terminate
using namespace std;   // eliminate the usage of std


//#include "token.h"
#include "testScanner.h"

//This function checks if string is only alphabetic characters
//no digits, uppecase or special characters
bool validateString(string s);
int filter1(ifstream &fileInput);
ofstream filter1File;
bool isEmpty(ifstream &file);


int main (int argc, char *argv[]){
  ifstream fileInput, tempInput, inFilter1;
  ofstream fileOut;
  string fileName;
  string input = "";		
  char c; 
 
  //open a temporary file to write the input from 3 cases 
  fileOut.open("tempFile.txt");
  filter1File.open("filter1.txt");

  if( argc == 1) {
  	//reads from the keyboard until simulated EOF (Ctrl ^C)
	if(isatty(STDIN_FILENO) == 1){
			
		cout << "Enter input: ";
		//while reading the input, from terminal write it in fileOut
		while(cin.get(c)){
		   fileOut <<  c ;
		}
		cout << "\nReading input from terminal..." << endl;
	}

	//redirecting from filename instead of keyboard 
	else { 
		//while reading the input, from terminal write it in fileOut "tempFile.txt"
	 	while( cin.get(c)){
	         	fileOut << c ;
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
	
  }

  //if user enters more than two arguments, ERROR case, not allowed
  else {
	cout << "Fatal: Improper usage" << endl;
	cout << "Usage: scanner [filename]" << endl;
	cout << "Terminating program..." << endl;
	exit(0);
  }
 

  fileOut.close();
  tempInput.open("tempFile.txt");

  //if more than 2 arguments proccess the file name specified by the user
  if(argc == 2){
    filter1(fileInput);  
  } 
  else {	
     filter1(tempInput);
  }
  filter1File.close();
  inFilter1.open("filter1.txt");


  cout << "\n\n\n";

 //call testScanner to display each token of the table
  testScanner(inFilter1);

cout << endl << endl;

 
  
    
 


  cout << "\n\nEnd of program 1\n\n " << endl;
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

int filter1(ifstream &fileInput){

     int count = 0;
     bool skip = false;
     int countPer = 0;
     char ch;
     while (fileInput.get(ch)) {
     	 count++;
	 cout << ch;
     	 //if(ch == ' ')
	   // continue;
         if(ch == '\n'){
           count++;
         }
	 // skipping characters
         if(ch == '%'){
            countPer++;
	   // if skip = false, we have seen only the opening %
	   // we set skip to true so it can ignore any charcter after %
	   if(skip == false)
	     skip = true;
	   else
 	   //skip set to false if closing % is seen
	     skip = false;
	   continue;
	   } 

	  // if skip true ignore all other characters that is reading until
	  // skip state will change
	  if(skip == true){
	    continue;
	  }
	  filter1File <<  ch;
	 
	  
	}

	// checking if for every opening there is a closing comment %
	if(countPer % 2 == 1){
	  cout << "ERROR: Missing closing % for comment " << endl;
	  exit(0);
	}
return count;
}	

bool isEmpty(ifstream &file){
	string s;
	int count;
	bool empty = false;
	while(file >>  s){
	 count++;
	}

	if(count == 0)
		empty = true;
	file.close();
return empty;
}
