/* Exercício 1
#include <stdio.h>

#define SIZE 10

void printReverse(int n, int vet[n]);

int main()
{
    int n = SIZE, vector[SIZE] = {0};

    for (int i = 0; i < SIZE; i++)
    {
        vector[i]=i + 1;
    }

    printReverse(n, vector);
      
    return 0;
}

void printReverse(int n, int vet[n])
{
   for (int i = n - 1; i >= 0; i--)
    {
        printf("%d ", vet[i]);
    } 
}
*/


/* Exercício 2
#include <stdio.h>

#define SIZE 10

void printEven(int n, int vet[n]);

int main()
{
    int n = SIZE, vector[SIZE] = {0};

    for (int i = 0; i < SIZE; i++)
    {
        vector[i] = i + 1;
    }

    printEven(n, vector);
      
    return 0;
}

void printEven(int n, int vet[n])
{
   for (int i = 0; i < n; i++)
    {
        if (vet[i] % 2 == 0)
        {
            printf("%d ", vet[i]);
        }
    } 
}
*/


/* Exercício 3
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

void setPositive(int n, int vet[n]);

int main()
{
    int n = SIZE, vector[SIZE] = {0};

    for (int i = 0; i < SIZE; i++)
    {
        vector[i] = -5 + rand () % SIZE;
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d ", vector[i]);
    } 
    printf("\n");

    setPositive(n, vector);
      
    return 0;
}

void setPositive(int n, int vet[n])
{
   for (int i = 0; i < n; i++)
    {
        if (vet[i] < 0)
        {
            vet[i] *= -1;
        }
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d ", vet[i]);
    } 
}
*/


/* Exercício 4
#include <stdio.h>

#define SIZE 7

int sumValues(int n, int vet[n]);

int main()
{
    int n = SIZE, vector[SIZE] = {1, 23, 4, 8, 41, 7, 3}, average = 0;

    average = sumValues(n, vector);

    printf("A media aritmetica e: %d \n", average);
      
    return 0;
}

int sumValues(int n, int vet[n])
{
    int average = 0, sum = 0, i = 0;

    for (i = 0; i < n; i++)
    {
        sum += vet[i];
    } 

    average = sum / n;

    return average;
}
*/


/*Exercício 5
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int find(int n, int vet[n], int elem);

int main()
{
    int n = SIZE, vector[SIZE] = {0}, elem = 0, result = 0;

    printf("Digite o valor a ser procurado no array/vetor: ");
    scanf("%d", &elem);
    printf("\n");

    for (int i = 0; i < SIZE; i++)
    {
        vector[i] = -5 + rand () % SIZE;
    }

    result = find(n, vector, elem);

    if (result != -1)
    {
        printf("O valor esta no índice %d do array/vetor. \n", result);

        for (int i = 0; i < SIZE; i++)
        {
            printf("%d ", vector[i]);
        }
    }

    else
        printf("O valor não foi encontrado no array/vetor! \n");
      
    return 0;
}

int find(int n, int vet[n], int elem)
{
   for (int i = 0; i < n; i++)
    {
        if (vet[i] == elem)
            return i;
    }

    return -1;     
}
*/


/* Exercício 6
#include <stdio.h>
#include <limits.h>

#define SIZE 7

void findMinMax(int n, int vet[n]);

int main()
{
    int n = SIZE, vector[SIZE] = {1, 23, 4, 8, 41, 7, 3};

    findMinMax(n, vector);
      
    return 0;
}

void findMinMax(int n, int vet[n])
{
    int maior = INT_MIN, menor = INT_MAX;

    for (int i = 0; i < n; i++)
    {
        if (vet[i] > maior)
            maior = vet[i];

        if (vet[i] < menor)
            menor = vet[i];
    } 

    printf("O maior e o menor valor do array são: %d e %d", maior, menor);
}
*/


/* Exercício 7
#include <stdio.h>

#define SIZE 10

void replaceAll(int n, int vet[n], int elem);

int main()
{
    int n = SIZE, vector[SIZE] = {0}, element = 0;

    printf("Digite o valor a para alterar o array/vetor: ");
    scanf("%d", &element);

    for (int i = 0; i < SIZE; i++)
    {
        vector[i] = i + 1;
    }

    replaceAll(n, vector, element);
      
    return 0;
}

void replaceAll(int n, int vet[n], int elem)
{
    for (int i = 0; i < n; i++)
    {
        vet[i] = elem - 1;
    } 

    for (int i = 0; i < n; i++)
    {
        printf("%d ", vet[i]);
    }
    printf("\n");
}
*/

/* Exercício 8
#include <stdio.h>

#define SIZE 10

void reverse(int n, int vet[n]);

int main()
{
    int n = SIZE, vector[SIZE] = {0};

    for (int i = 0; i < SIZE; i++)
    {
        vector[i] = i + 1;
        printf("%d ", vector[i]);
    }
    printf("\n");

    reverse(n, vector);
      
    return 0;
}

void reverse(int n, int vet[n])
{   
    int hold = 0, j = n - 1;

    for (int i = 0; i < n / 2; i++)
    {
        hold = vet[i];
        vet[i] = vet[j];
        vet[j] = hold;

        j--;
    } 

    for (int i = 0; i < n; i++)
    {
        printf("%d ", vet[i]);
    }
    printf("\n");
}
*/

/*Exercício 9
#include <stdio.h>

#define SIZE 10

void readVector(int n, int vet[n]);

int main()
{
    int n = SIZE, vector[SIZE] = {0};

    readVector(n, vector);
      
    return 0;
}

void readVector(int n, int vet[n])
{   
    int value = 0;

    for (int i = 0; i < n; i++)
    {
        printf("Digite o valor da posição %d do array: ", i);
        scanf("%d", &value);

        vet[i] = value;
    } 

    for (int i = 0; i < n; i++)
    {
        printf("%d ", vet[i]);
    }
    printf("\n");
}
*/

/* Exercício 10
#include <stdio.h>

#define SIZE 10

void reverseInput(int n);

int main()
{
    int n = SIZE;

    reverseInput(n);
      
    return 0;
}

void reverseInput(int n)
{   
    int vet[n], value = 0;

    for (int i = 0; i < n; i++)
    {
        printf("Digite o valor da posição %d do array: ", i);
        scanf("%d", &value);

        vet[i] = value;
    } 

    for (int i = n - 1; i >= 0; i--)
    {
        printf("%d ", vet[i]);
    }
    printf("\n");
}
*/


/* Exercício 11
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

void countElements(int n, int vet[n]);

int main()
{
    int vet[SIZE], n = SIZE;

    printf("Vetor: ");
    
    for (int i = 0; i < n; i++)
    {
        vet[i] = rand () % SIZE;
        printf("%d ", vet[i]);  
    }

    printf("\n");

    countElements(n, vet);
      
    return 0;
}

void countElements(int n, int vet[n])
{   
    int countVet[SIZE] = {0};

    for (int i = 0; i < n; i++)
    {
        int value = vet[i];
        countVet[value]++;
    } 

    for (int i = 0; i < n; i++)
    {
        printf("Contador do numero %d: %d \n", i, countVet[i]);
    }
}
*/

/* Exercício 12
#include <stdio.h>

#define SIZE 5

void minBills(int money);

int main()
{
    int money = 0;

    printf("Digite um valor inteiro: ");
    scanf("%d", &money);

    printf("\n");

    minBills(money);
      
    return 0;
}

void minBills(int money)
{   
    const int bills[SIZE] = {1, 5, 10, 50, 100};
    int count[SIZE] = {0};

    for (int i = SIZE - 1; i >= 0; i--)
    {
        count[i] = money / bills[i];
        money -= (count[i] * bills[i]);
        printf("%d cedular de %d. \n", count[i], bills[i]);
    }
}
*/

/* Exercício 13
#include <stdio.h>
#include <math.h>

#define SIZE 10

void distances(int n, int points[n]);

int main()
{
    int coordinatesPair[SIZE] = {0}, n = SIZE;

    for (int i = 0; i < SIZE; i+=2)
    {
        printf("Digite um par ordenado: ");
        scanf("%d %d", &coordinatesPair[i], &coordinatesPair[i + 1]);
    }

    printf("\n");

    distances(n, coordinatesPair);
      
    return 0;
}

void distances(int n, int points[n])
{   
    int pointsDistance[SIZE/2] = {0};

    for (int i = 0; i < n/2; i++)
    {
        pointsDistance[i] = sqrt(((points[i + 2] - points[i]) * (points[i + 2] - points[i])) + ((points[i + 1])*(points[i+3])));
    }

    for (int i = 0; i < n/2; i++)
    {
        printf("A distancia do %d ponto e: %d \n", i + 1, pointsDistance[i]);
    }
}
*/


/* Exercício 14
#include <stdio.h>

#define SIZE 7

void histogram(int days[]);

int main()
{
    int vetHistogram[SIZE] = {0};

    for (int i = 0; i < SIZE; i++)
    {
        printf("Digite a temperatura do %dº dia: ", i + 1);
        scanf("%d", &vetHistogram[i]);
    }

    printf("\n");

    histogram(vetHistogram);
      
    return 0;
}

void histogram(int days[])
{   
    char daysLetter[SIZE] = {'D', 'S', 'T', 'Q', 'Q', 'S', 'S'};
    const char symbol = '>';

    for (int i = 0; i < SIZE; i++)
    {
        printf("%c:", daysLetter[i]);

        for (int j = 0; j < days[i]; j++)
        {
            printf("%c", symbol);
        }
        printf("\n");
    }
}
*/


/* Exercício 15
#include <stdio.h>
#include <limits.h>

#define SIZE 7

void tempReport(int days[]);

int main()
{
    int vetHistogram[SIZE] = {0};

    for (int i = 0; i < SIZE; i++)
    {
        printf("Digite a temperatura do %dº dia: ", i + 1);
        scanf("%d", &vetHistogram[i]);
    }

    printf("\n");

    tempReport(vetHistogram);
      
    return 0;
}

void tempReport(int days[])
{   
    char daysLetter[SIZE] = {'D', 'S', 'T', 'Q', 'Q', 'S', 'S'};
    const char symbol = '>';

    int average = 0, max = INT_MIN, min = INT_MAX;

    for (int i = 0; i < SIZE; i++)
    {
        average += days[i];

        if (days[i] > max)
            max = days[i];
        if (days[i] < min)
            min = days[i];

        printf("%c:", daysLetter[i]);

        for (int j = 0; j < days[i]; j++)
        {
            printf("%c", symbol);
        }
        printf("\n");
    }

    average /= 7;

    printf("A média é: %d \n", average);
    printf("A mínima é: %d \n", min);
    printf("A máxima é: %d \n", max);
}
*/


/* Exercício 16
#include <stdio.h>

#define SIZE 8

void defrag(const int n, const int vet[n]);

int main()
{
    int vet[SIZE] = {1, 6, -1, 9, 4, -1, 2, -1};
    const int n = SIZE;

    defrag(n, vet);
      
    return 0;
}

void defrag(const int n, const int vet[n])
{  
    int defrag[SIZE] = {0};

    for (int i = 0, j = SIZE - 1, k = 0; i < SIZE; i++)
    {
        if (vet[i] == -1)
        {
            defrag[j] = -1;
            j--;
        }

        else
        {
            defrag[k] = vet[i];
            k++;
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", defrag[i]);
    }
}
*/


/* Exercício 17
#include <stdio.h>

#define SIZE1 8
#define SIZE2 5
#define SIZE3 13

void vecConcat(int n1, int v1[n1], int n2, int v2[n2], int v3[]);

int main()
{
    int vet1[SIZE1] = {8, 7, 6, 5, 4, 3, 2, 1};
    const int n1 = SIZE1;

    int vet2[SIZE2] = {0, 1, 2, 3, 4};
    const int n2 = SIZE2;

    int vet3[SIZE3] = {0};

    vecConcat(n1, vet1, n2, vet2, vet3);
      
    return 0;
}

void vecConcat(int n1, int v1[n1], int n2, int v2[n2], int v3[])
{  
    for (int i = 0; i < SIZE3; i++)
    {
        if (i < n1)
            v3[i] = v1[i];

        else
            v3[i] = v2[i - n1];
    }

    for (int i = 0; i < SIZE3; i++)
    {
        printf("%d ", v3[i]);
    }
}
*/

/*
#include <stdio.h>

#define SIZE1 8
#define SIZE2 5
#define SIZE3 13

void vecConcat(int n1, int v1[n1], int n2, int v2[n2], int v3[]);

int main()
{
    int vet1[SIZE1] = {8, 7, 6, 5, 4, 3, 2, 1};
    const int n1 = SIZE1;

    int vet2[SIZE2] = {9, 1, 2, 3, 4};
    const int n2 = SIZE2;

    int vet3[SIZE3] = {0};

    vecConcat(n1, vet1, n2, vet2, vet3);
      
    return 0;
}

void vecConcat(int n1, int v1[n1], int n2, int v2[n2], int v3[])
{  
    for (int i = 0; i < SIZE3; i++)
    {
        int aux = 0;

        for (int j = 0; j < SIZE3; j++)
        {
            if (v1[i] == v3[j])
                aux++;
        }

        for (int j = 0; j < SIZE3; j++)
        {
            if (v2[i] == v3[j])
                aux++;
        }
        
        if (aux == 0)
        {
            if (i < n1)
                v3[i] = v1[i];

            else
                v3[i] = v2[i - n1];
        }
    }

    for (int i = 0; i < SIZE3; i++)
    {
        printf("%d ", v3[i]);
    }
}
*/

/* Exercício 19
#include <stdio.h>

#define SIZE1 8
#define SIZE2 5
#define SIZE3 13

void vecIntersection(int n1, int v1[], int n2, int v2[], int v3[]);

int main()
{
    int vet1[SIZE1] = {8, 7, 6, 5, 4, 3, 2, 1};
    const int n1 = SIZE1;

    int vet2[SIZE2] = {9, 1, 2, 3, 4};
    const int n2 = SIZE2;

    int vet3[SIZE3] = {0};

    vecIntersection(n1, vet1, n2, vet2, vet3);
      
    return 0;
}

void vecIntersection(int n1, int v1[], int n2, int v2[], int v3[])
{  
    int value = 0, aux = 0;

    for (int i = 0; i < n2; i++)
    {
        value = v2[i];

        for (int j = 0; j < n1; j++)
        {
            if (v1[j] == value)
            {
                v3[aux] = value;
                aux++;
            }
        }
    }

    for (int i = 0; i < SIZE3; i++)
    {
        printf("%d ", v3[i]);
    }
}
*/
