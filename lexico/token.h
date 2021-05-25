#include <iostream>
#include <ctype.h>//Funções de caracteres
#include <string>

using namespace std;

enum Names 
{
    UNDEF,//0
    ID,//1
    ARITHOP,//2
    PLUS,//3
    MINUS,//4
    MULT,//5
    DIV,//6
    LPAREN,//7
    RPAREN,//8
    LCOL,//9
    RCOL,//10
    LCHAVES,//11
    RCHAVES,//12
    NUMBER,//13
    STRING_LITERAL,//14
    COMENTARIO,//15
    PONTO_VIRGULA,//16
    PONTO,//17
    VIRGULA,//18
    DOUBLE_LITERAL,//19
    FLOAT_LITERAL,//20
    INTEGER_LITERAL,//21
    END_OF_FILE,//22
    
};

class Token 
{
    public: 
        int name;
        int attribute;
        string* lexeme;
    
        Token(int name)
        {
            this->name = name;
            attribute = UNDEF;
        }
        
        Token(int name, int attr)
        {
            this->name = name;
            attribute = attr;
        }
};