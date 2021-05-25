#include "parser.h"

Parser::Parser(string* input)
{
	scanner = new Scanner(input);
}

void
Parser::advance()
{
	lToken = scanner->nextToken();
}

void
Parser::match(int t)
{
	if (lToken->name == t || lToken->attribute == t)
		advance();
	else
		error();
}

void
Parser::run()
{
	advance();

	goal();

	cout << "Compilação encerrada com sucesso!\n";
}

void 
Parser::goal()
{
	expr();
}

void 
Parser::expr()
{
	term();
	exprLinha();
}

void
Parser::exprLinha()
{
	if (lToken->attribute == PLUS)
	{
		advance();
		term();
		exprLinha();
	}
	else if (lToken->attribute == MINUS)
	{
		advance();
		term();
		exprLinha();
	}

	//else
	//	;

}

void
Parser::term()
{
	factor();
	termLinha();
}

void
Parser::termLinha()
{
	if (lToken->attribute == MULT)
	{
		advance();
		factor();
		termLinha();
	}
	else if (lToken->attribute == DIV)
	{
		advance();
		factor();
		termLinha();
	}
}

void 
Parser::factor()
{
	if (lToken->name == NUMBER)
	{
		//Trata número
		advance();
	}
	else if (lToken->name == ID)
	{
		//Trata identificador
		advance();
	}
	else if (lToken->name == LPAREN)
	{
		advance();
		expr();
		match(RPAREN);
	}
	else if (lToken->name == LCOL)
	{
		advance();
		expr();
		match(RCOL);
	}
	else if (lToken->name == LCHAVES)
	{
		advance();
		expr();
		match(RCHAVES);
	}
	else if (lToken->name == STRING_LITERAL)
	{
		advance();
	}
	else
		error();
}

void
Parser::error()
{
	cout << "Erro sintático\n";

	exit(EXIT_FAILURE);
}
