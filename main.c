#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "Analex.h"
#define TAM_LEXEMA 50
#define TAM_NUM 20
#define MAX_PALAVRAS_RESERVADAS 100

char *palavras_reservadas[MAX_PALAVRAS_RESERVADAS];
int num_palavras_reservadas = 0;

void load_reserved_words() {
    FILE *file = fopen("palavras_reservadas.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo 'palavras_reservadas.txt'\n");
        exit(1);
    }

    char line[TAM_LEXEMA];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // remove o '\n' do final
        palavras_reservadas[num_palavras_reservadas] = strdup(line);
        num_palavras_reservadas++;
    }

    fclose(file);
}

void error(char msg[]) {
    printf("%s\n", msg);
    exit(1);
}

TOKEN AnaLex(FILE *file) {
    
    int estado = 0;
    char lexema[TAM_LEXEMA] = "";
    int tamLexema = 0;
    char digitos[TAM_NUM] = "";
    int tamDigitos = 0;

    TOKEN token;
    while (true) {
        char c = fgetc(file);
        switch (estado) {
            case 0:
                if (c == ' ' || c == '\t') estado = 0;
                else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') { // inicio de identificador - lexema
                    estado = 1;
                    lexema[tamLexema] = c;
                    lexema[tamLexema + 1] = '\0';
                }
                else if (c >= '1' && c <= '9'){ // inicio constante inteira - digitos
                    estado = 10;
                    digitos[tamDigitos] = c;
                    digitos[tamDigitos + 1] = '\0';
                }
                else if (c == '+') { // Sinal de adicao
                    estado = 3;
                    token.categoria = SN;
                    token.codigo = ADICAO;
                    return token;
                }
                else if (c == '-') { // Sinal de subtracao
                    estado = 4;
                    return token;
                }
                else if (c == '*') { // Sinal de multiplicacao
                    estado = 5;
                    token.categoria = SN;
                    token.codigo = MULTIPLICACAO;
                    return token;
                }
                else if (c == '/') { // Sinal de divisao
                    estado = 6;
                    token.categoria = SN;
                    token.codigo = DIVISAO;
                }
                else if (c == '=') { // Sinal de atribuicao
                    estado = 7;
                    token.categoria = SN;
                    token.codigo = ATRIB;
                    return token;
                }
                else if (c == '(') { // Sinal de abre parenteses
                    estado = 8;
                    token.categoria = SN;
                    token.codigo = ABRE_PARENTESE;
                    return token;
                }
                else if (c == ')') { // Sinal de fecha parenteses
                    estado = 9;
                    token.categoria = SN;
                    token.codigo = FECHA_PARENTESE;
                    return token;
                }
                else if (c == '{') { // Sinal de abre chaves
                    estado = 12;
                    token.categoria = SN;
                    token.codigo = ABRE_CHAVES;
                    return token;
                }
                else if (c == '}') { // Sinal de fecha chaves
                    estado = 13;
                    token.categoria = SN;
                    token.codigo = FECHA_CHAVES;
                    return token;
                }
                else if (c == '[') { // Sinal de abre colchetes
                    estado = 14;
                    token.categoria = SN;
                    token.codigo = ABRE_COLCHETE;
                    return token;
                }
                else if (c == ']') { // Sinal de fecha colchetes
                    estado = 15;
                    token.categoria = SN;
                    token.codigo = FECHA_COLCHETE;
                    return token;
                }
                else if (c == '<') { // Sinal de menor que
                    estado = 16;
                    token.categoria = SN;
                    token.codigo = MENOR;
                }
                else if (c == '>') { // Sinal de maior que
                    estado = 18;
                    token.categoria = SN;
                    token.codigo = MAIOR;
                }
                else if (c == '!') { // Sinal de negacao
                    estado = 20;
                    token.categoria = SN;
                    token.codigo = NEGACAO;
                }
                else if (c == '&') { // Sinal de e
                    estado = 23;
                    token.categoria = SN;
                    token.codigo = E;
                }
                else if (c == '|') { // Sinal de ou
                    estado = 25;
                    token.categoria = SN;
                }
                else if (c == ',') { // Sinal de ponto e virgula
                    estado = 26;
                    token.categoria = SN;
                    token.codigo = VIRGULA;
                    return token;
                }
                else if (c == '\n') {
                    estado = 0;
                    token.categoria = FIM_EXPR;
                    contLinha++;
                    return token;
                }
                else if (c == EOF) {
                    token.categoria = FIM_ARQ;
                    return token;
                }
                else {
                    error("Caractere invalido na linha!");
                }
                break;

            case 1: // Identificador
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    estado = 1;
                    lexema[tamLexema] = c;
                    lexema[tamLexema + 1] = '\0';
                } else {
                    estado = 2;
                    ungetc(c, file);
                    token.categoria = ID;
                    strcpy(token.lexema, lexema);
                    return token;
                }
                break;
            
            case 6: // Vericar comentário
                if (c == '/') {
                    estado = 27;
                    token.categoria = COMENTARIO;
                    lexema[tamLexema] = c;
                    lexema[tamLexema + 1] = '/';
                    lexema[tamLexema + 2] = '\0';
                } else {
                    return token;
                }

            case 7: // Sinal de atribuicao
                if (c == '=') { // Sinal de igual
                    estado = 22;
                    token.categoria = SN;
                    token.codigo = IGUAL;
                    return token;
                } else {
                    token.categoria = SN;
                    token.codigo = SUBTRACAO;
                    return token;
                }
                break;
            
            case 10: // Constante inteira
                if (c >= '0' && c <= '9') {
                    estado = 10;
                    digitos[tamDigitos] = c;
                    digitos[tamDigitos + 1] = '\0';
                } else {
                    estado = 11;
                    ungetc(c, file);
                    token.categoria = CT_I;
                    token.valInt = atoi(digitos);
                    return token;
                }
                break;

            case 16: // Sinal de menor que
                if (c == '=') { // Sinal de menor ou igual
                    estado = 17;
                    token.categoria = SN;
                    token.codigo = MENOR_IGUAL;
                    return token;
                } else {
                    return token;
                }
                break;
            
            case 18: // Sinal de maior que
                if (c == '=') { // Sinal de maior ou igual
                    estado = 19;
                    token.categoria = SN;
                    token.codigo = MAIOR_IGUAL;
                    return token;
                } else {
                    return token;
                }
                break;
            
            case 20: // Sinal de diferente
                if (c == '=') { // Sinal de diferente
                    estado = 21;
                    token.categoria = SN;
                    token.codigo = DIFERENTE_DE;
                    return token;
                } else {
                    return token;
                }
                break;

            case 23: // Sinal de e
                if (c == '&') { // Sinal de e
                    estado = 24;
                    token.categoria = SN;
                    token.codigo = AND;
                    return token;
                } else {
                    return token;
                }
                break;
            
            case 25: // Sinal de ou
                if (c == '|') { // Sinal de ou
                    token.codigo = OR;
                    return token;
                } else {
                    error("Caracter inválido");
                }
                break;

            case 27: // Vericar comentário
                if (c != '\n') {
                    estado = 27;
                    lexema[tamLexema] = c;
                    lexema[tamLexema + 1] = '\0';
                } else {
                    return token;
                }
        }
    }
    
}

int main() {
    load_reserved_words();
    FILE *file = fopen("teste.txt", "r");
}