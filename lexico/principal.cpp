#include "parser.h"


int main(int argc, char* argv[]) 
{
    string* vetNomes;

    vetNomes = new string[17];

    vetNomes[0] = " UNDEF";
    vetNomes[1] = " ID";
    vetNomes[2] = " ARITHOP";
    vetNomes[3] = "PLUS";
    vetNomes[4] = "MINUS";
    vetNomes[5] = "MULT";
    vetNomes[6] = "DIV";
    vetNomes[7] = " LPAREN";
    vetNomes[8] = " RPAREN";
    vetNomes[9] = " NUMBER";
    vetNomes[10] = "DOUBLE_LITERAL";
    vetNomes[11] = "FLOAT_LITERAL";
    vetNomes[12] = "INTEGER_LITERAL";
    vetNomes[13] = "END_OF_FILE";
    string input;
    
    getline(cin, input);

    Parser* parser = new Parser(&input);

    parser->run();


    delete parser;

    /*Scanner* scanner = new Scanner(&input);
    
    Token* t;
    
    do
    {
        t = scanner->nextToken();
        
        cout << vetNomes[t->name] << " ";
        if (t->attribute)
            cout << "(" << vetNomes[t->attribute] << ")";
    }while (t->name != END_OF_FILE);
    cout << endl;

    delete scanner;*/

    return 0;
}