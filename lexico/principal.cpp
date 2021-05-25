#include "parser.h"


int main(int argc, char* argv[]) 
{
    string* vetNomes;

    vetNomes = new string[300];

    vetNomes[0] = " UNDEF";
    vetNomes[1] = " ID";
    vetNomes[2] = " ARITHOP";
    vetNomes[3] = "PLUS";
    vetNomes[4] = "MINUS";
    vetNomes[5] = "MULT";
    vetNomes[6] = "DIV";
    vetNomes[7] = " LPAREN";
    vetNomes[8] = " RPAREN";
    vetNomes[9] = " LCOL";
    vetNomes[10] = "RCOL";
    vetNomes[11] = "LCHAVES";
    vetNomes[12] = "RCHAVES";
    vetNomes[13] = "S_COMENTARIO";
    vetNomes[14] = "STRING_LITERAL";
    string input;
    
    getline(cin, input);

    Parser* parser = new Parser(&input);

    parser->run();


    delete parser;

    Scanner* scanner = new Scanner(&input);
    
    Token* t;
    
    do
    {
        t = scanner->nextToken();
        
        cout << vetNomes[t->name] << " ";
        if (t->attribute)
            cout << "(" << vetNomes[t->attribute] << ")";
    }while (t->name != END_OF_FILE);
    cout << endl;

    //delete scanner;*/

    return 0;
}