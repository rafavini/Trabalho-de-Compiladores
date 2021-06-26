#include "scanner.h"

class Parser
{
	private:
		Scanner* scanner;
		Token* lToken;
		int linha;
		

		void advance();
		void match(int);
		void program();
		void classList();
		void classDecl();
		void classBody();
		void varDeclListOpt();
		void varDeclList();
		void varDecl();
		void varDeclOpt();
		bool isType(Token*);
		void type();
		void constructDeclListOpt();
		void constructDeclList();
		void constructDecl();
		void methodDeclListOpt();
		void methodDeclList();
		void methodDecl();
		void methodBody();
		void paramListOpt();
		void paramList();
		void param();
		void statementsOpt();
		void statements();
		void statement();
		void atribstat();
		void printstat();
		void readstat();
		void returnstat();
		void superstat();
		void ifstat();
		void forstat();
		void atribstatOpt();
		void expressionOpt();
		void Lvalue();
		void LvalueComp();
		void expression();
		void allocExpression();
		void numExpression();
		void term();
		void UnaryExpression();
		void factor();
		void argListOpt();
		void argList();
		//void goal();
		//void expr();
		//void exprLinha();
		//void term();
		//void termLinha();
		//void factor();
		void error(string);

	public:
		Parser(string);
		void run();
};