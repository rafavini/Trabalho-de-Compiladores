#include "scanner.h"    

//Construtor
Scanner::Scanner(string input)
{
   /* this->input = input;
    cout << "Entrada: " << (*input) << endl << "Tamanho: " 
         << input->length() << endl; */
    pos = 0;
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

//Método que retorna o próximo token da entrada
Token* 
Scanner::nextToken()
{
    Token* tok;
    int state;
    
    state = 0;

    //Consumir espaços em branco
    while (isspace((input)[pos]))
        pos++;

    //Verificar os tokens possíveis
    //Fim de arquivo
    if ( (input)[pos] == '\0')
    {
        tok = new Token(END_OF_FILE);
    }
    //Operadores aritmeticos
    
    
   else if ((input)[pos] == '+')//+
   {
        pos++;
        tok = new Token(ARITHOP, PLUS);
   }
   else if ((input)[pos] == '-')//-
   {
        pos++;
        tok = new Token(ARITHOP, MINUS);
   }
   else if ((input)[pos] == '*')//*
   {
        pos++;
        tok = new Token(ARITHOP, MULT);
   }
   else if ((input)[pos] == '<')
   {
    pos++;
        if((input)[pos] == '=')
        {
            pos++;
            tok = new Token(ARITHOP,MENOR_IGUAL);
        }else
        {
            tok = new Token(ARITHOP,MENOR);
        }
    
   }
    else if ((input)[pos] == '>')
   {
    pos++;
        if((input)[pos] == '=')
        {
            pos++;
            tok = new Token(ARITHOP,MAIOR_IGUAL);
        }else
        {
           tok = new Token(ARITHOP,MAIOR); 
        }
    
   }
   else if((input)[pos] == '%')
   {
    pos++;
    tok = new Token(ARITHOP,MOD);
   }
   else if ((input)[pos] == '=')
   {
    pos++;
    if((input)[pos] == '=')
    {
        pos++;
        tok = new Token(ARITHOP,IGUAL);
    }else
    {
        tok = new Token(ARITHOP,RECEBE);
    }
   }   
   else if ((input)[pos] == '!')
   {
    pos++;
    if((input)[pos] == '=')
    {
        pos++;
        tok = new Token(ARITHOP,DIFERENTE);
    }
   }
   else if ((input)[pos] == '/')
   {
        pos++;
        if((input)[pos] == '/')
        {
            pos++;
            while(isalpha((input)[pos]) || isalnum((input)[pos])|| isspace((input)[pos]))
                pos++;
                
            //COLOCAR AQUI DEPOIS A CONDICAO DO \n
             tok = new Token(COMENTARIO);
            
        }else if((input)[pos] =='*')
        {
            pos++;
            while(isalpha((input)[pos]) || isalnum((input)[pos])|| isspace((input)[pos]))
                pos++;
            if((input)[pos] == '*')
            {
                pos++;
                if((input)[pos] == '/')
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
   else if ((input)[pos] == '(')
   {
        pos++;
        tok = new Token(LPAREN);
   }
   else if ((input)[pos] == ')')
   {
        pos++;
        tok = new Token(RPAREN);
   }
    else if ((input)[pos] == '[')
   {
        pos++;
        tok = new Token(LCOL);
   }
   else if ((input)[pos] == ']')
   {
        pos++;
        tok = new Token(RCOL);
   }
    else if ((input)[pos] == '{')
   {
        pos++;
        tok = new Token(LCHAVES);
   }
   else if ((input)[pos] == '}')
   {
        pos++;
        tok = new Token(RCHAVES);
   }
   else if ((input)[pos] == '.')
   {
        pos++;
        tok = new Token(PONTO);
   }
    else if ((input)[pos] == ',')
   {
        pos++;
        tok = new Token(VIRGULA);
   }
   else if ((input)[pos] == ';')
   {
        pos++;
        tok = new Token(PONTO_VIRGULA);
   }
   

   //STRING LITERAL
   else if ((input)[pos] == '"')
   {
        pos++;
        while(isalpha((input)[pos]) || isalnum((input)[pos])|| isspace((input)[pos]))
            pos++; 
        if((input)[pos] == '"')
        {
            pos++;
            tok = new Token(STRING_LITERAL);
        }
   }

   
    //Identificadores
    else if (isalpha((input)[pos]) || (input)[pos] == '_')
    {
        pos++;
        while (isalnum((input)[pos]))
            pos++;

        //Pesquisar na tabela de palavras reservadas
        //caso encontrem, retornem o token adequado,
        //caso contrário, é ID
        tok = new Token(ID);
    }
    //Números
    else if (isdigit((input)[pos]))
    {
        pos++;
        while (isdigit((input)[pos]))
            pos++;

        bool isFloat = false;

        if ((input)[pos] == '.')
        {
            pos++;

            if (isdigit((input)[pos]))
            {
                pos++;
                while (isdigit((input)[pos]))
                    pos++;
            }
            else
                lexicalError();

            isFloat = true;
        }

        bool isDouble = false;
        if ((input)[pos] == 'E')
        {
            pos++;

            if ((input)[pos] == '+' || (input)[pos] == '-')
                pos++;

            if (isdigit((input)[pos]))
            {
                pos++;
                while (isdigit((input)[pos]))
                    pos++;
            }
            else
                lexicalError();

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
        lexicalError();

    return tok;
    /*

    while (true)
    {
        switch (state)
        {
            case 0:
                if (input[pos] == '\0')
                {
                    tok = new Token(END_OF_FILE);

                    return tok;
                }
                else if (input[pos] == '<')
                    state = 1;
                else if (input[pos] == '=')
                    state = 5;
                else if (input[pos] == '>')
                    state = 6;
                else if (isalpha(input[pos]))
                    state = 10;
                else if (isdigit(input[pos]))
                    state = 13;
                else if (isspace(input[pos]))
                    state = 23;
                else
                    lexicalError();//Outros possíveis tokens

                pos++;

                break;
            case 1:
                if (input[pos] == '=')
                    state = 2;
                else if (input[pos] == '>')
                    state = 3;
                else
                    state = 4;

                pos++;

                break;
            case 2:
                tok = new Token(RELOP, LE);
                return tok;
            case 3:
                tok = new Token(RELOP, NE);
                return tok;
            case 4:
                tok = new Token(RELOP, LT);
                pos--;
                return tok;
            case 5:
                tok = new Token(RELOP, EQ);
                return tok;
            case 6:
                if (input[pos] == '=')
                    state = 7;
                else
                    state = 8;

                pos++;

                break;
            case 7:
                tok = new Token(RELOP, GE);
                return tok;
            case 8:
                tok = new Token(RELOP, GT);
                pos--;
                return tok;
            case 10:
                if (isalnum(input[pos]))
                    pos++;
                else
                {
                    state = 11;
                    pos++;
                }
                break;
            case 11:
                tok = new Token(ID);
                pos--; 

                return tok;
            case 13:
                if (isdigit(input[pos]))
                    pos++;
                else
                {
                    if (input[pos] == '.')
                        state = 14;
                    else if (input[pos] == 'E')
                        state = 16;
                    else
                        state = 20;

                    pos++;
                }
                break;
            case 14:
                if (isdigit(input[pos]))
                {
                    state = 15;
                    pos++;
                }
                else
                    lexicalError();

                break;
            case 15:
                if (isdigit(input[pos]))
                    pos++;
                else if (input[pos] == 'E')
                    state = 16;
                else
                    state = 21;

                pos++;

                break;
            case 16:
                if (input[pos] == '+' || input[pos] == '-')
                {
                    state = 17;
                    pos++;
                }
                else if (isdigit(input[pos]))
                {
                    state = 18;
                    pos++;
                }
                else
                    lexicalError();

                break;
            case 17:
                if (isdigit(input[pos]))
                {
                    state = 18;
                    pos++;
                }
                else
                    lexicalError();

                break;

            case 18:
                if (isdigit(input[pos]))
                    pos++;
                else
                    state = 19;

                pos++;

                break;
            case 19:
                tok = new Token(NUMBER, DOUBLE_LITERAL);
                pos--;
                return tok;

            case 20:
                tok = new Token(NUMBER, INTEGER_LITERAL);
                pos--;
                return tok;

            case 21:
                tok = new Token(NUMBER, FLOAT_LITERAL);
                pos--;
                return tok;

            case 23:
                if (isspace(input[pos]))
                    pos++;
                else
                    state = 24;

                pos++;

                break;

            case 24:
                pos--;
                state = 0;
                break;
            //outros casos....
            default:
                lexicalError();

        }
    }*/
}

void 
Scanner::lexicalError()
{
    cout << "Token mal formado\n";
    
    exit(EXIT_FAILURE);
}
