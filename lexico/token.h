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
    NUMBER,//9
    DOUBLE_LITERAL,//10
    FLOAT_LITERAL,//11
    INTEGER_LITERAL,//12
    END_OF_FILE,//13
    
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