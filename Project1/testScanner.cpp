#include <fstream>
#include <iostream>
#include "testScanner.h"
#include "scanner.h"
#include <iomanip>

using namespace std;

int testScanner(ifstream &inFilter1){
	int lineNumber = 0;
	string line;

	//printing the header of the table that will be displayed on the 
	//screen for each token
	
	 cout << "|" << setw(11)  << "TokenType" << setw(16) << "TokenValue" << setw(13) << "LineNumber " << endl;
         cout << "|----------------------------------------" << endl;	
	/*opening the file after it was filtered
	and reading the lines one by one, this ease the
	process of keeping track of line numbers, after 
	each file read, pass the line and line number to 
	scanner so it can process */
	while(getline(inFilter1, line))
	{  
           //after each line read, increment line #
       	   lineNumber++;
	  
	   scanner(line, lineNumber);

	}
	cout <<"|" << setw(11) << "EOFtk" << endl << endl;

 return 0;

 }


