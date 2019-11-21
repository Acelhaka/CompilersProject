#ifndef BUILDTREE_H
#define BUILDTREE_H
 
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <cstdio>
#include <stdlib.h>    // using exit() to force the system to terminate
using namespace std;   // eliminate the usage of std

#include "node.h"			 


void insert(TreeNode *&nodePtr, TreeNode *&newNode);

void buildTree(char element, string str);

void printChar();

void traverseInOrder(ofstream &inOrderFile);

void traversePostOrder(ofstream &postOrderFile);

void traverseLevelOrder(ofstream &levelOrderFile);

void traversePreOrder(ofstream &preOrderFile);

void printParseTree(string node, int level);

void printParseTreeInFile(string node, int level, ofstream &outFile);

bool sameCharWord(string word);

vector<string> printSimilarWord(string word);

#endif
