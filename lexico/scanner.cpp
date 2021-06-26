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

   //palavras reservadas
   //CLASS
    else if (input[pos] == 'c' && input[pos+1] == 'l' && input[pos+2] == 'a' && input[pos+3] == 's' && input[pos+4] == 's' && isspace(input[pos+5])){
       pos = 5;
       tok = new Token(CLASS);
   }
    // INT
    else if (input[pos] == 'i' && input[pos+1] == 'n' && input[pos+2] == 't' && isspace(input[pos+3])){
        pos = pos + 3;
        tok = new Token(INT);
    }
    // IF
    else if ((input[pos] == 'i' && input[pos+1] == 'f') && (isspace(input[pos+2]) || input[pos+2] == '(')){
            pos = pos + 2;
            tok = new Token(IF);
    }
    // ELSE
    else if((input[pos] == 'e' && input[pos+1] == 'l' && input[pos+2] == 's' && input[pos+3] == 'e') && (isspace(input[pos+4]) || input[pos+4] == '(')){  
            pos = pos + 4;
            tok = new Token(ELSE);
    }
     // PRINT
    else if((input[pos] == 'p' && input[pos+1] == 'r' && input[pos+2] == 'i' && input[pos+3] == 'n' && input[pos+4] == 't') && (isspace(input[pos+5]) || input[pos+5] == '(')){
            pos = pos + 5;
            tok = new Token(PRINT);
    }
    //RETURN
    else if(input[pos] == 'r' && input[pos+1] == 'e' && input[pos+2] == 't' && input[pos+3] == 'u' && input[pos+4] == 'r' && input[pos+5] == 'n' && isspace(input[pos+6])){
        pos = pos + 6;
        tok = new Token(RETURN);
    }
      // STRING
    else if(input[pos] == 's' && input[pos+1] == 't' && input[pos+2] == 'r' && input[pos+3] == 'i' && input[pos+4] == 'n' && input[pos+5] == 'g' && isspace(input[pos+6])){
        pos = pos + 6;
        tok = new Token(STRING);
    }
    //EXTENDS
    else if (input[pos] == 'e' && input[pos+1] == 'x' && input[pos+2] == 't' && input[pos+3] == 'e' && input[pos+4] == 'n' && input[pos+5] == 'd' && input[pos+6] == 's' && isspace(input[pos+7])){
       pos =  pos + 7;
       tok = new Token(EXTENDS);
   }
   //CONSTRUCTOR
   else if (input[pos] == 'c' && input[pos+1] == 'o' && input[pos+2] == 'n' && input[pos+3] == 's' && input[pos+4] == 't' && input[pos+5] == 'r' && input[pos+6] == 'u' && input[pos+7] == 'c' && input[pos+8] == 't' && input[pos+9] == 'o' && input[pos+10] == 'r' && isspace(input[pos+11])){
       pos = pos + 11;
       tok = new Token(CONSTRUCTOR);
   }
   //FOR
   else if ((input[pos] == 'f' && input[pos+1] == 'o' && input[pos+2] == 'r') && (isspace(input[pos+3]) || input[pos+4] == '(')){
       pos = pos + 3;
       tok = new Token(FOR);
   }
   //READ
    else if ((input[pos] == 'r' && input[pos+1] == 'e' && input[pos+2] == 'a' && input[pos+3] == 'd') &&  (isspace(input[pos+4]) || input[pos+4] == '(')){
       pos = pos + 4;
       tok = new Token(READ);
   }
   //SUPER
     else if ((input[pos] == 's' && input[pos+1] == 'u' && input[pos+2] == 'p' && input[pos+3] == 'e' && input[pos+4] == 'r') &&  (isspace(input[pos+5]) || input[pos+5] == '(')){
       pos = pos + 5;
       tok = new Token(SUPER);
   }
   //BREAK
     else if ((input[pos] == 'b' && input[pos+1] == 'r' && input[pos+2] == 'e' && input[pos+3] == 'a' && input[pos+4] == 'k') &&  (isspace(input[pos+5]) || input[pos+5] == ';')){
       pos = pos + 5;
       tok = new Token(BREAK);
   }
   //NEW
     else if ((input[pos] == 'n' && input[pos+1] == 'e' && input[pos+2] == 'w') && isspace(input[pos+3])){
       pos = pos + 3;
       tok = new Token(NEW);
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
