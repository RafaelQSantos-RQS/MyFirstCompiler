#ifndef ANALEX
#define ANALEX
#define TAM_MAX_LEXEMA 31

// Definindo categorias de token
enum TOKEN_CATEGORIAS {
    ID=1, // Identificador
    SN, // Sinal
    CT_I, // Constante inteira
    CT_R, // Constante real
    PALAVRA_RESERVADA, // Palavra reservada
    COMENTARIO, // Comentario
    FIM_EXPR, // Fim de expressão
    FIM_ARQ, // Fim de arquivo
    STRING // String
};

enum SINAIS {
    ATRIB = 1, // Atribuição (=)
    ADICAO, // Adição (+)
    SUBTRACAO, // Subtração (-)
    MULTIPLICACAO, // Multiplicação (*)
    DIVISAO, // Divisão (/)
    ABRE_PARENTESE, // Abre Parenteses (()
    FECHA_PARENTESE, // Fecha Parenteses ())
    ABRE_CHAVES, // Abre Chaves ({)
    FECHA_CHAVES, // Fecha Chaves (})
    ABRE_COLCHETE, // Abre Colchetes ([])
    FECHA_COLCHETE, // Fecha Colchetes ([])
    MENOR, // Menor que (<)
    MAIOR, // Maior que (>)
    MENOR_IGUAL, // Menor ou igual (<=)
    MAIOR_IGUAL, // Maior ou igual (>=)
    IGUAL, // Igual (==)
    PONTEIRO, //PONTEIRO (&)
    AND, // EE (&&)
    OR, // Ou (||)
    VIRGULA, // Virgula (,)
    NEGACAO, // Negação (!)
    DIFERENTE_DE // Diferente de (!=)
};

enum WHAT_RESERVED_WORD {
    // Palavra reservada "const"
    CONST,
    // Palavra reservada "pr"
    PR,
    // Palavra reservada "init"
    INIT,
    // Palavra reservada "endp"
    ENDP,
    // Palavra reservada "char"
    CHAR,
    // Palavra reservada "int"
    INT,
    // Palavra reservada "real"
    REAL,
    // Palavra reservada "bool"
    BOOL,
    // Palavra reservada "do"
    DO,
    // Palavra reservada "while"
    WHILE,
    // Palavra reservada "endw"
    ENDW,
    // Palavra reservada "var"
    VAR,
    // Palavra reservada "from"
    FROM,
    // Palavra reservada "to"
    TO,
    // Palavra reservada "dt"
    DT,
    // Palavra reservada "by"
    BY,
    // Palavra reservada "if"
    IF,
    // Palavra reservada "endv"
    ENDV,
    // Palavra reservada "elif"
    ELIF,
    // Palavra reservada "else"
    ELSE,
    // Palavra reservada "endi"
    ENDI,
    // Palavra reservada "getout"
    GETOUT,
    // Palavra reservada "getint"
    GETINT,
    // Palavra reservada "getchar"
    GETCHAR,
    // Palavra reservada "getreal"
    GETREAL,
    // Palavra reservada "putint"
    PUTINT,
    // Palavra reservada "putchar"
    PUTCHAR,
    // Palavra reservada "putreal"
    PUTREAL
};

typedef
    struct {
        enum TOKEN_CATEGORIAS categoria;
        union {
            int codigo; // para tokens das categorias SN
            char lexema[TAM_MAX_LEXEMA]; // cadeira de caracteres que correspondem ao nome do token da cat. ID e PR
            int valInt; // valor da constante inteira da cat. CT_I
            double valReal; // valor da constante real da cat. CT_R
            int whatReservedWord; // para cat. PALAVRA_RESERVADA
        };
        
    
} TOKEN; // Tipo TOKEN

#endif

int contLinha = 1;