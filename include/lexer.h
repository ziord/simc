#ifndef LEXER_H
#define LEXER_H
#include "utils.h"


typedef enum {
	PLUS,
	MINUS,
	DIV,
	MULT,
	MOD,
	NUMBER,
	LPAREN,
	RPAREN,
	ERROR,
	T_EOF
}TokenType;

typedef struct {
	int line;
	char* start;
	int length;
	TokenType type;
}Token;

typedef struct {
	char* start;
	char* current;
	int line;
}Lexer;

Lexer lexer;
void initLexer(char* src);
Token makeToken(TokenType);
const char advance();
bool match(char);
char peek();
char peekNext();
bool isAtEnd();
bool isDigit(char ch);
Token errorToken(const char* msg);
Token number();
Token getToken();
#endif // !LEXER_H
