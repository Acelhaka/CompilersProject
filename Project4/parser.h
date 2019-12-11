#ifndef PARSER_H
#define PARSER_H

#include "node.h"
#include "token.h"
#include <fstream>
#include <iostream>


node_t* parser();
node_t* S(int treeDepth);
node_t* B(int treeDepth);
node_t* V(int treeDepth);
node_t* M(int treeDepth);
node_t* Mprime(int treeDepth);
node_t* Q(int treeDepth);
node_t* H(int treeDepth);
node_t* R(int treeDepth);
node_t* Q(int treeDepth);
node_t* T(int treeDepth);
node_t* A(int treeDepth);
node_t* Aprime(int treeDepth);
node_t* W(int treeDepth);
node_t* I(int treeDepth);
node_t* G(int treeDepth);
node_t* E(int treeDepth);
node_t* Z(int treeDepth);
void displayError();
node_t* getNode(string type);

#endif
