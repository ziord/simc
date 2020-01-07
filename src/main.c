#include "../include/lexer.h"
#include "../include/pp.h"
#include "../include/visitor.h"

#define PRINT_EXPR_TRACE


void parse();
void printExpr();

int main() {
	parse();
	return 0;
}

void printExpr() {
#ifdef PRINT_EXPR_TRACE
	int line = 0;
	for (;;) {
		Token tok = getToken();
		if (line == tok.line) {
			printf("|	");
		}
		else {
			printf("%d	", tok.line);
			line = tok.line;
		}
		printf("'%.*s'	%d\n", tok.length, tok.start, tok.type);
		if (tok.type == T_EOF)
			break;
	}

	printf("\n");
#endif
}

void parse() {
	for (;;) {
		printf(">>> ");
		char src[0xff];
		int ret = fgets(src, 0xff, stdin);
		if (!ret) {
			int c;
			while ((c = getchar()) != '\n')
				;
			//getchar();
			fprintf(stdout, "\n");
			continue;
		}
		if (src[0] == '\n')
			continue;
		else if (strcmp(src, "exit\n") == 0)
			break;
		initLexer(src);
		printExpr();
		initMVM(&mv);
		initLexer(src);
		initASTTable(&ast);
		adv();
		expression();
		AST node = popNode();
		if (parser.hadError) {
			mvisit(&node);
			parser.hadError = false;
			continue;
		}
		visit(&node);
		printf("%g\n", pop());
		mvisit(&node);
		freeASTTable(&ast);
	}
}