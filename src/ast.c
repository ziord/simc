#include "../include/ast.h"
void initASTTable(ASTTable* table) { table->tstack = (ASTTable*)malloc(ASTTREE_MAX);
    table->tstackTop = table->tstack; table->tcount = 0; }

void freeASTTable(ASTTable* table) {
    free(table->tstack);
    table->tstack = NULL;
    table->tstackTop = NULL;
    table->tcount = 0;
}

void pushNode(AST node) {
    *ast.tstackTop = node;
    ast.tstackTop++;
    ast.tcount++;
};
AST popNode() {  ast.tstackTop--; return *ast.tstackTop; }