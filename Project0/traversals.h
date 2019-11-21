#ifndef TRAVERSALS_H
#define TRAVERSALS_H


#include "buildTree.h"

/*left - root -right*/
void traverseInOrder(TreeNode *nodePtr, ofstream &inOrderFile);

/*root - left - right*/
void traversePreOrder(TreeNode *nodePtr, ofstream &preOrderFile);

/*left - right- root*/
void traversePostOrder(TreeNode *nodePtr, ofstream &postOrderFile);

//up-down, left-right
void traverseLevelOrder(TreeNode *nodePtr, int level, ofstream &levelOrderFile);


#endif
