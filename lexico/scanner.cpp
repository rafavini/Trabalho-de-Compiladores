#include "scanner.h"    

//Construtor
Scanner::Scanner(string input)
{
   /* this->input = input;
    cout << "Entrada: " << (*input) << endl << "Tamanho: " 
         << input->length() << endl; */
    pos = 0;
    linha = 1;
    ifstream inputFile(input, ios::in);
    string line;

    if(inputFile.is_open()){
        while(getline(inputFile,line) ){
            this->input.append(line + '\n');
        }
        inputFile.close();
    }
    else
        cout << "unable to open file \n";
    
    cout << this->input;
}
int
Scanner::getLine(){
    return linha;
}

//Método que retorna o próximo token da entrada
Token* 
Scanner::nextToken()
{
    Token* tok;



    //Consumir espaços em branco
    while (isspace(input[pos])){
        pos++;

        if(input[pos] == '\n')
            linha++;
    }

    //Verificar os tokens possíveis
    //Fim de arquivo
    if (input[pos] == '\0')
    {
        tok = new Token(END_OF_FILE);
    }
    //Operadores aritmeticos
    
    
   else if (input[pos] == '+')//+
   {
        pos++;
        tok = new Token(ARITHOP, PLUS);
   }
   else if (input[pos] == '-')//-
   {
        pos++;
        tok = new Token(ARITHOP, MINUS);
   }
   else if (input[pos] == '*')//*
   {
        pos++;
        tok = new Token(ARITHOP, MULT);
   }
   else if (input[pos] == '<')
   {
    pos++;
        if(input[pos] == '=')
        {
            pos++;
            tok = new Token(ARITHOP,MENOR_IGUAL);
        }else
        {
            tok = new Token(ARITHOP,MENOR);
        }
    
   }
    else if (input[pos] == '>')
   {
    pos++;
        if(input[pos] == '=')
        {
            pos++;
            tok = new Token(ARITHOP,MAIOR_IGUAL);
        }else
        {
           tok = new Token(ARITHOP,MAIOR); 
        }
    
   }
   else if(input[pos] == '%')
   {
    pos++;
    tok = new Token(ARITHOP,MOD);
   }
   else if (input[pos] == '=')
   {
    pos++;
    if(input[pos] == '=')
    {
        pos++;
        tok = new Token(ARITHOP,IGUAL);
    }else
    {
        tok = new Token(ARITHOP,RECEBE);
    }
   }   
   else if (input[pos] == '!')
   {
    pos++;
    if(input[pos] == '=')
    {
        pos++;
        
        tok = new Token(ARITHOP,DIFERENTE);
    }
   }
   else if (input[pos] == '/')
   {
        pos++;
        if(input[pos] == '/')
        {
            pos++;
            while(isalpha((input)[pos]) || isalnum((input)[pos])|| isspace((input)[pos]))
                pos++;

            if(input[pos] == '\n'){
                linha++;
            }
                
          
             tok = new Token(COMENTARIO);
            
        }else if(input[pos] =='*')
        {
            pos++;
            while(isalpha(input[pos]) || isalnum(input[pos])|| isspace(input[pos]))
                pos++;
            if(input[pos] == '*')
            {
                pos++;
                if(input[pos] == '/')
                {
                    pos++;
                    tok = new Token(COMENTARIO);
                }
            }
        }else
        {
            tok = new Token(ARITHOP,DIV);
        }
   }
   else if (input[pos] == '(')
   {
        pos++;
        if(input[pos] == '\n'){
                linha++;
            }
        tok = new Token(LPAREN);
   }
   else if (input[pos] == ')')
   {
        pos++;
        if(input[pos] == '\n'){
                linha++;
            }
        tok = new Token(RPAREN);
   }
    else if (input[pos] == '[')
   {
        pos++;
        if(input[pos] == '\n'){
                linha++;
            }
        tok = new Token(LCOL);
   }
   else if (input[pos] == ']')
   {
        pos++;
        if(input[pos] == '\n'){
                linha++;
            }
        tok = new Token(RCOL);
   }
    else if (input[pos] == '{')
   {
        pos++;
        if(input[pos] == '\n'){
                linha++;
            }
        tok = new Token(LCHAVES);
   }
   else if (input[pos] == '}')
   {
        pos++;
        if(input[pos] == '\n'){
                linha++;
            }
        tok = new Token(RCHAVES);
   }
   else if (input[pos] == '.')
   {
        pos++;
        if(input[pos] == '\n'){
                linha++;
            }
        tok = new Token(PONTO);
   }
    else if (input[pos] == ',')
   {
        pos++;
        if(input[pos] == '\n'){
                linha++;
            }
        tok = new Token(VIRGULA);
   }
   else if (input[pos] == ';')
   {
        pos++;
        if(input[pos] == '\n'){
                linha++;
            }
        tok = new Token(PONTO_VIRGULA);
   }
   

   //STRING LITERAL
   else if (input[pos] == '"')
   {
        pos++;
        while(isalpha(input[pos]) || isalnum(input[pos])|| isspace(input[pos]))
            pos++; 
        if(input[pos] == '"')
        {
            pos++;
            tok = new Token(STRING_LITERAL);
        }
   }

   
    //Identificadores
    else if (isalpha(input[pos]) || input[pos] == '_')
    {
        pos++;
        while (isalnum(input[pos]))
            pos++;

        if(input[pos] == '\n'){
                linha++;
            }
        //Pesquisar na tabela de palavras reservadas
        //caso encontrem, retornem o token adequado,i
        //caso contrário, é ID
        tok = new Token(ID);
    }
    //Números
    else if (isdigit(input[pos]))
    {
        pos++;
        while (isdigit(input[pos]))
            pos++;

        bool isFloat = false;

        if (input[pos] == '.')
        {
            pos++;

            if (isdigit(input[pos]))
            {
                pos++;
                while (isdigit(input[pos]))
                    pos++;
            }
            else
                lexicalError("Token mal formado");

            isFloat = true;
        }

        bool isDouble = false;
        if (input[pos] == 'E')
        {
            pos++;

            if (input[pos] == '+' || input[pos] == '-')
                pos++;

            if (isdigit(input[pos]))
            {
                pos++;
                while (isdigit(input[pos]))
                    pos++;
                
                if(input[pos] == '\n'){
                linha++;
            }
            }
            else
                lexicalError("Token mal formado");

            isDouble = true;
        }

        if (isDouble)
            tok = new Token(NUMBER, DOUBLE_LITERAL);
        else if (isFloat)
            tok = new Token(NUMBER, FLOAT_LITERAL);
        else
            tok = new Token(NUMBER, INTEGER_LITERAL);

    }
    else
        lexicalError("Token mal formado");

    return tok;
    
}

void 
Scanner::lexicalError(string msg)
{
    cout << "Linha: " << linha << ": " << msg << endl;
    
    exit(EXIT_FAILURE);
}
