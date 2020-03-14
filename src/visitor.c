#include "visitor.h"
#include "utils.h"
//#define PRINT_FREE_TRACE

void dispatch_visit_(AST* root) {
	switch (root->type) {
	case T_BINARY: visitBinary(AS_BINARY(*root)); break;
	case T_UNARY: visitUnary(AS_UNARY(*root)); break;
	case T_NUMBER: visitNumber_float(AS_NUMBER(*root)); break;//visitNumber(AS_NUMBER(*root)); break;
	default: break; 
	}
}

void visitUnary(UnaryOp* uop) {
	visit(uop->node);
	switch (uop->op) {
	case PLUS: {
		Value v = pop();
		push(v);
		break;
	}
	case MINUS: {
		Value v = pop();
		push(-v);
		break;
	}
	}
}

void visitBinary(BinaryOp* bop) {
#define BIN_OP(vType, op) \
						do { \
							Value b = pop(); \
							Value a = pop();  \
							push((vType)(a op b));   \
						}while(false)
	visit(bop->lnode);
	visit(bop->rnode);
	switch (bop->op) {
	case PLUS: {
		BIN_OP(Value, +); 
		break;
	}
	case MINUS: {
		BIN_OP(Value, - );
		break;
	}
	case DIV: {
		BIN_OP(Value, / );
		break;
	}
	case MULT: {
		BIN_OP(Value, * );
		break;
	}
	case MOD: {
		Value b = pop(); 
		Value a = pop();  
		push((int)a % (int)b);
		break;
	}
	}
#undef BIN_OP
}

void visitNumber_float(Number* num) {
	push(AS_FLOAT(*num));
}


void dispatch_mvisit_(AST* root) {
	switch (root->type) {
	case T_BINARY: mvisitBinary(AS_BINARY(*root)); break;
	case T_UNARY: mvisitUnary(AS_UNARY(*root)); break;
	case T_NUMBER: mvisitNumber(AS_NUMBER(*root)); break;
	default: break;
	}
}
void mvisitUnary(UnaryOp* uop) {
	mvisit(uop->node);
#ifdef PRINT_FREE_TRACE
	printf("freeing UnaryOp\n");
#endif
	FREE(UnaryOp, uop);
}

void mvisitBinary(BinaryOp* bop) {
	mvisit(bop->lnode);
	mvisit(bop->rnode);
#ifdef PRINT_FREE_TRACE
	printf("freeing BinaryOp\n");
#endif
	FREE(BinaryOp, bop);
}
void mvisitNumber(Number* num) {
#ifdef PRINT_FREE_TRACE
	printf("freeing Number\n");
#endif
	FREE(Number, num);
}
//void mvisitNumber_int(Number* num);
