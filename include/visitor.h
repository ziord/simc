#ifndef VISITOR_H
#define VISITOR_H
#include "ast.h"
#include "stack.h"
#include "utils.h"

#define visitNumber(obj) (visitNumber_float(obj))
#define visit(ast) dispatch_visit_(ast)

void dispatch_visit_(AST* root);
void visitUnary(UnaryOp* uop);
void visitBinary(BinaryOp* bop);
void visitNumber_float(Number* num);

#define mvisit(ast) dispatch_mvisit_(ast)

void dispatch_mvisit_(AST* root);
void mvisitUnary(UnaryOp* uop);

void mvisitBinary(BinaryOp* bop);
void mvisitNumber(Number* num);

#endif // !VISITOR_H
