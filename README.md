# Meu primeiro compilador
Este projeto consiste me desenvolver um pequeno compilador para a matéria de compiladores da Universidade Estadual da Bahia - UNEB.

# Especificação da Linguagem
## Notação BNF Estendida
Nas regras léxicas e sintáticas descritas abaixo os caracteres da notação BNF estão grifados em {c:green}verde{/c}.

- Alternativas são separadas por barras verticais, ou seja, `a|b` sigifica `a` ou `b`.
- Colchetes indicam ocorrência opcional: `[a]` significa `a|ε`. (`ε` significa vazio)
- Chaves indicam repetição: `{a}` significa `ε|a|aa|aaa|aaaa|...`.
- Pareêntese indicam ocorrência de uma das alternativas: `(a|b|c)` significa obrigatoriamente `a` ou `b` ou `c`.

# 0. Tokens
## Palavras Reservadas
- const
- pr
- init
- endp
- char
- int
- real
- bool
- do
- while
- endw
- var
- from
- to
- dt
- by
- if
- endv
- elif
- else
- endi
- getout
- getint
- getchar
- getreal
- putint
- putchar
- putreal

## Sinais
- +
- -
- *
- /
- <
- >=
- <
- <=
- ==
- =
- (
- )
- [
- ]
- ||
- &
- &&
- , (virgula)
- !
- !=

# 1. Regras Léxicas
*letra* ::= a|b|...|z|A|B|...|Z

*digito* ::= 0|1|2|3|4|5|6|7|8|9

id ::= {_}letra{letra|digito|_}

intcon ::= digito{digito}

realcon ::= intcon.intcon

charcon ::= 'ch' | '\n' | '\0', onde ch denota qualquer caractere imprimível da tabela ASCII, como especificado pela função isprint() da linguagem C, diferente de \ (barra invertida) e ' (apóstrofo).

stringcon ::= "{ch}", onde ch denota qualquer caractere imprimível da tabela ASCII, como especificado pela função isprint() da linguagem C, diferente de " (aspas) e do caractere newline (\n).

idconst ::= indica a ocorrência de uma constante inteira declarada e inicializada previamente com "const int".

idproc ::= indica a ocorrencia de um nome de procedimento.

*comentário" Comentários iniciam sempre com o sufixo // (dupla barra comum) e se estendem até a ocorrência do caractere de fim de linha (\n).

# 2. Regras Sintáticas
Símbolos *não-terminais* são apresentados em itálico; Símbolos *terminais* são apresentados em negrito e, eventualmente, entre aspas por questão de clareza.

Declarações e comando da linguagem têm estrutura próprio, que indica como inicia e quando termina um comando. sendo assim, declarações e comandos devem estar estruturalmente completos em uma única linha.