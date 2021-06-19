#include "token.h"
#include <fstream>

class Scanner 
{
    private: 
        string input;//Armazena o texto de entrada
        int pos;//Posição atual
        int line;
        bool FlagErro;
    
    public:
    //Construtor
        Scanner(string);
        int getLine();
        bool getFlagErro();
    
        //Método que retorna o próximo token da entrada
        Token* nextToken();        
    
        //Método para manipular erros
        void lexicalError(string);
        ;
};
