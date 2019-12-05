#ifndef PP_H
#define PP_H
#include "utils.h"
#include "lexer.h"
#include "ast.h"

typedef enum {
	PREC_NONE,
	PREC_EXPR,  //+, -
	PREC_TERM, //*, /
	PREC_SUP_TERM, //%
	PREC_FACTOR,// number, ( )
	PREC_PRIMARY
}Precedence;
typedef void (*ParseFn)();

typedef struct {
	Token previous;
	Token current;
	bool hadError;
	bool panicMode;
}PParser;

PParser parser;
typedef struct {
	ParseFn* prefix;
	ParseFn* infix;
	Precedence precedence;
}ParseRule;



void adv();
bool match_tok(TokenType);
void consume(TokenType, const char*);
void error(Token*, const char*);
void expression();
void synch();
#endif