#include "lexer.h"

Token makeToken(TokenType type) {
	Token tok;
	tok.line = lexer.line;
	tok.start = lexer.start;
	tok.length = (int)(lexer.current - lexer.start);
	tok.type = type;
	return tok;
}
void initLexer(char* src) {
	lexer.start = src;
	lexer.current = src;
	lexer.line = 1;
}

const char advance() {
	lexer.current++;
	return *(lexer.current - 1);
}

bool isAtEnd() {
	return lexer.current == '\0';
}
bool isDigit(char ch) {
	if ('0' <= ch && ch <= '9') {
		return true;
	}
	return false;
}

char peek() {
	return *lexer.current;
}

char peekNext() {
	return *(lexer.current + 1);
}
Token number() {
	while (!isAtEnd() && isDigit(*lexer.current))  {
		advance();
	}
	char ch = peekNext();
	if (peek() == '.' && (ch == ' ' || isDigit(ch))) {
		advance();
		while (!isAtEnd() && isDigit(*lexer.current)) {
			advance();
		}
	}
	return makeToken(NUMBER);
}

Token errorToken(const char* msg) {
	Token tok;
	tok.start = msg;
	tok.line = lexer.line;
	tok.type = ERROR;
	tok.length = strlen(msg);
	return tok;
}

bool match(char ch) {
	if (isAtEnd()) return false;
	if (lexer.current != ch) return false;
	advance();
	return true;
}
void skipWhitespace() {
	for (;;) {
		switch (*lexer.current) {
		case ' ':
		case '\t':
		case '\r':
			advance();
			break;
		case '\n': lexer.line++; advance(); break;
		default: return;
		}
	}
}
Token getToken() {
	skipWhitespace();
	lexer.start = lexer.current;
	if (isDigit(*lexer.current)) return number();
	char ch = advance();
	switch (ch) {
	case '+': return makeToken(PLUS);
	case '-': return makeToken(MINUS);
	case '/': return makeToken(DIV);
	case '*': return makeToken(MULT);
	case '%': return makeToken(MOD);
	case '(': return makeToken(LPAREN);
	case ')': return makeToken(RPAREN);
	//case '\0': return makeToken(EOF);
	default: return makeToken(T_EOF);
	}
}