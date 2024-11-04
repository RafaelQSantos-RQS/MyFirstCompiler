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

int is_reserved_word(const char *word) {
    for (int i = 0; i < num_palavras_reservadas; i++) {
        if (strcmp(palavras_reservadas[i], word) == 0) {
            return 1; // A palavra foi encontrada
        }
    }
    return 0; // A palavra não foi encontrada
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
                    lexema[++tamLexema] = '\0';
                }
                else if (c >= '1' && c <= '9'){ // inicio constante inteira - digitos
                    estado = 10;
                    digitos[tamDigitos] = c;
                    digitos[++tamDigitos] = '\0';
                }
                else if (c == '+') { // Sinal de adicao
                    estado = 3;
                    token.categoria = SN;
                    token.codigo = ADICAO;
                    return token;
                }
                else if (c == '-') { // Sinal de subtracao
                    estado = 4;
                    token.categoria = SN;
                    token.codigo = SUBTRACAO;
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
                else if (c == ',') { // Sinal virgula
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

            case 1: // Identificador ou palavra reservada
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    estado = 1;
                    lexema[tamLexema] = c;
                    lexema[++tamLexema] = '\0';
                } else {
                    ungetc(c, file);
                    strcpy(token.lexema, lexema);
                    if (is_reserved_word(token.lexema)) {
                        estado = 28;
                        token.categoria = PR;
                    } else {
                        estado = 2;
                        token.categoria = ID;
                    }
                    return token;
                }
                break;
            
            case 6: // Vericar comentário
                if (c == '/') {
                    estado = 27; // Comentario
                    break;
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
                    ungetc(c, file);
                    return token;
                }
                break;
            
            case 10: // Constante inteira
                if (c >= '0' && c <= '9') {
                    estado = 10;
                    digitos[tamDigitos] = c;
                    digitos[++tamDigitos] = '\0';
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
                if (c == '\n'){
                    estado = 0;
                    ungetc(c, file);
                }
                break;
        }
    }
    
}

int main() {
    load_reserved_words();

    FILE *file;
    TOKEN token;
    
    if ((file = fopen("teste.txt", "r")) == NULL) {
        error("Erro ao abrir o arquivo");
    }

    printf("LINHA %d\n", contLinha);

    while(1) { // Laço infinito para processar até o fim do arquivo
        token = AnaLex(file);
        switch (token.categoria){
            case ID: printf("<ID, %s>\n", token.lexema); break;
            case PR: printf("<PR, %s>\n", token.lexema); break;
            case SN:
                switch (token.codigo){
                case ADICAO: printf("<SN, ADICAO>\n"); break;
                case SUBTRACAO: printf("<SN, SUBTRACAO>\n"); break;
                case MULTIPLICACAO: printf("<SN, MULTIPLICACAO>\n"); break;
                case DIVISAO: printf("<SN, DIVISAO>\n"); break;
                case ATRIB: printf("<SN, ATRIB>\n"); break;
                case IGUAL: printf("<SN, IGUALDADE>\n"); break;
                case NEGACAO: printf("<SN, NEGACAO>\n"); break;
                case E: printf("<SN, E>\n"); break;
                case OR: printf("<SN, OR>\n"); break;
                case MENOR: printf("<SN, MENOR>\n"); break;
                case MAIOR: printf("<SN, MAIOR>\n"); break;
                case MENOR_IGUAL: printf("<SN, MENOR_IGUAL>\n"); break;
                case MAIOR_IGUAL: printf("<SN, MAIOR_IGUAL>\n"); break;
                case DIFERENTE_DE: printf("<SN, DIFERENTE_DE>\n"); break;
                case AND: printf("<SN, AND>\n"); break;
                case ABRE_PARENTESE: printf("<SN, ABRE_PARENTESE>\n"); break;
                case FECHA_PARENTESE: printf("<SN, FECHA_PARENTESE>\n"); break;
                case ABRE_CHAVES: printf("<SN, ABRE_CHAVES>\n"); break;
                case FECHA_CHAVES: printf("<SN, FECHA_CHAVES>\n"); break;
                case ABRE_COLCHETE: printf("<SN, ABRE_COLCHETE>\n"); break;
                case FECHA_COLCHETE: printf("<SN, FECHA_COLCHETE>\n"); break;
                case VIRGULA: printf("<SN, VIRGULA>\n"); break;
                }
                break;
            case CT_I: printf("<CT_I, %d>\n", token.valInt); break;
            case FIM_EXPR: printf("<FIM_EXPR>\n"); printf("\nLINHA %d\n", contLinha); break;
            case FIM_ARQ: printf("<FIM_ARQ>\n"); break;
        }
        if (token.categoria == FIM_ARQ) break;
    }
    fclose(file);
    return 0;
}