#ifndef STATICSEM_H
#define STATICSEM_H
#include "node.h"

void staticSematic(node_t *p, ofstream &asmFile);
void insert(node_t *p, unsigned int i);
bool verify(string var);
void printSymbolTb(ofstream &asmFile);
void codeGeneration(node_t *p, ofstream &asmFile);
void writeStoAsm(node_t *p,ofstream &asmFile );
void writeVtoAsm(node_t *p,ofstream &asmFile );
void writeBtoAsm(node_t *p,ofstream &asmFile );
void writeAtoAsm(node_t *p,ofstream &asmFile );
void writeQtoAsm(node_t *p,ofstream &asmFile );
void writeMtoAsm(node_t *p,ofstream &asmFile );
void writeTtoAsm(node_t *p,ofstream &asmFile );
void writeAtoAsm(node_t *p,ofstream &asmFile );
void writeAprimetoAsm(node_t *p, ofstream &asmFile);
void writeMprimetoAsm(node_t *p, ofstream &asmFile);
void writeHtoAsm(node_t *p, ofstream &asmFile);
void writeRtoAsm(node_t *p, ofstream &asmFile);
void writeItoAsm(node_t *p, ofstream &asmFile);
void writeGtoAsm(node_t *p, ofstream &asmFile);
void writeEtoAsm(node_t *p, ofstream &asmFile);
void writeWtoAsm(node_t *p, ofstream &asmFile);
void writeZtoAsm(node_t *p, ofstream &asmFile);
string getBranchName();
string getTempName();
string getInBranchName();

#endif
