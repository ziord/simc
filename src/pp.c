#include "../include/visitor.h"
#include "../include/pp.h"
#include "../include/ast.h"
void binary();
void unary();
void number_();
void grouping();
void parsePrec(Precedence);


ParseRule* getRule(TokenType t);


ParseRule rule[] = {
	{unary, binary, PREC_EXPR},  //plus
	{unary, binary, PREC_EXPR},  //minus
	{NULL, binary, PREC_TERM},   //div
	{NULL, binary, PREC_TERM},   //mult
	{NULL, binary, PREC_FACTOR}, //mod
	{number_, NULL, PREC_NONE},  //number
	{grouping, NULL, PREC_NONE},  //lparen
	{NULL, NULL, PREC_NONE},   //rparen
	{NULL, NULL, PREC_NONE},  //error
	{NULL, NULL, PREC_NONE},   //t_eof
};

ParseRule* getRule(TokenType t) {
	return &rule[t];
}
void adv() {
	parser.previous = parser.current;
	for (;;) {
		Token tok = getToken();
		parser.current = tok;
		//if (tok.type != T_EOF) break;
		return;
	}
}

void error(Token* tok, const char* err) {
	if (parser.hadError) synch();
	parser.hadError = true;
	fprintf(stderr, "%s [line %d] -> %s", err, 
		tok->line, tok->start);
}

bool match_tok(TokenType type) {
	if (parser.current.type != type) return false;
	adv();
	return true;
}

void consume(TokenType type, const char* msg) {
	if (!match_tok(type))
		error(&parser.current, msg);
}


void parsePrec(Precedence prec) {
	adv();
	ParseRule* prefix_rule = getRule(parser.previous.type);
	ParseFn prefix = prefix_rule->prefix;
	if (prefix == NULL) {
		error(&parser.previous, "Invalid Token");
		synch();
		return;
	}
	
	prefix();
	while (prec <= getRule(parser.current.type)->precedence) {
		adv();
		ParseRule* infix_rule = getRule(parser.previous.type);
		ParseFn infix = infix_rule->infix;
		infix();
	}
}

void binary() {
#define BINOP(o)	\
				do{ \
					AST* b = ALLOC(AST); \
					*b = popNode();   \
					AST* a = ALLOC(AST);  \
					*a = popNode();  \
					bop->op = o;   \
					bop->lnode = a;  \
					bop->rnode = b;  \
					pushNode(BINARY_NODE(bop));  \
				}while(0);

	TokenType type = parser.previous.type;
	ParseRule* rule = getRule(type);
	parsePrec((Precedence)(rule->precedence + 1));
	BinaryOp* bop = ALLOC(BinaryOp);
	switch (type) {
	case PLUS: {
		BINOP(PLUS); break;
	}
	case MINUS: BINOP(MINUS); break;
	case MOD: BINOP(MOD); break;
	case MULT: BINOP(MULT); break;
	case DIV: BINOP(DIV); break;
	}
#undef BINOP
}
void unary() {
	TokenType operatorType = parser.previous.type;
	ParseRule* rule = getRule(operatorType);
	parsePrec(PREC_FACTOR);
	UnaryOp* uop = ALLOC(UnaryOp);
	switch (operatorType) {
	case PLUS: {
		AST* node = ALLOC(AST);
		*node = popNode();
		uop->node = node;
		uop->op = PLUS;
		pushNode(UNARY_NODE(uop));
		break;
	}
	case MINUS: {
		AST* node = ALLOC(AST);
		*node = popNode();
		uop->node = node;
		uop->op = MINUS;
		pushNode(UNARY_NODE(uop));
		break;
	}
	}
}

void number_() {
	Value val = strtod(parser.previous.start, NULL);
	Number* node = ALLOC(Number);
	node->type = T_FLOAT;
	node->as.float_ = val;
	pushNode(NUM_NODE(node));
	}

void expression() {
	parsePrec(PREC_EXPR);
}

void grouping() {
	expression();
	consume(RPAREN, "Expected ')' at end of expression");
}

void synch() {
	if (parser.hadError)
		while (peek() != '\n') {
			getToken();
		}
}