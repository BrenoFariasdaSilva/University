/*

Reproduza todas as formas de Entrada, Processamento e Saída (como visto em aula) para o problema abaixo. 
Escreva um algoritmo que calcule a média aritmética simples de 3 notas de um aluno. 
Na parte do processamento desenvolva uma função responsável por efetuar o cálculo da média e invoque essa função na main.

*/

#include <stdio.h>
#include <stdlib.h>

float AverageCalculator (const float grade1, const float grade2, const float grade3);

float main(int argc, char const *argv[])
{
    float grade1 = 0;
    float grade2 = 0;
    float grade3 = 0;

    // Input

    grade1 = atof(argv[1]);
    grade2 = atof(argv[2]);
    grade3 = atof(argv[3]);

    // Processing

    const float Average = AverageCalculator (grade1, grade2, grade3);

    // Output

    printf("%.2f", Average);
      
    return 0;
}

float AverageCalculator (const float grade1, const float grade2, const float grade3)
{
    const float Average = (grade1 + grade2 + grade3) / 3;

    return Average;
}
