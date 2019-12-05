#ifndef STACK_H
#define STACK_H
#define INIT_CAP 20
#include <stdlib.h>

typedef double Value;
#define ALLOC(type) (type*)(malloc(sizeof(type)));
#define FREE(type, obj)		free(obj);

typedef struct {
	Value stack[INIT_CAP];
	Value* stackTop;
}MVM;

MVM mv;
void initMVM(MVM* mvm);
void push(Value val);
Value pop(void);

#endif // !STACK_H
