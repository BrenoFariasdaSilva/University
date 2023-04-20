#include <stdio.h>

int main()
{
    double nota1 = 0, nota2 = 0, nota3 = 0, average = 0;

    printf("DIgite os valores das notas dos tres alunos: ");
    scanf("%lf %lf %lf", &nota1, &nota2, &nota3);

    average = (nota1 + nota2 + nota3) / 3;

    if ((nota1 < 0) || (nota2 < 0) || (nota3 < 0) || (nota1 > 10) || (nota2 > 10) || (nota3 > 10))
    {
        printf("Valor(es) fora da escala (0-10)! \n");
    }

    else
    {
        if (average >= 9.0)
        {
            printf("O Aluno tem conceito A, com media de: %.2lf \n", average);
        }

        if ((average >= 8.0) && (average < 9.0))
        {
            printf("O Aluno tem conceito B, com media de: %.2lf \n", average);
        }

        if ((average >= 7.0) && (average < 8.0))
        {
            printf("O Aluno tem conceito C, com media de: %.2lf \n", average);
        }

        if (average < 7.0)
        {
            printf("O Aluno tem conceito F, com media de: %.2lf \n", average);
        }
    }

    return 0;
}
