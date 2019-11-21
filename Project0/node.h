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

using namespace std;   // eliminate the usage of std


struct TreeNode
{
	char key;
	string str;
	TreeNode *left, *right;	
	int level;
	int maxLevel;

};	      





#endif 
