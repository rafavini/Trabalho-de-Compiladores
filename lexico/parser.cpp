#include "parser.h"

Parser::Parser(string input)
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
		error("Erro inesperado");
}

void
Parser::run()
{
	advance();

	program();

	cout << "Compilação encerrada com sucesso!\n";
}

/*void 
Parser::goal()
{
	expr();
}*/

/*void 
Parser::expr()
{
	term();
	exprLinha();
}*/

/*void
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
	else if (lToken->attribute == MENOR)
	{
		advance();
		term();
		exprLinha();
	}
	else if (lToken->attribute == MENOR_IGUAL)
	{
		advance();
		term();
		exprLinha();
	}

	else if (lToken->attribute == MAIOR)
	{
		advance();
		term();
		exprLinha();
	}
	else if (lToken->attribute == MAIOR_IGUAL)
	{
		advance();
		term();
		exprLinha();
	}


	//else
	//	;

}*/

/*void
Parser::term()
{
	factor();
	termLinha();
}*/

/*void
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
	else if (lToken->attribute == MOD)
	{
		advance();
		factor();
		termLinha();
	}
	else if (lToken->attribute == RECEBE)
	{
		advance();
		factor();
		termLinha();
	}
	else if (lToken->attribute == IGUAL)
	{
		advance();
		factor();
		termLinha();
	}
	else if (lToken->attribute == DIFERENTE)
	{
		advance();
		factor();
		termLinha();
	}
	
}*/


/*void 
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
	else if (lToken->name == COMENTARIO)
	{
		advance();
	}
	else if (lToken->name == PONTO_VIRGULA)
	{
		advance();
	}
	else if (lToken->name == PONTO)
	{
		advance();
	}
	else if (lToken->name == VIRGULA)
	{
		advance();
	}
	else
		error("Erro inesperado");
}*/


//GRAMATICA
void
Parser::program(){
	if (lToken->name == CLASS)
		classList();
}

void
Parser::classList(){
	do{
		classDecl();
	}
	while(lToken->name == CLASS);
}

void
Parser::classDecl(){
	match(CLASS);
	match(ID);

	if(lToken->name == EXTENDS){
		advance();
		match(ID);
	}

	classBody();
}

void
Parser::classBody(){
	match(LCHAVES);
	varDeclListOpt();
	constructDeclListOpt();
	match(RCHAVES);
}

void
Parser::varDeclListOpt(){
	if(isType(lToken)){
		varDeclList();
	}
}

void
Parser::varDeclList(){
	do{
		varDecl();
 	}while(isType(lToken));
}

void
Parser::varDecl(){
	type();

	if(lToken->name == LCOL){
		advance();
		match(RCOL);
	}
	match(ID);
	varDeclOpt();
	match(PONTO_VIRGULA);
}

void
Parser::varDeclOpt(){
	while(lToken->name == VIRGULA){
		advance();
		match(ID);
	}
}

void
Parser::type(){
	if(isType(lToken))
		advance();
	else
		error("Tipo esperado");
}

void
Parser::constructDeclListOpt(){
	if(lToken->name == CONSTRUCTOR)
		constructDeclList();
}

void
Parser::constructDeclList(){
	do{
		constructDecl();
	}while(lToken->name == CONSTRUCTOR);
}

void
Parser::constructDecl(){
	match(CONSTRUCTOR);
	methodBody();
}

void
Parser::methodDeclListOpt(){
	if(isType(lToken))
		methodDeclList();
}

void
Parser::methodDeclList(){
	do{
		methodDecl();
	}while(isType(lToken));
}

void
Parser::methodDecl(){
	type();

	if(lToken->name == LCOL){
		advance();
		match(RCOL);
	}
	match(ID);
	methodBody();
	match(PONTO_VIRGULA);
}

void
Parser::methodBody(){
	match(LPAREN);
	paramListOpt();
	match(RPAREN);
	match(LCHAVES);
	statementsOpt();
	match(RCHAVES);
	UnaryExpression();
}

void
Parser::paramListOpt(){
	if(isType(lToken)){
		paramList();
	}
}

void
Parser::paramList(){
	param();
	while(lToken->name == VIRGULA){
		advance();
		param();
	}
}

void
Parser::param(){
	type();

	if(lToken->name == LCOL){
		advance();
		match(RCOL);
	}
	match(ID);
}

void
Parser::statementsOpt(){
	if(isType(lToken)|| lToken->name == PRINT || lToken->name == READ || lToken->name == RETURN || lToken->name == SUPER || lToken->name == IF || lToken->name == FOR || lToken->name == BREAK || lToken->name ==  PONTO_VIRGULA){
		statements();
	}
}

void
Parser::statements(){
	do{
		statement();	
	}while(isType(lToken)|| lToken->name == PRINT || lToken->name == READ || lToken->name == RETURN || lToken->name == SUPER || lToken->name == IF || lToken->name == FOR || lToken->name == BREAK || lToken->name ==  PONTO_VIRGULA);
}

void
Parser::statement(){
	if(isType(lToken)){
		varDeclList();
	}else if(lToken->name == ID){
		atribstat();
		match(PONTO_VIRGULA);
	}else if(lToken->name == PRINT){
		printstat();
		match(PONTO_VIRGULA);
	}else if(lToken->name == READ){
		readstat();
		match(PONTO_VIRGULA);
	}else if(lToken->name == RETURN){
		returnstat();
		match(PONTO_VIRGULA);
	}else if(lToken->name == SUPER){
		superstat();
		match(PONTO_VIRGULA);
	}else if(lToken->name == IF){
		ifstat();
	}else if(lToken->name == FOR){
		forstat();
	}else if(lToken->name == BREAK){
		advance();
		match(PONTO_VIRGULA);
	}else if(lToken->name == PONTO_VIRGULA){
		advance();
	}else{
		error("erro do statements");
	}
}

void
Parser::atribstat(){
	Lvalue();
	match(IGUAL);
	if(lToken->name == PLUS || lToken->name == MINUS){
		expression();
	}else if(lToken->name == NEW){
		allocExpression();
	}
}

void
Parser::printstat(){
	match(PRINT);
	expression();
}

void
Parser::readstat(){
	match(READ);
	Lvalue();
}

void
Parser::returnstat(){
	match(RETURN);
	expression();
}

void
Parser::superstat(){
	match(SUPER);
	match(LPAREN);
	argListOpt();
	match(RPAREN);
}

void
Parser::ifstat(){
	match(IF);
	match(LPAREN);
	expression();
	match(RPAREN);
	match(LCHAVES);
	statements();
	match(RCHAVES);
	if(lToken->name == ELSE){
		advance();
		match(LCHAVES);
		statements();
		match(RCHAVES);
	}
}

void
Parser::forstat(){
	match(FOR);
	match(LPAREN);
	atribstatOpt();
	match(PONTO_VIRGULA);
	expressionOpt();
	match(PONTO_VIRGULA);
	atribstatOpt();
	match(RPAREN);
	match(LCHAVES);
	statements();
	match(RCHAVES);
}

void
Parser::atribstatOpt(){
	if(lToken->name == ID){
		atribstat();
	}
}

void
Parser::expressionOpt(){
	if(lToken->name == PLUS || lToken->name == MINUS){
		expression();
	}
}

void
Parser::Lvalue(){
	match(ID);
	if(lToken->name == LCOL){
		advance();
		expression();
		match(RCOL);
	}
	LvalueComp();
}

void
Parser::LvalueComp(){
	if(lToken->name == PONTO){
		advance();
		match(ID);
		if(lToken->name == LCOL){
			advance();
			expression();
		}
		LvalueComp();
	}
}

void
Parser::expression(){
	numExpression();
	if(lToken->name == ARITHOP){
		advance();
		numExpression();
	}
}

void
Parser::allocExpression(){
	if(isType(lToken)){
		type();
		match(LCOL);
		expression();
		match(RCOL);
	}else if(lToken->name == NEW){
		advance();
		match(ID);
		match(LPAREN);
		argListOpt();
		match(RPAREN);
	}
}

void
Parser::numExpression(){
	term();
	if(lToken->name == PLUS || lToken->name == MINUS){
		advance();
		term();
	}
}

void
Parser::term(){
	UnaryExpression();
	if(lToken->name == MULT || lToken->name == DIV || lToken->name == MOD){
		advance();
		UnaryExpression();
	}
}

void
Parser::UnaryExpression(){
	if(lToken->name == PLUS || lToken->name == MINUS){
		advance();
		factor();
	}
}

void
Parser::factor(){
	if(lToken->name == INTEGER_LITERAL){
		advance();
	}else if(lToken->name == STRING_LITERAL){
		advance();
	}else if(lToken->name == ID){
		Lvalue();
	}else if(lToken->name == LPAREN){
		advance();
		expression();
		match(RPAREN);
	}
}

void
Parser::argListOpt(){
	if(lToken->name == PLUS || lToken->name == MINUS){
		argList();
	}
}

void
Parser::argList(){
	expression();
	while(lToken->name == VIRGULA){
		advance();
		expression();
	}
}

bool
Parser::isType(Token* tok){
	if (tok->name == INT || tok->name == STRING || tok->name == ID){
		return true;
	}else{
		return false;
	}
}


void
Parser::error(string msg)
{
	
	linha = scanner->getLine();
	cout << "Linha: " << linha << ": " << msg << endl;
	exit(EXIT_FAILURE);
}
