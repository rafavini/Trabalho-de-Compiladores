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
    MENOR,//7
    MAIOR,//8
    MENOR_IGUAL,//9
    MAIOR_IGUAL,//10
    MOD,//11
    RECEBE,//12
    IGUAL,//13
    DIFERENTE,//14 
    LPAREN,//15
    RPAREN,//16
    LCOL,//17
    RCOL,//18
    LCHAVES,//19
    RCHAVES,//20
    NUMBER,//21
    STRING_LITERAL,//22
    COMENTARIO,//23
    PONTO_VIRGULA,//24
    PONTO,//25
    VIRGULA,//26
    DOUBLE_LITERAL,//27
    FLOAT_LITERAL,//28
    INTEGER_LITERAL,//29
    CLASS,//30
    EXTENDS,//31
    CONSTRUCTOR,//32
    FOR,//33
    READ,//34
    SUPER,//35
    BREAK,//36
    NEW,//37
    INT,//38
    IF,//39
    ELSE,//40
    PRINT,//41
    RETURN,//42
    STRING,//43
    END_OF_FILE,//44
   
    
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