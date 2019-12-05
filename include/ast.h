#ifndef AST_H
#define AST_H
#include "lexer.h"
#include "stack.h"
#define ASTTREE_MAX 256

struct UnaryOp;
struct BinaryOp;
struct Number;

typedef enum {
	T_UNARY,
	T_BINARY,
	T_NUMBER,
	T_INT,
	T_FLOAT
}Type;
typedef TokenType Op;

#define AS_UNARY(obj)		(obj).as.unary
#define IS_UNARY(obj)		(obj).type == T_UNARY

#define AS_BINARY(obj)		(obj).as.binary
#define IS_BINARY(obj)		(obj).type == T_BINARY

#define AS_NUMBER(obj)		(obj).as.number
#define IS_NUMBER(obj)		(obj).type == T_NUMBER

#define NUM_NODE(obj)		(AST){.type=T_NUMBER, {.number=obj}} //AST form for num
#define UNARY_NODE(obj)		(AST){.type=T_UNARY, {.unary=obj}}   //ditto
#define BINARY_NODE(obj)	(AST){.type=T_BINARY, {.binary=obj}}

#define IS_INT(obj)			(obj).type == T_INT
#define IS_FLOAT(obj)		(obj).type == T_FLOAT

#define AS_INT(obj)			(obj).as.integer
#define AS_FLOAT(obj)		(obj).as.float_

typedef struct {
	Type type;
	union {
		struct UnaryOp* unary;
		struct BinaryOp* binary;
		struct Number* number;
	}as;
}AST;

typedef struct {
	AST* node;
	Op op;
}UnaryOp;

typedef struct {
	Type type;
	union {
		int integer;
		double float_;
	}as;
}Number;

typedef struct {
	AST* lnode;
	Op op;
	AST* rnode;
}BinaryOp;

typedef struct {
	AST* tstack;
	AST* tstackTop;
	int tcount;
}ASTTable;

ASTTable ast;
void initASTTable(ASTTable* table);
void freeASTTable(ASTTable* table);
void freeASTTable(ASTTable* table);
void pushNode(AST node);
AST popNode();


#endif