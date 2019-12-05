#include "../include/stack.h"


void initMVM(MVM* mvm) {
	mvm->stackTop = mvm->stack;
}

void push(Value val) {
	*mv.stackTop = val;
	mv.stackTop++;
}

Value pop(void) {
	mv.stackTop--;
	return *mv.stackTop;
}
