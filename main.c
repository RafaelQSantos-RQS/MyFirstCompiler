#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "Analex.h"
#define TAM_LEXEMA 50
#define TAM_NUM 20
#define NUM_PALAVRAS_RESERVADAS 28

// Array of reserved words, each with a maximum length of TAM_LEXEMA
char RESERVED_WORDS[][TAM_LEXEMA] = {
    "const",  // Represents the keyword "const"
    "pr",     // Represents the keyword "pr"
    "init",   // Represents the keyword "init"
    "endp",   // Represents the keyword "endp"
    "char",   // Represents the keyword "char"
    "int",    // Represents the keyword "int"
    "real",   // Represents the keyword "real"
    "bool",   // Represents the keyword "bool"
    "do",     // Represents the keyword "do"
    "while",  // Represents the keyword "while"
    "endw",   // Represents the keyword "endw"
    "var",    // Represents the keyword "var"
    "from",   // Represents the keyword "from"
    "to",     // Represents the keyword "to"
    "dt",     // Represents the keyword "dt"
    "by",     // Represents the keyword "by"
    "if",     // Represents the keyword "if"
    "endv",   // Represents the keyword "endv"
    "elif",   // Represents the keyword "elif"
    "else",   // Represents the keyword "else"
    "endi",   // Represents the keyword "endi"
    "getout", // Represents the keyword "getout"
    "getint", // Represents the keyword "getint"
    "getchar",// Represents the keyword "getchar"
    "getreal",// Represents the keyword "getreal"
    "putint", // Represents the keyword "putint"
    "putchar",// Represents the keyword "putchar"
    "putreal" // Represents the keyword "putreal"
};

/**
 * Checks if the given word is a reserved word.
 * 
 * @param word The word to check.
 * @return The index of the reserved word in the RESERVED_WORDS array if found, 
 *         otherwise returns -1.
 */
int is_reserved_word(const char *word)
{
    for (int i = 0; i < NUM_PALAVRAS_RESERVADAS; i++)
    {
        if (strcmp(RESERVED_WORDS[i], word) == 0)
        {
            return i; // A palavra foi encontrada
        }
    }
    return -1; // A palavra não foi encontrada
}

/**
 * Prints an error message and exits the program.
 * 
 * @param msg The error message to print.
 */
void error(char msg[])
{
    printf("%s\n", msg);
    exit(1);
}

/**
 * @brief Analisador léxico que lê um arquivo e retorna tokens.
 * 
 * @param file Arquivo a ser lido.
 * @return O token lido.
 */
TOKEN AnaLex(FILE *file)
{

    int estado = 0;
    char lexema[TAM_LEXEMA] = "";
    int tamLexema = 0;
    char digitos[TAM_NUM] = "";
    int tamDigitos = 0;

    TOKEN token;
    while (true)
    {
        char c = fgetc(file);
        switch (estado)
        {
        case 0:
            if (c == ' ' || c == '\t')
                estado = 0;
            else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
            { // inicio de identificador - lexema
                estado = 1;
                lexema[tamLexema] = c;
                lexema[++tamLexema] = '\0';
            }
            else if (c >= '1' && c <= '9')
            { // inicio constante inteira - digitos
                estado = 10;
                digitos[tamDigitos] = c;
                digitos[++tamDigitos] = '\0';
            }
            else if (c == '+')
            { // Sinal de adicao
                estado = 3;
                token.categoria = SN;
                token.codigo = ADICAO;
                return token;
            }
            else if (c == '-')
            { // Sinal de subtracao
                estado = 4;
                token.categoria = SN;
                token.codigo = SUBTRACAO;
                return token;
            }
            else if (c == '*')
            { // Sinal de multiplicacao
                estado = 5;
                token.categoria = SN;
                token.codigo = MULTIPLICACAO;
                return token;
            }
            else if (c == '/')
            { // Sinal de divisao
                estado = 6;
                token.categoria = SN;
                token.codigo = DIVISAO;
            }
            else if (c == '=')
            { // Sinal de atribuicao
                estado = 7;
                token.categoria = SN;
                token.codigo = ATRIB;
            }
            else if (c == '(')
            { // Sinal de abre parenteses
                estado = 8;
                token.categoria = SN;
                token.codigo = ABRE_PARENTESE;
                return token;
            }
            else if (c == ')')
            { // Sinal de fecha parenteses
                estado = 9;
                token.categoria = SN;
                token.codigo = FECHA_PARENTESE;
                return token;
            }
            else if (c == '{')
            { // Sinal de abre chaves
                estado = 12;
                token.categoria = SN;
                token.codigo = ABRE_CHAVES;
                return token;
            }
            else if (c == '}')
            { // Sinal de fecha chaves
                estado = 13;
                token.categoria = SN;
                token.codigo = FECHA_CHAVES;
                return token;
            }
            else if (c == '[')
            { // Sinal de abre colchetes
                estado = 14;
                token.categoria = SN;
                token.codigo = ABRE_COLCHETE;
                return token;
            }
            else if (c == ']')
            { // Sinal de fecha colchetes
                estado = 15;
                token.categoria = SN;
                token.codigo = FECHA_COLCHETE;
                return token;
            }
            else if (c == '<')
            { // Sinal de menor que
                estado = 16;
                token.categoria = SN;
                token.codigo = MENOR;
            }
            else if (c == '>')
            { // Sinal de maior que
                estado = 18;
                token.categoria = SN;
                token.codigo = MAIOR;
            }
            else if (c == '!')
            { // Sinal de negacao
                estado = 20;
                token.categoria = SN;
                token.codigo = NEGACAO;
            }
            else if (c == '&')
            { // Sinal de e (PONTEIRO)
                estado = 23;
                token.categoria = SN;
                token.codigo = PONTEIRO;
            }
            else if (c == '|')
            { // Sinal de ou
                estado = 25;
                token.categoria = SN;
            }
            else if (c == ',')
            { // Sinal virgula
                estado = 26;
                token.categoria = SN;
                token.codigo = VIRGULA;
                return token;
            }
            else if (c == '\n')
            {
                estado = 0;
                token.categoria = FIM_EXPR;
                contLinha++;
                return token;
            }
            else if (c == EOF)
            {
                token.categoria = FIM_ARQ;
                return token;
            }
            else if (c == '"')
            {
                token.categoria = STRING;
                estado = 29;
                token.lexema[tamLexema] = c;
                token.lexema[++tamLexema] = '\0';
            }
            else
            {
                error("Caractere invalido na linha!");
            }
            break;

        case 1: // Identificador ou palavra reservada
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')
            {
                estado = 1;
                lexema[tamLexema] = c;
                lexema[++tamLexema] = '\0';
            }
            else
            {
                ungetc(c, file);
                strcpy(token.lexema, lexema);
                int is_rw = is_reserved_word(token.lexema);
                if (is_rw >= 0)
                {
                    estado = 28;
                    token.categoria = PALAVRA_RESERVADA;
                    token.whatReservedWord = is_rw;
                }
                else
                {
                    estado = 2;
                    token.categoria = ID;
                }
                return token;
            }
            break;

        case 6: // Vericar comentário
            if (c == '/')
            {
                estado = 27; // Comentario
                break;
            }
            else
            {
                return token;
            }

        case 7: // Sinal de atribuicao
            if (c == '=')
            { // Sinal de igual
                estado = 22;
                token.categoria = SN;
                token.codigo = IGUAL;
                return token;
            }
            else
            {
                ungetc(c, file);
                return token;
            }
            break;

        case 10: // Constante inteira
            if (c >= '0' && c <= '9')
            {
                estado = 10;
                digitos[tamDigitos] = c;
                digitos[++tamDigitos] = '\0';
            } else if (c == '.') {
                estado = 30;
                digitos[tamDigitos] = c;
                digitos[++tamDigitos] = '\0';
            }
            else
            {
                estado = 11;
                ungetc(c, file);
                token.categoria = CT_I;
                token.valInt = atoi(digitos);
                return token;
            }
            break;

        case 16: // Sinal de menor que
            if (c == '=')
            { // Sinal de menor ou igual
                estado = 17;
                token.categoria = SN;
                token.codigo = MENOR_IGUAL;
                return token;
            }
            else
            {
                return token;
            }
            break;

        case 18: // Sinal de maior que
            if (c == '=')
            { // Sinal de maior ou igual
                estado = 19;
                token.categoria = SN;
                token.codigo = MAIOR_IGUAL;
                return token;
            }
            else
            {
                return token;
            }
            break;

        case 20: // Sinal de diferente
            if (c == '=')
            { // Sinal de diferente
                estado = 21;
                token.categoria = SN;
                token.codigo = DIFERENTE_DE;
                return token;
            }
            else
            {
                return token;
            }
            break;

        case 23: // Sinal de e
            if (c == '&')
            { // Sinal de e
                estado = 24;
                token.categoria = SN;
                token.codigo = AND;
                return token;
            }
            else
            {
                return token;
            }
            break;

        case 25: // Sinal de ou
            if (c == '|')
            { // Sinal de ou
                token.codigo = OR;
                return token;
            }
            else
            {
                error("Caracter inválido");
            }
            break;

        case 27: // Vericar comentário
            if (c == '\n')
            {
                estado = 0;
                ungetc(c, file);
            }
            break;
        case 29:
            if (c == '"')
            {                                 // Encontra o final da string
                lexema[tamLexema] = '\0';     // Finaliza o lexema
                strcpy(token.lexema, lexema); // Copia para o token
                token.categoria = STRING;
                return token;
            }
            else if ((c == '\n') || (c == EOF))
            { // Erro: string mal formada
                error("String mal formada!");
            }
            else
            { // Continua lendo a string
                lexema[++tamLexema] = c;
            }
            break;
        case 30:
            if (c >= '0' && c <= '9')
            {
                estado = 30;
                digitos[tamDigitos] = c;
                digitos[++tamDigitos] = '\0';
            }
            else
            {
                ungetc(c, file);
                token.categoria = CT_R;
                token.valReal = atof(digitos);
                return token;
            }
            break;
        }
    }
}

/**
 * Função principal do programa.
 * 
 * Abre um arquivo e processa suas linhas,
 * chamando a função AnaLex() para analisar cada linha e extrair seus
 * tokens. Em seguida, imprime os tokens extraídos na forma de pares
 * categoria, lexema. Se o token for uma palavra reservada, imprime
 * a categoria e o valor da palavra reservada. Se o token for um sinal,
 * imprime a categoria e o valor do sinal. Se o token for um identificador,
 * imprime a categoria e o valor do identificador. Se o token for uma
 * constante inteira, imprime a categoria e o valor da constante. Se o
 * token for uma constante real, imprime a categoria e o valor da
 * constante. Se o token for uma string, imprime a categoria e o valor
 * da string. Quando o token for o final do arquivo, imprime o final do
 * arquivo e fecha o arquivo.
 */
int main()
{

    FILE *file;
    TOKEN token;

    if ((file = fopen("teste_palavra_reservada.txt", "r")) == NULL)
    {
        error("Erro ao abrir o arquivo");
    }

    printf("LINHA %d\n", contLinha);

    while (1)
    { // Laço infinito para processar até o fim do arquivo
        token = AnaLex(file);
        switch (token.categoria)
        {
        case ID:
            printf("<ID, %s>\n", token.lexema);
            break;
        case PALAVRA_RESERVADA:
            switch (token.whatReservedWord) {
            case CONST: printf("<PALAVRA_RESERVADA, CONST>\n"); break;
            case PR: printf("<PALAVRA_RESERVADA, PR>\n"); break;
            case INIT: printf("<PALAVRA_RESERVADA, INIT>\n"); break;
            case ENDP: printf("<PALAVRA_RESERVADA, ENDP>\n"); break;
            case CHAR: printf("<PALAVRA_RESERVADA, CHAR>\n"); break;
            case INT: printf("<PALAVRA_RESERVADA, INT>\n"); break;
            case REAL: printf("<PALAVRA_RESERVADA, REAL>\n"); break;
            case BOOL: printf("<PALAVRA_RESERVADA, BOOL>\n"); break;
            case DO: printf("<PALAVRA_RESERVADA, DO>\n"); break;
            case WHILE: printf("<PALAVRA_RESERVADA, WHILE>\n"); break;
            case ENDW: printf("<PALAVRA_RESERVADA, ENDW>\n"); break;
            case VAR: printf("<PALAVRA_RESERVADA, VAR>\n"); break;
            case FROM: printf("<PALAVRA_RESERVADA, FROM>\n"); break;
            case TO: printf("<PALAVRA_RESERVADA, TO>\n"); break;
            case DT: printf("<PALAVRA_RESERVADA, DT>\n"); break;
            case BY: printf("<PALAVRA_RESERVADA, BY>\n"); break;
            case IF: printf("<PALAVRA_RESERVADA, IF>\n"); break;
            case ENDV: printf("<PALAVRA_RESERVADA, ENDV>\n"); break;
            case ELIF: printf("<PALAVRA_RESERVADA, ELIF>\n"); break;
            case ELSE: printf("<PALAVRA_RESERVADA, ELSE>\n"); break;
            case ENDI: printf("<PALAVRA_RESERVADA, ENDI>\n"); break;
            case GETOUT: printf("<PALAVRA_RESERVADA, GETOUT>\n"); break;
            case GETINT: printf("<PALAVRA_RESERVADA, GETINT>\n"); break;
            case GETCHAR: printf("<PALAVRA_RESERVADA, GETCHAR>\n"); break;
            case GETREAL: printf("<PALAVRA_RESERVADA, GETREAL>\n"); break;
            case PUTINT: printf("<PALAVRA_RESERVADA, PUTINT>\n"); break;
            case PUTCHAR: printf("<PALAVRA_RESERVADA, PUTCHAR>\n"); break;
            case PUTREAL: printf("<PALAVRA_RESERVADA, PUTREAL>\n"); break;
            break;
            }
            break;
        case SN:
            switch (token.codigo)
            {
            case ADICAO:
                printf("<SN, ADICAO>\n");
                break;
            case SUBTRACAO:
                printf("<SN, SUBTRACAO>\n");
                break;
            case MULTIPLICACAO:
                printf("<SN, MULTIPLICACAO>\n");
                break;
            case DIVISAO:
                printf("<SN, DIVISAO>\n");
                break;
            case ATRIB:
                printf("<SN, ATRIB>\n");
                break;
            case IGUAL:
                printf("<SN, IGUALDADE>\n");
                break;
            case NEGACAO:
                printf("<SN, NEGACAO>\n");
                break;
            case PONTEIRO:
                printf("<SN, E>\n");
                break;
            case OR:
                printf("<SN, OR>\n");
                break;
            case MENOR:
                printf("<SN, MENOR>\n");
                break;
            case MAIOR:
                printf("<SN, MAIOR>\n");
                break;
            case MENOR_IGUAL:
                printf("<SN, MENOR_IGUAL>\n");
                break;
            case MAIOR_IGUAL:
                printf("<SN, MAIOR_IGUAL>\n");
                break;
            case DIFERENTE_DE:
                printf("<SN, DIFERENTE_DE>\n");
                break;
            case AND:
                printf("<SN, AND>\n");
                break;
            case ABRE_PARENTESE:
                printf("<SN, ABRE_PARENTESE>\n");
                break;
            case FECHA_PARENTESE:
                printf("<SN, FECHA_PARENTESE>\n");
                break;
            case ABRE_CHAVES:
                printf("<SN, ABRE_CHAVES>\n");
                break;
            case FECHA_CHAVES:
                printf("<SN, FECHA_CHAVES>\n");
                break;
            case ABRE_COLCHETE:
                printf("<SN, ABRE_COLCHETE>\n");
                break;
            case FECHA_COLCHETE:
                printf("<SN, FECHA_COLCHETE>\n");
                break;
            case VIRGULA:
                printf("<SN, VIRGULA>\n");
                break;
            }
            break;
        case CT_I:
            printf("<CT_I, %d>\n", token.valInt);
            break;
        case CT_R:
            printf("<CT_R, %f>\n", token.valReal);
            break;
        case STRING:
            printf("<STRING, %s>\n", token.lexema);
            break;
        case FIM_EXPR:
            printf("<FIM_EXPR>\n");
            printf("\nLINHA %d\n", contLinha);
            break;
        case FIM_ARQ:
            printf("<FIM_ARQ>\n");
            break;
        }
        if (token.categoria == FIM_ARQ)
            break;
    }
    fclose(file);
    return 0;
}