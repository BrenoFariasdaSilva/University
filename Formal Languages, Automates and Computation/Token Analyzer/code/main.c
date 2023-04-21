// Author: Breno Farias da Silva
// Email: brenofarias@alunos.utfpr.edu.br
// Curso: Ciência da Computação (BCC)
// Disciplina: BCC34B - Linguagens formais, automatos e computabilidade
// Turma: IC4A_CM
// Instituição: Universidade Tecnológica Federal do Paraná (UTFPR)
// Campi: Campo Mourão - PR
// Date: 13/05/2022
// Atividade: Projetar e implementar um autômato com saída, do tipo Máquina de Moore, que funcione como um Analisador Léxico para a linguagem C- (CM).

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Defining the keywords
#define IF "if"
#define ELSE "else"
#define INT "int"
#define RETURN "return"
#define VOID "void"
#define WHILE "while"

// Defining the keywords output
#define IF_OUTPUT "IF"
#define ELSE_OUTPUT "ELSE"
#define INT_OUTPUT "INT"
#define FLOAT_OUTPUT "FLOAT"
#define FOR_OUTPUT "FOR"
#define RETURN_OUTPUT "RETURN"
#define VOID_OUTPUT "VOID"
#define WHILE_OUTPUT "WHILE"

// Defining the symbols
#define PLUS '+'
#define MINUS '-'
#define MULTIPLY '*'
#define DIVIDE '/'
#define LESS_THAN '<'
#define LESS_THAN_EQUAL '<'
#define GREATER_THAN '>'
#define GREATER_THAN_EQUAL '>'
#define EQUAL '='
#define SEMICOLON ';'
#define COMMA ','
#define LEFT_PARENTHESIS '('
#define RIGHT_PARENTHESIS ')'
#define LEFT_BRACKET '['
#define RIGHT_BRACKET ']'
#define LEFT_BRACE '{'
#define RIGHT_BRACE '}'

// Defining the symbols output
#define PLUS_OUTPUT "PLUS"
#define MINUS_OUTPUT "MINUS"
#define MULTIPLY_OUTPUT "MULTIPLY"
#define DIVIDE_OUTPUT "DIVIDE"
#define LESS_THAN_OUTPUT "LESS_THAN"
#define LESS_THAN_EQUAL_OUTPUT "LESS_THAN_EQUAL"
#define GREATER_THAN_OUTPUT "GREATER_THAN"
#define GREATER_THAN_EQUAL_OUTPUT "GREATER_THAN_EQUAL"
#define EQUAL_OUTPUT "EQUAL TO"
#define ATTRIBUTION_OUTPUT "ATTRIBUTION"
#define SEMICOLON_OUTPUT "SEMICOLON"
#define COMMA_OUTPUT "COMMA"
#define LEFT_PARENTHESIS_OUTPUT "LPAREN"
#define RIGHT_PARENTHESIS_OUTPUT "RPAREN"
#define LEFT_BRACKET_OUTPUT "LBRACKETS"
#define RIGHT_BRACKET_OUTPUT "RBRACKETS"
#define LEFT_BRACE_OUTPUT "LBRACES"
#define RIGHT_BRACE_OUTPUT "RBRACES"
#define NUM_OUTPUT "NUMBER"

int main(int argc, char *argv[]) {
    // Verifica se o número de argumentos está correto (igual a 2)
    if (argc != 2) {
        printf("Use: ./main <input_file_name>\n");
        return 1;
    }

    // Abrindo o arquivo
    FILE* fptr = fopen(argv[1], "r");

    if (fptr == NULL) {
        printf("Error: File not found\n");
        return 1;
    }

    int state = 0;

    char c = 0;

    while ((c = fgetc(fptr)) != EOF)
    {
        // se for espaço, tab, ou newline, ignora
        if (c == ' ' || c == '\n' || c == '\t') {
            state = 0;
        }

        // verifica se é um palavra reservada
        else if (c == 'f' && fgetc(fptr) == 'l' && fgetc(fptr) == 'o' && fgetc(fptr) == 'a' && fgetc(fptr) == 't') {
            state = 28;
            printf("%s\n", FLOAT_OUTPUT);
        }
        else if (c == 'f' && fgetc(fptr) == 'o' && fgetc(fptr) == 'r') {
            state = 51;
            printf("%s\n", FOR_OUTPUT);
        }
        else if (c == 'i' && fgetc(fptr) == 'n' && fgetc(fptr) == 't') {
            state = 4;
            printf("%s\n", INT_OUTPUT);
        }
        else if (c == 'v' && fgetc(fptr) == 'o' && fgetc(fptr) == 'i' && fgetc(fptr) == 'd') {
            state = 18;
            printf("%s\n", VOID_OUTPUT);
        }
        else if (c == 'i' && fgetc(fptr) == 'f') {
            state = 2;
            printf("%s\n", IF_OUTPUT);
        }
        else if (c == 'e' && fgetc(fptr) == 'l' && fgetc(fptr) == 's' && fgetc(fptr) == 'e') {
            state = 14;
            printf("%s\n", ELSE_OUTPUT);
        }
        else if (c == 'r' && fgetc(fptr) == 'e' && fgetc(fptr) == 't' && fgetc(fptr) == 'u' && fgetc(fptr) == 'r' && fgetc(fptr) == 'n') {
            state = 10;
            printf("%s\n", RETURN_OUTPUT);
        }
        else if (c == 'w' && fgetc(fptr) == 'h' && fgetc(fptr) == 'i' && fgetc(fptr) == 'l' && fgetc(fptr) == 'e') {
            state = 23;
            printf("%s\n", WHILE_OUTPUT);
        }

        // Verifica se é um número, seja um número inteiro ou um número real
        else if (isdigit(c))
        {
            while (isdigit(c) || c == '.') // se for um número (int ou float), continua lendo até encontrar um caracter que não seja um número
                c = fgetc(fptr);
            printf("%s\n", NUM_OUTPUT);
            fseek(fptr, -1, SEEK_CUR);
            state = 48;
        }

        // Verifica se é um símbolo
        else if (c == EQUAL && fgetc(fptr) == EQUAL) {
            state = 37;
            printf("%s\n", EQUAL_OUTPUT);
        }
        else if (c == EQUAL) {
            state = 37;
            printf("%s\n", ATTRIBUTION_OUTPUT);
        }
        else if (c == PLUS) {
            state = 30;
            printf("%s\n", PLUS_OUTPUT);
        }
        else if (c == MINUS) {
            state = 29;
            printf("%s\n", MINUS_OUTPUT);
        }
        else if (c == MULTIPLY) {
            state = 31;
            printf("%s\n", MULTIPLY_OUTPUT);
        }
        else if (c == LESS_THAN && fgetc(fptr) == EQUAL) {
            state = 34;
            printf("%s\n", LESS_THAN_EQUAL_OUTPUT);
        }
        else if (c == GREATER_THAN && fgetc(fptr) == EQUAL) {
            state = 36;
            printf("%s\n", GREATER_THAN_EQUAL_OUTPUT);
        }
        else if (c == DIVIDE) {
            state = 32;
            printf("%s\n", DIVIDE_OUTPUT);
        }
        else if (c == LESS_THAN) {
            state = 33;
            printf("%s\n", LESS_THAN_OUTPUT);
        }
        else if (c == GREATER_THAN) {
            state = 35;
            printf("%s\n", GREATER_THAN_OUTPUT);
        }
        else if (c == SEMICOLON) {
            state = 39;
            printf("%s\n", SEMICOLON_OUTPUT);
        }
        else if (c == COMMA) {
            state = 38;
            printf("%s\n", COMMA_OUTPUT);
        }
        else if (c == LEFT_PARENTHESIS) {
            state = 46;
            printf("%s\n", LEFT_PARENTHESIS_OUTPUT);
        }
        else if (c == RIGHT_PARENTHESIS) {
            state = 45;
            printf("%s\n", RIGHT_PARENTHESIS_OUTPUT);
        }
        else if (c == LEFT_BRACKET) { 
            state = 44;
            printf("%s\n", LEFT_BRACKET_OUTPUT);
        }
        else if (c == RIGHT_BRACKET) {
            state = 43;
            printf("%s\n", RIGHT_BRACKET_OUTPUT);
        }
        else if (c == LEFT_BRACE) {
            state = 42;
            printf("%s\n", LEFT_BRACE_OUTPUT);
        }
        else if (c == RIGHT_BRACE) {
            state = 41;
            printf("%s\n", RIGHT_BRACE_OUTPUT);
        }

        // Else é um ID
        else
        { // Enquanto o próximo caracter é um número ou uma letra. Se for, atualiza o ponteiro para o próximo caracter
            while (isdigit(c) || isalpha(c))
                c = fgetc(fptr);

            fseek(fptr, -1, SEEK_CUR);
            printf("ID\n");
            state = 0;
        }
    }

    // fechar arquivo argv[1];
    fclose(fptr);

    return 0;
}
