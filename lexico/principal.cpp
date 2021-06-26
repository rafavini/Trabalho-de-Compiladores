#include "parser.h"
#include<fstream>
#include<ostream>

#include<iostream>

int main(int argc, char* argv[]) 
{
    string* vetNomes;
    

    vetNomes = new string[500];

    vetNomes[0] = " UNDEF";
    vetNomes[1] = " ID";
    vetNomes[2] = " ARITHOP";
    vetNomes[3] = "PLUS";
    vetNomes[4] = "MINUS";
    vetNomes[5] = "MULT";
    vetNomes[6] = "DIV";
    vetNomes[7] = "MENOR";
    vetNomes[8] = "MAIOR";
    vetNomes[9] = "MENOR_IGUAL";
    vetNomes[10] = "MAIOR_IGUAL";
    vetNomes[11] = "MOD";
    vetNomes[12] = "RECEBE";
    vetNomes[13] = "IGUAL";
    vetNomes[14] = "DIFERENTE";
    vetNomes[15] = " LPAREN";
    vetNomes[16] = " RPAREN";
    vetNomes[17] = " LCOL";
    vetNomes[18] = "RCOL";
    vetNomes[19] = "LCHAVES";
    vetNomes[20] = "RCHAVES";
    vetNomes[21] = "NUMBER";
    vetNomes[22] = "STRING_LITERAL";
    vetNomes[23] = "COMENTARIO";
    vetNomes[24] = "PONTO_VIRGULA";
    vetNomes[25] = "PONTO";
    vetNomes[26] = "VIRGULA";
    vetNomes[27] = "DOUBLE_LITERAL";
    vetNomes[28] = "FLOAT_LITERAL";
    vetNomes[29] = "INTEGER_LITERAL";
    vetNomes[30] = "CLASS";
    vetNomes[31] = "EXTENDS";
    vetNomes[32] = "CONSTRUCTOR";
    vetNomes[33] = "FOR";
    vetNomes[34] = "READ";
    vetNomes[35] = "SUPER";
    vetNomes[36] = "BREAK";
    vetNomes[37] = "NEW";
    vetNomes[38] = "INT";
    vetNomes[39] = "IF";
    vetNomes[40] = "ELSE";
    vetNomes[41] = "PRINT";
    vetNomes[42] = "RETURN";
    vetNomes[43] = "STRING";
    vetNomes[44] = "END_OF_FILE";
    
    //string input;
    
    //getline(cin, input);

    Parser* parser = new Parser(argv[1]);

    parser->run();

    delete parser;



   Scanner* scanner = new Scanner(argv[1]);
    
    Token* t;
    
    do
    {
        t = scanner->nextToken();
        
        cout << vetNomes[t->name] << " ";
        if (t->attribute)
            cout << "(" << vetNomes[t->attribute] << ")";
    }while (t->name != END_OF_FILE);
    cout << endl;
    

    delete scanner;


     

    return 0;
}